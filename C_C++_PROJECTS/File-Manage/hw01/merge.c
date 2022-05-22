#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[]) {
    FILE* original_file_01;     // 파일 1
    FILE* original_file_02;     // 파일 2
    FILE* new_file;             // 합친 결과물 파일

    original_file_01 = fopen(argv[1], "r");		// 대상파일 오픈
	if(original_file_01 == NULL){
		printf("파일1을 여는데 실패했습니다. 종료합니다.\n");
		return 0;
	}
    original_file_02 = fopen(argv[2], "r");		// 대상파일 오픈
	if(original_file_02 == NULL){
		printf("파일2를 여는데 실패했습니다. 종료합니다.\n");
        fclose(original_file_01);
        return 0;
	}

    new_file = fopen(argv[3],"w+");			    // 파일 생성
	if(new_file == NULL){
		printf("파일을 생성하는데 실패했습니다. 종료합니다.\n");
		fclose(original_file_01);
		fclose(original_file_02);
		return 0;		
	}

    char buffer[11];		// 10바이트씩 복사할 때 쓸 임시 공간

	while(feof(original_file_01)==0){
		fread(buffer,sizeof(char),10,original_file_01);		// 10바이트씩 읽어서
		fwrite(buffer, strlen(buffer),1,new_file);			// 생성한 파일에 씀
		memset(buffer,0,11);								// 메모리초기화
	}

	while(feof(original_file_02)==0){
		fread(buffer,sizeof(char),10,original_file_02);		// 10바이트씩 읽어서
		fwrite(buffer, strlen(buffer),1,new_file);			// 생성한 파일에 씀
		memset(buffer,0,11);								// 메모리초기화
	}

    fclose(original_file_01);
    fclose(original_file_02);
    fclose(new_file);
    
    return 0;
}
