// #define DEBUG
#include <stdio.h>
#include <sys/time.h>

//�ʿ��ϸ� header file �߰� ����


//
// input parameters: ���ڵ� ����
//
float time_diff(struct timeval *start, struct timeval *end){
    return (end->tv_sec - start->tv_sec) + 1e-6*(end->tv_usec - start->tv_usec);
}

int main(int argc, char **argv){
	// ���ڵ� ���Ϸκ��� ��ü ���ڵ带 ���������� �о���̰�, �̶�
	// �ɸ��� �ð��� �����ϴ� �ڵ� ����
	FILE* target_file;
	char* file_name;
	#ifdef DEBUG
	file_name = "test_case_01.txt";
	#endif

	#ifndef DEBUG
	file_name = argv[1];	
	#endif

	struct timeval startTime, endTime;
	double diffTime;

	gettimeofday(&startTime, NULL);

	target_file = fopen(file_name, "r");
	if(target_file == NULL){
		printf("error!!");
		return 0;
	}

	char curr_c;
	curr_c = getc(target_file);
	while (curr_c != EOF){
		curr_c = getc(target_file);
		#ifdef DEBUG
		printf("%c",curr_c);
		#endif
	}

	gettimeofday(&endTime, NULL);
	printf("%0.4f usec\n", time_diff(&startTime,&endTime)*1000.0);

	return 0;
}
