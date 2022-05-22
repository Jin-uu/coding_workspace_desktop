#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){
    int offset = atoi(argv[1]);
    char* data_s = strtok(argv[2],"\"");
    FILE* target_file;

    target_file = fopen(argv[3],"r+");    
	if(target_file == NULL){
		printf("Failed to open file...\n");
		return 0;
	}

    fseek(target_file,offset,SEEK_CUR);
    fwrite(argv[2],sizeof(char),strlen(data_s),target_file);

    fclose(target_file);

    return 0;
}
