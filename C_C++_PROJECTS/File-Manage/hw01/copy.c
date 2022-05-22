#include <stdio.h>
#include <string.h>


int main(int argc, char *argv[]){
	FILE* copy_file;			// 복사할 파일
	FILE* original_file;		// 원본 파일

	original_file = fopen(argv[1], "r");		// 원본파일 오픈
	if(original_file == NULL){
		printf("파일을 여는데 실패했습니다. 종료합니다.\n");
		return 0;
	}

	copy_file = fopen(argv[2],"w+");			// 생성파일 오픈
	if(copy_file == NULL){
		printf("파일을 생성하는데 실패했습니다. 종료합니다.\n");
		fclose(original_file);
		return 0;		
	}

	char buffer[11];		// 10바이트씩 복사할 때 쓸 임시 공간

	while(feof(original_file)==0){
		fread(buffer,sizeof(char),10,original_file);		// 10바이트씩 읽어서
		fwrite(buffer, strlen(buffer),1,copy_file);			// 생성한 파일에 씀
		memset(buffer,0,11);								// 메모리초기화
	}

	fclose(original_file);		// 원본파일 닫음
	fclose(copy_file);			// 생성파일 닫음

	return 0;
}
