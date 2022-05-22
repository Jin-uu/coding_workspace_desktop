#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// #define DEBUG
// �ʿ��ϸ� header ���� �߰� ����

//
// input parameters: �л� ���ڵ� ��, ���ڵ� ����
// a.out <#records> <record_file_name>
int main(int argc, char **argv) {
	int records_num;
	char* file_name;	
	FILE* new_file;

	#ifdef DEBUG
	records_num = 3;
	file_name = "test_case_00.txt";
	#endif

	#ifndef DEBUG
	records_num = atoi(argv[1]);
	file_name = argv[2];	
	#endif
	
	new_file = fopen(file_name, "w+");
	if(new_file == NULL){
		printf("error!\n");
		return 0;
	}

	char* buffer;
	buffer = "1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789/";
	
	for (int i = 0; i < records_num; i++){
		fwrite(buffer, sizeof(char), 200, new_file);
	}	

	// ����ڷκ��� �Է� ���� ���ڵ� �� ��ŭ�� ���ڵ� ������ �����ϴ� �ڵ� ����
	
	// ���Ͽ� '�л� ���ڵ�' ������ �� ���� ����
	// 1. ���ڵ��� ũ��� ������ 200 ����Ʈ�� �ؼ�
	// 2. ���ڵ� ���Ͽ��� ���ڵ�� ���ڵ� ���̿� � �����͵� ���� �ȵ�
	// 3. ���ڵ忡�� ������ �����͸� �����ص� ����
	// 4. ���� n���� ���ڵ带 �����ϸ� ���� ũ��� ��Ȯ�� 200 x n ����Ʈ�� �Ǿ�� ��

	return 0;
}