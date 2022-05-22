// #define DEBUG

#include <stdio.h>
#include <sys/types.h>
#include <time.h>
#include <stdlib.h>
#include <sys/time.h>
//�ʿ��ϸ� header file �߰� ����


#define SUFFLE_NUM	10000	// �� ���� ������� ���� ����

void GenRecordSequence(int *list, int n);
void swap(int *a, int *b);
// �ʿ��� �Լ��� ������ �� �߰��� �� ����

//
// input parameters: ���ڵ� ����
//
float time_diff(struct timeval *start, struct timeval *end){
    return (end->tv_sec - start->tv_sec) + 1e-6*(end->tv_usec - start->tv_usec);
}

int main(int argc, char **argv){
	int *read_order_list;
	int num_of_records;
	char *file_name;
	FILE *target_file;

	#ifdef DEBUG
	file_name = "test_case_00.txt";
	#endif
	#ifndef DEBUG
	file_name = argv[1];
	#endif

	target_file = fopen(file_name,"r");
	if(target_file == NULL){
		printf("error!\n");
		return 0;
	}

	int file_start, file_end, file_size;
	fseek(target_file,0,SEEK_SET);
	file_start = ftell(target_file);
	fseek(target_file,0,SEEK_END);
	file_end = ftell(target_file);
	file_size = file_end - file_start;

	read_order_list = malloc(sizeof(int)*file_size);
	num_of_records = file_size;

	// �� �Լ��� �����ϸ� 'read_order_list' �迭�� �о�� �� ���ڵ� ��ȣ���� �������
	// �����Ǿ� �����. 'num_of_records'�� ���ڵ� ���Ͽ� ����Ǿ� �ִ� ��ü ���ڵ��� ���� �ǹ���.
	GenRecordSequence(read_order_list, num_of_records);

	// 'read_order_list'�� �̿��Ͽ� ���ڵ� ���Ϸκ��� ��ü ���ڵ带 random �ϰ� �о���̰�,
	// �̶� �ɸ��� �ð��� �����ϴ� �ڵ� ����
	struct timeval startTime, endTime;
	double diffTime;

	gettimeofday(&startTime, NULL);

	int cnt=0;
	for (int i = 0; i < file_size; i++){
		fseek(target_file,read_order_list[i],SEEK_SET);
		char cur_c = getc(target_file);
		#ifdef DEBUG
		cnt++;
		printf("%c ",cur_c);
		#endif
	}
	#ifdef DEBUG
	printf("\n%d \n",cnt);
	#endif

	gettimeofday(&endTime, NULL);
	printf("%0.4f usec\n", time_diff(&startTime,&endTime)*1000.0);
	

	return 0;
}

void GenRecordSequence(int *list, int n)
{
	int i, j, k;

	srand((unsigned int)time(0));

	for(i=0; i<n; i++)
	{
		list[i] = i;
	}
	
	for(i=0; i<SUFFLE_NUM; i++)
	{
		j = rand() % n;
		k = rand() % n;
		swap(&list[j], &list[k]);
	}

	return;
}

void swap(int *a, int *b)
{
	int tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;

	return;
}