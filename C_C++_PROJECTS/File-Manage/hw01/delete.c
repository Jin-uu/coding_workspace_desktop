// #define DEBUG
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    FILE* target_file;
    int offset;
    int byte_num;
    char* file_name;

    #ifdef DEBUG
    offset = 7;
    byte_num = -4;
    file_name = "testFile3.txt";
    #endif
    #ifndef DEBUG
    offset = atoi(argv[1]);
    byte_num = atoi(argv[2]);
    file_name = argv[3];
    #endif


    target_file = fopen(file_name,"r+");
	if(target_file == NULL){
		printf("Failed to open file...\n");
		return 0;
	}

    int del_start;
    int del_end;

    if(byte_num == 0 ){
        fclose(target_file);
        return 0;
    }

    fseek(target_file,0,SEEK_SET);
    int file_start = ftell(target_file);
    fseek(target_file,0,SEEK_END);
    int file_end = ftell(target_file);
    int file_size = file_end - file_start;

    if(byte_num < 0 ){
        del_start = offset + byte_num;
        if(del_start < 0) del_start = 0;
        del_end = offset - 1;
        if(del_end < del_start) return 0;
    }
    else{
        del_start = offset +1;
        if(del_start > file_size) return 0;
        del_end = offset + byte_num;
        if(del_end > file_size) del_end = file_size;
    }

    #ifdef DEBUG
    printf("file_size : %d\n", file_size);
    printf("del_start : %d\n", del_start);
    printf("del_end :   %d\n", del_end);
    #endif

    char buf[1];
    char curr_loc=0;
    for(int i=del_end+1; i<file_size; i++){
        fseek(target_file,i,SEEK_SET);
        fread(buf, sizeof(char), 1, target_file);
        fseek(target_file,del_start+curr_loc,SEEK_SET);
        fwrite(buf,sizeof(char),1,target_file);
        curr_loc++;
    }

    truncate(file_name,file_size - (del_end - del_start+1));

    return 0;
}
