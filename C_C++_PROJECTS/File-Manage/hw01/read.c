#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


int main(int argc, char *argv[]){
	FILE* original_file;		// 대상 파일
    int offset = atoi(argv[1]);
    int byte_num = atoi(argv[2]);
    

	original_file = fopen(argv[3], "r");		// 대상파일 오픈
	if(original_file == NULL){
		printf("파일을 여는데 실패했습니다. 종료합니다.\n");
		return 0;
	}

    int read_start, read_end;
    if(byte_num == 0){
        fclose(original_file);
        return 0;
    }
    if(byte_num < 0 ){
        read_start = offset + byte_num;
        if(read_start < 0) read_start = 0;
        read_end = offset - 1;
        if(read_end < read_start) return 0;
    }
    int curr_cnt=0;
    if(byte_num == 0) return 0;             // 바이트 수가 0일 경우
    if(byte_num < 0){                       // 바이트 수가 음수일 경우
        fseek(original_file, read_start, SEEK_SET);
        for(int i=0; i<=read_end - read_start; i++){
            char c = getc(original_file);
            putchar(c);
        }
    }
    else{                                   // 바이트 수가 양수일 경우
        fseek(original_file, offset, SEEK_CUR);
        char c = getc(original_file);
        for(int i=0; i<abs(byte_num); i++){
            c = getc(original_file);
            if(c==EOF) break;
            putchar(c);
        }
    }

    printf("\n");

	fclose(original_file);		// 대상파일 닫음
	return 0;
}
