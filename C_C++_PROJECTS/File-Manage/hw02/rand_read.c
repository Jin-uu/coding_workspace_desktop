// #define DEBUG

#include <stdio.h>
#include <sys/types.h>
#include <time.h>
#include <stdlib.h>
#include <sys/time.h>
//필요하면 header file 추가 가능


#define SUFFLE_NUM	10000	// 이 값은 마음대로 수정 가능

void GenRecordSequence(int *list, int n);
void swap(int *a, int *b);
// 필요한 함수가 있으면 더 추가할 수 있음

//
// input parameters: 레코드 파일
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

	// 이 함수를 실행하면 'read_order_list' 배열에 읽어야 할 레코드 번호들이 순서대로
	// 나열되어 저장됨. 'num_of_records'는 레코드 파일에 저장되어 있는 전체 레코드의 수를 의미함.
	GenRecordSequence(read_order_list, num_of_records);

	// 'read_order_list'를 이용하여 레코드 파일로부터 전체 레코드를 random 하게 읽어들이고,
	// 이때 걸리는 시간을 측정하는 코드 구현
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