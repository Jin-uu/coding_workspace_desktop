// #define DEBUG
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){
    #ifdef DEBUG
    int offset = 3;
    char* data_s = "aaa";
    int data_len = strlen(data_s);
    char* file_name = "testFile3.txt";
    #endif
    #ifndef DEBUG
    int offset = atoi(argv[1]);
    char* data_s = strtok(argv[2],"\"");
    int data_len = strlen(data_s);
    char* file_name = argv[3];
    #endif
    FILE* target_file;

    target_file = fopen(file_name, "r+"); 
	if(target_file == NULL){
		printf("Failed to open file...\n");
		return 0;
	}
    fseek(target_file, 0 ,SEEK_END);
    int file_end = ftell(target_file);
    fseek(target_file, 0 ,SEEK_SET);
    int file_start = ftell(target_file);
    int file_size =  file_end - file_start;

    char buf_1[1];
    char buf_2[1];

    for(int i=0; i<data_len; i++){
        fseek(target_file, offset, SEEK_SET);
        fread(buf_1,sizeof(char), 1, target_file);
        while(1){
            if(ftell(target_file) >= file_size+i){
                fwrite(buf_1,1,1,target_file);
                break;
            }
            fread(buf_2,sizeof(char), 1, target_file);
            fseek(target_file,-1,SEEK_CUR);
            fwrite(buf_1,1,1,target_file);
            buf_1[0] = buf_2[0];
            fseek(target_file,0,SEEK_CUR);
        }
    }

    fseek(target_file, offset+1,SEEK_SET);
    fwrite(data_s,sizeof(char),strlen(data_s),target_file);
    
    fclose(target_file);
    return 0;
}
