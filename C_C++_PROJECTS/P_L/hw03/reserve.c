#define DEBUG
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>        // write(), close(), ftruncate()
#include <io.h>

// �ʵ� ũ�� ���
#define SIZE_BRANCH_ABLE 6
#define SIZE_ROOM_ABLE 5
#define SIZE_ROOM_CAPACITY 10
#define SIZE_RESERVE_CNT 10
#define SIZE_USER_ID 10
#define SIZE_RESERVED_DATE 4
#define SIZE_RESERVED_TIME 4
#define SIZE_USING_TIME 4
#define SIZE_RESERVE 24
#define SIZE_ROOM_INFO_FILE_NAME 26
// �ִ밪 ���
const int BRANCH_NUM = 6;
const int MAX_ROOM_NUM = 5;

typedef struct _RESERVE{
    char user_id[10];
    int reserved_date;
    int reserved_time;
    int using_time;
} RESERVE;

// #define branch_format "./branch_%d_info.dat"
#define room_format "./branch_%d_room_%d_info.dat"

// ���ϸ�
char BRANCH_INFO_FILE_NAME[] = "./branch_info.dat";
char BRANCH_1_INFO[] = "./branch_1_info.dat";
char BRANCH_2_INFO[] = "./branch_2_info.dat";
char BRANCH_3_INFO[] = "./branch_3_info.dat";
char BRANCH_4_INFO[] = "./branch_4_info.dat";
char BRANCH_5_INFO[] = "./branch_5_info.dat";
char BRANCH_6_INFO[] = "./branch_6_info.dat";

char branch_able_char[6] = {'a','a','a','a','a','a'};
bool branch_able_arr[6];
char room_able_char[SIZE_ROOM_ABLE] = {'i','i','i','i','i'};          // curr�� ������ room ���� ����
bool room_able_arr[5];
char  room_capacity_char[SIZE_ROOM_CAPACITY] = {'i','i','i','i','i','i','i','i','i','i'};      // ���� ������ room�� �ִ��ο� ����
int room_capacity_arr[5];
char  room_reserve_cnt_char[SIZE_RESERVE_CNT] = {'i','i','i','i','i','i','i','i','i','i'};        // ���� ������ room�� ���� ���� ����
int room_reserve_cnt_arr[5];
// input func
int  get_user_input(void);                      // ����� �Է� �ޱ�
void wrong_input(void);                         // �Է� ������
void exit_program(void);                        // ���α׷� ����
//          
void mode_selection(void);                      // �ʱ� ��� ���� ȭ��
// admin        
void mode_admin(void);                          // ������ ��� �ʱ� ȭ��
void mode_add_branch(int);                      // ���� �߰� ���
void mode_mod_branch(int);                      // ���� ���� ���
void mode_del_branch(int);                      // ���� ���� ���
void mode_add_room(int, int);                   // ���͵� �� �߰� ���
void mode_mod_room(int, int);                   // ���͵� �� ���� ���
void mode_del_room(int, int);                   // ���͵� �� ���� ���

// user 
void mode_user(void);                           // ����� ��� �ʱ� ȭ��
// file manage  
void open_file(FILE**, char*);                      // ���� ����
void get_branch_able_info(void);                    // ���� ���� ���� ���� �ҷ�����
void get_branch_info(int);                          // Ư�� ���� ���� �ҷ��ͼ� �迭�� ����
bool is_file_empty(FILE*);                          // ������ ����ִ��� �˻�
void init_branch_able_info(FILE*);                  // branch_able_info.dat �ʱ�ȭ
void init_branch_info(int);                         // branch_n_info.dat �ʱ�ȭ
void init_room_info(int,int);                       // branch_n_room_n_info.dat �ʱ�ȭ
void set_branch_able_info(char[]);                  // branch_able_info.dat ���� ���� ���� ����
void set_room_able_info(char[],int);                // branch_n_info.dat ���͵� �� ���� ���� ����
void set_room_capacity_info(char[], int);           // branch_n_info.dat ���͵� �� �ִ��ο� ����
void set_room_reserve_cnt_info(char[], int);        // branch_n_info.dat ���͵� �� ���� ���� ����
void delete_file(char[]);                           // ���� ����
void read_reserve(int, int, int, RESERVE*);         // n������ n�� �� n��° ���� �о����
void write_reserve(int, int, int, RESERVE*);        // n������ n�� �� n��° ���� ����
void delete_reserve(int, int, int, RESERVE*);       // n������ n�� �� n��° ���� �����
// translate
char* get_branch_file_name(int);                    // ���� ��ȣ�ָ� ���ϸ� ��ȯ
// FILE* get_file_pointer_with_num(int);               // ���� ��ȣ�ָ� ���������� ��ȯ
char* get_room_file_name(int, int);                 // n�� ������ n�� ���͵�� ���ϸ� ��ȯ



int main(void){
    while(1) mode_selection();
    // RESERVE* r = (RESERVE* )malloc(sizeof(RESERVE));

    // strcpy(r->user_id, "user_id");
    // r->reserved_date = 220515;
    // r->reserved_time = 15;
    // r->using_time = 2;

    // write_reserve(1,2,0,r);
    // read_reserve(1,2,0,r);
    // printf("%s,%d,%d,%d\n",r->user_id, r->reserved_date,r->reserved_time,r->using_time);

    // strcpy(r->user_id, "user_id2");
    // r->reserved_date = 220516;
    // r->reserved_time = 13;
    // r->using_time = 3;
    
    // write_reserve(1,2,1,r);
    // read_reserve(1,2,1,r);
    // printf("%s,%d,%d,%d\n",r->user_id, r->reserved_date,r->reserved_time,r->using_time);

    return 0;
}

int get_user_input(void){
    int input;
    scanf("%d", &input);
    return input;
}

void wrong_input(void){
    printf(">> �ùٸ��� ���� �Է��Դϴ�...\n");
    exit_program();
}

void exit_program(void){
    printf(">> ���α׷��� �����մϴ�...\n");
    exit(0);
}


// �ʱ� ��� ���� ȭ��
void mode_selection(void){
    printf("------------<��� ����>------------\n");
    printf("        1. ������ ��� (1)\n");
    printf("        2. ����� ��� (2)\n");
    printf("        3. ���α׷� ���� (0)\n");
    printf("-----------------------------------\n");
    printf("��带 �����ϼ���.\n>> ");
    switch(get_user_input()){
        case 1:
            mode_admin();
            break;
        case 2:
            // mode_user();
            break;
        case 0:
            exit_program();
            break;
        default:
            wrong_input();            
    }
}

// ������ ��� �ʱ� ȭ��
void mode_admin(void){
    get_branch_able_info();                  // branch_able_char �� ���� ����
    printf("--------<������ ���>--------\n");
    printf("---------<���� ��Ȳ>---------\n");
    for (int i = 1; i <= BRANCH_NUM; i++) {
        printf("    ���� %d", i);
        if(branch_able_arr[i-1]){                  // ���� ���� �Ǿ�����
            printf(" (������)\n");
        }
        else { printf(" (�������� ����)\n"); }  // ���� �����̸�
    }
    printf("���α׷� ���� : (0)\n");
    printf("-----------------------------\n");
    printf("������ �����ϼ���.\n>> ");          // �������� �Է� �ޱ�
    int input_branch_selection = get_user_input();
    if(input_branch_selection == 0) exit_program();
    printf("���� %d�� ���� �۾��� �����ϼ���.\n", input_branch_selection);   // ���õ� ������ ���� �۾� �Է� �ޱ�
    printf(" (1) �߰�    (2) ����    (3) ����   (4) ���α׷� ����\n");
    printf(">> ");
    switch(get_user_input()){
        case 1:
            mode_add_branch(input_branch_selection);
            break; 
        case 2:
            mode_mod_branch(input_branch_selection);
            break;
        case 3:
            mode_del_branch(input_branch_selection);
            break;
        case 4:
            exit_program();
            break;
        default:
            wrong_input();
    }
}     

// ���� �߰� ���
void mode_add_branch(int branch_num){
    if(branch_able_arr[branch_num-1]){          // �̹� ���� �� �������� �˻�
        printf(">> �̹� ������ �����Դϴ�.\n");
        return;
    }
    // �������� ���� �����̸�
    branch_able_char[branch_num-1] = '1';
    set_branch_able_info(branch_able_char);
    FILE* fp;
    open_file(&fp, get_branch_file_name(branch_num));
    fclose(fp);
    printf("���� %d�� �����߽��ϴ�.\n", branch_num);
}

// ���� ���� ���
void mode_mod_branch(int branch_num){
    if(!branch_able_arr[branch_num-1]){          // ���� ���� Ȯ��
        printf(">> ���� �������� ���� �����Դϴ�.\n");
        return;
    }
    get_branch_info(branch_num);
    printf("---------<����%d ��Ȳ>---------\n", branch_num);
    for (int i = 1; i <= MAX_ROOM_NUM; i++) {
        printf("    ���͵� �� %d", i);
        if(room_able_arr[i-1]){                     // ���͵� �� ���� �Ǿ�����
            printf("(����ο�: %d, ���� ��Ȳ: %d��)\n",room_capacity_arr[i-1],room_reserve_cnt_arr[i-1]);
        }
        else { printf(" (�������� ����)\n"); }      // ���� �����̸�
    }
    printf("���α׷� ���� : (0)\n");
    printf("-----------------------------\n");
    printf("�۾��� ���͵� �� ��ȣ�� �����ϼ���.\n>> ");    // ���͵�� ��ȣ �Է� �ޱ�
    int input_room_selection = get_user_input();
    if(input_room_selection == 0) exit_program();
    if(input_room_selection<0 || input_room_selection>5) wrong_input();

    printf(">>���͵� �� %d�� ���� �۾��� �����ϼ���.\n", input_room_selection);   // ���õ� ������ ���� �۾� �Է� �ޱ�
    printf(" (1) �߰�    (2) ����    (3) ����   (4) ���α׷� ����\n");
    printf(">> ");
    switch(get_user_input()){
        case 1:
            mode_add_room(branch_num, input_room_selection);
            break;  
        case 2:
            mode_mod_room(branch_num, input_room_selection);
            break;
        case 3:
            mode_del_room(branch_num, input_room_selection);
            break;
        case 4:
            exit_program();
            break;
        default:
            wrong_input();
    }

}
// ���͵� �� �߰� ���
void mode_add_room(int branch_num, int room_num){
    if(room_able_arr[room_num-1]){          // �̹� ���� �� ���͵� ������ �˻�
        printf(">> �̹� ������ ���͵� ���Դϴ�.\n");
        return;
    }
    // �������� ���� �����̸�
    printf(">> ���͵� �� %d�� �ִ� ��� �ο��� �Է��ϼ���.(1~10)\n>>",room_num);
    int max_capacity = get_user_input();
    char ten, one;
    if(max_capacity>10 || max_capacity < 1){
        wrong_input();
    }
    else if(max_capacity == 10){
        ten = '1'; one = '0';
    }
    else{
        ten = '0'; one = max_capacity+'0';
    }

    room_able_char[room_num-1] = '1';
    room_capacity_char[(room_num-1)*2] = ten; room_capacity_char[(room_num-1)*2+1] = one;
    room_reserve_cnt_char[(room_num-1)*2] = '0'; room_reserve_cnt_char[(room_num-1)*2+1] = '0';
    set_room_able_info(room_able_char, branch_num);
    set_room_capacity_info(room_capacity_char,branch_num);
    set_room_reserve_cnt_info(room_reserve_cnt_char,branch_num);
    
    char* filename = (char*)malloc(28);
    sprintf(filename, room_format, branch_num, room_num);
    FILE* temp_fp;      
    open_file(&temp_fp, filename);
    fclose(temp_fp);
    printf("���͵� �� %d�� �����߽��ϴ�.\n", room_num);
}            
// ���͵� �� ���� ���
void mode_mod_room(int branch_num, int room_num){
    if(!room_able_arr[room_num-1]){          // ���� �� �������� �˻�
        printf(">> �������� ���� ���͵� ���Դϴ�.\n");
        return;
    }
    printf(">> ���͵� �� %d�� ������ �ִ� �ο� ���� �Է��ϼ���. (���� : %d)\n>>",room_num,room_capacity_arr[room_num]);
    int max_capacity = get_user_input();
    char ten,one;
    if(max_capacity>10 || max_capacity < 1){
        wrong_input();
    }
    else if(max_capacity == 10){
        ten = '1'; one = '0';
    }
    else{
        ten = '0'; one = max_capacity+'0';
    }
    room_capacity_char[(room_num-1)*2] = ten; room_capacity_char[(room_num-1)*2+1] = one;
    set_room_capacity_info(room_capacity_char, branch_num);
}             
// ���͵� �� ���� ���
void mode_del_room(int branch_num, int room_num){
    if(!room_able_arr[room_num-1]){          // �̹� ���� �� �������� �˻�
        printf(">> �̹� ������ ���͵� ���Դϴ�.\n");
        return;
    }

    // branch_%d_info.dat. �ʱ�ȭ
    room_able_char[room_num-1] = '0';
    room_capacity_char[room_num-1] = '0';
    room_reserve_cnt_char[room_num-1] = '0';
    set_room_able_info(room_able_char, branch_num);
    set_room_capacity_info(room_capacity_char, branch_num);
    set_room_reserve_cnt_info(room_reserve_cnt_char,branch_num);
    // branch_%d_room_%d_info.dat ����
    char* filename = (char*)malloc(28);
    sprintf(filename, room_format, branch_num, room_num);            
    delete_file(filename);
    printf("���͵� �� %d�� �����߽��ϴ�.\n", room_num);
}                 

// ���� ���� ���
void mode_del_branch(int branch_num){
    if(!branch_able_arr[branch_num-1]){          // �̹� ���� �� �������� �˻�
        printf(">> �̹� ������ �����Դϴ�.\n");
        return;
    }

    branch_able_char[branch_num-1] = '0';
    set_branch_able_info(branch_able_char);
    // branch_%d_room_%d_info.dat ����
    get_branch_info(branch_num);
    for (int i = 0; i < 6; i++) {
        if(room_able_arr[i]){
            char* filename = (char*)malloc(28);
            sprintf(filename, room_format, branch_num, i+1);            
            delete_file(filename);
        }
    }
    // branch_%d_info.dat ����
    delete_file(get_branch_file_name(branch_num));
    
    printf("���� %d�� �����߽��ϴ�.\n", branch_num);
}

// ����� ��� �ʱ� ȭ��
void mode_user(void){

}

void open_file(FILE** filestream, char filename[]){
    FILE* check_file_exist = fopen(filename,"r");   // ���ڷ� ���� ���� ���� �õ�
    if(check_file_exist == NULL){                   // ������ ������
        check_file_exist = fopen(filename, "w+");   // ���� ����
        fclose(check_file_exist);                   // ������ ���� �ݱ�
    }
    else{ fclose(check_file_exist); }

    *filestream = fopen(filename,"r+");     // ���� ����
    if(filestream == NULL){                 // �� ���ȴ��� �˻�
        printf("ERROR open_file() (file name: \"%s\")\n",filename);
        exit(1);
    }
}

// ���� ���� �ҷ�����
void get_branch_able_info(void){
    FILE* fp;
    open_file(&fp ,BRANCH_INFO_FILE_NAME);         // ���� ����
    if(is_file_empty(fp)){                         // ������ ���������
        init_branch_able_info(fp);                 // �ʱ�ȭ (���� ����)
        open_file(&fp ,BRANCH_INFO_FILE_NAME);     // ���� ����
    }
    
    fseek(fp, 0, SEEK_SET);            // ���� ������ ������ ����
    fread(branch_able_char,strlen(branch_able_char), sizeof(char),fp);   // �б�
    for (int i = 0; i < 6; i++) {
        if(branch_able_char[i] == '0'){             // char ������ bool �� �迭�� ��ȯ
            branch_able_arr[i] = false;          
        }
        else { branch_able_arr[i] = true; }
    }

    fclose(fp);                        // ���� �� �а� ���� �ݱ�
}

// ������ ����ִ��� �˻�
bool is_file_empty(FILE *filestream){
    fseek(filestream, 0, SEEK_END);
    int file_size = ftell(filestream);

    if(file_size < 1) return true;          // ���� �����
    return false;                           // ���� �Ⱥ����
}

// branch_able_info.txt. �ʱ�ȭ
void init_branch_able_info(FILE* filestream){
    char branch_able_info_init_string[] = "000000";
    if(fwrite(branch_able_info_init_string, strlen(branch_able_info_init_string), sizeof(char),filestream) < 1){
        printf("error in init branch able info!\n");
        exit(1);
    }
    fclose(filestream);               // ���� �ݾƼ� ����
}

void init_branch_info(int branch_num){
    FILE* fp;
    open_file(&fp , get_branch_file_name(branch_num));
    char branch_info_room_able_init_string[] ="00000";
    char branch_info_room_capacity_init_string[] ="0000000000";
    char branch_info_room_reserve_cnt_init_string[] ="0000000000";
    set_room_able_info(branch_info_room_able_init_string,branch_num);
    set_room_capacity_info(branch_info_room_capacity_init_string,branch_num);
    set_room_reserve_cnt_info(branch_info_room_reserve_cnt_init_string,branch_num);
    fseek(fp,0,SEEK_SET);
    if(fwrite(branch_info_room_able_init_string,strlen(branch_info_room_able_init_string), sizeof(char), fp) <1){
        printf("branch info init error(room_able_char)!\n");
        exit(1);
    }
    fseek(fp,SIZE_ROOM_ABLE,SEEK_SET);
    if(fwrite(branch_info_room_capacity_init_string,strlen(branch_info_room_capacity_init_string), sizeof(char), fp) <1){
        printf("branch info init error(room_capacity)!\n");
        exit(1);
    }
    fseek(fp,SIZE_ROOM_ABLE + SIZE_ROOM_CAPACITY,SEEK_SET);
    if(fwrite(branch_info_room_reserve_cnt_init_string,strlen(branch_info_room_reserve_cnt_init_string), sizeof(char), fp) <1){
        printf("branch info init error(room_reserve_cnt)!\n");
        exit(1);
    }
    fclose(fp);
}
// branch_n_room_n_info.dat ����
void init_room_info(int branch_num,int room_num){
    char* filename = (char*)malloc(SIZE_ROOM_INFO_FILE_NAME);
    sprintf(filename, room_format, branch_num, room_num);
    FILE* fp;
    open_file(&fp,filename);
    fclose(fp);
}                       

void get_branch_info(int branch_num){
    FILE* fp;    
    open_file(&fp ,get_branch_file_name(branch_num));         // ���� ����
    if(is_file_empty(fp)){                                    // ������ ���������
        init_branch_info(branch_num);                         // �ʱ�ȭ (���� ����)
        // open_file(&fp ,get_branch_file_name(branch_num));     // ���� ����
    }
    
    fseek(fp, 0, SEEK_SET);            // ���� ������ ������ ����
    fread(room_able_char,strlen(room_able_char), sizeof(char),fp);   // �б�    
    fseek(fp, SIZE_ROOM_ABLE, SEEK_SET);            // ���� ������ ������ ����
    fread(room_capacity_char,strlen(room_capacity_char), sizeof(char),fp);   // �б�    
    fseek(fp, SIZE_ROOM_ABLE + SIZE_ROOM_CAPACITY, SEEK_SET);            // ���� ������ ������ ����
    fread(room_reserve_cnt_char,strlen(room_reserve_cnt_char), sizeof(char),fp);   // �б�
    // printf("ra:%s\nrc:%s\nrcnt:%s\n", room_able_char, room_capacity_char, room_reserve_cnt_char);

    printf("room_able_arr[]: ");
    for (int i = 0; i < 5; i++) {
        if(room_able_char[i] == '0') room_able_arr[i] = false;
        else room_able_arr[i] = true;
        printf("%d ", room_able_arr[i]);
    }
    printf("\nroom_capacity_arr[]: ");
    for (int i = 0; i < 5; i++) {
        room_capacity_arr[i] = (room_capacity_char[i*2] - '0')*10 + (room_capacity_char[i*2+1] - '0');
        printf("%d ", room_capacity_arr[i]);
    }
    printf("\nreserve_cnt_arr[]: ");
    for (int i = 0; i < 5; i++) {
        room_reserve_cnt_arr[i] = (room_reserve_cnt_char[i*2] - '0')*10 + (room_reserve_cnt_char[i*2+1] - '0');
        printf("%d ", room_reserve_cnt_arr[i]);
    }
    printf("\n");
    fclose(fp);
}

// branch_able_info.txt ����
void set_branch_able_info(char new_branch_info[]){
    FILE* fp;
    open_file(&fp ,BRANCH_INFO_FILE_NAME);         // brnach_info.txt ���� ����
    if(fwrite(new_branch_info, strlen(new_branch_info), sizeof(char),fp) < 1){
        printf("error in set branch able info!\n");
        exit(1);
    }
    fclose(fp);               // ���� �ݾƼ� ����
}  
// branch_n_info.dat ����
void set_room_able_info(char new_room_info[], int branch_num){
    FILE* fp;
    open_file(&fp, get_branch_file_name(branch_num));
    if(fwrite(new_room_info, strlen(new_room_info), sizeof(char),fp) < 1){
        printf("error in set room able info!\n");
        exit(1);
    }
    fclose(fp);               // ���� �ݾƼ� ����
}

void set_room_capacity_info(char new_room_capacity_info[], int branch_num){
    FILE* fp;
    open_file(&fp, get_branch_file_name(branch_num));
    fseek(fp, SIZE_ROOM_ABLE, SEEK_SET);
    if(fwrite(new_room_capacity_info, strlen(new_room_capacity_info), sizeof(char),fp) < 1){
        printf("error in set room capacity info!\n");
        exit(1);
    }
    fclose(fp);               // ���� �ݾƼ� ����
}

void set_room_reserve_cnt_info(char new_room_reserve_cnt_info[], int branch_num){
    FILE* fp;
    open_file(&fp, get_branch_file_name(branch_num));
    fseek(fp, SIZE_ROOM_ABLE+SIZE_ROOM_CAPACITY, SEEK_SET);
    if(fwrite(new_room_reserve_cnt_info, strlen(new_room_reserve_cnt_info), sizeof(char),fp) < 1){
        printf("error in set room reserve_cnt info!\n");
        exit(1);
    }
    fclose(fp);               // ���� �ݾƼ� ����
}
// ���� ����
void delete_file(char filename[]){
    if(remove(filename)==0){
        return;
    }
    else{
        printf("error in remove file(%s)\n", filename);
        exit(1);
    } 

}                
// n������ n�� �� n��° ���� �о����
void read_reserve(int branch_num, int room_num, int rnn, RESERVE* r){
    FILE* fp;
    char* filename = (char*) malloc(SIZE_ROOM_INFO_FILE_NAME);
    sprintf(filename,room_format,branch_num, room_num);
    open_file(&fp,filename);
    fseek(fp, SIZE_RESERVE*rnn,SEEK_SET);
    fread(r, SIZE_RESERVE, 1, fp);
    free(filename);
    fclose(fp);
}                
// n������ n�� �� n��° ���� ����  
void write_reserve(int branch_num, int room_num, int rnn, RESERVE* r){
    FILE* fp;
    char* filename = (char*) malloc(SIZE_ROOM_INFO_FILE_NAME);
    sprintf(filename,room_format,branch_num, room_num);
    open_file(&fp,filename);
    fseek(fp, SIZE_RESERVE*rnn,SEEK_SET);
    fwrite(r, SIZE_RESERVE, 1, fp);
    free(filename);
    fclose(fp);
}      
// n������ n�� �� n��° ���� �����
void delete_reserve(int branch_num, int room_num, int rnn, RESERVE* r){
    FILE* fp;
    char* filename = (char*)malloc(SIZE_ROOM_INFO_FILE_NAME);
    sprintf(filename, room_format, branch_num, room_num);
    open_file(&fp,filename);
    get_branch_info(branch_num);
    int reserve_cnt = room_reserve_cnt_arr[room_num];
    RESERVE r;
    read_reserve(branch_num,room_num, (reserve_cnt-1), &r);
    write_reserve(branch_num,room_num, rnn, &r);

    //TODO : reserve cnt -- ����
    fclose(fp);
    free(filename);
}

int get_file_size(char filename[]){
    FILE* fp;
    fopen(fp, filename);
    int size = fseek(fp, 0, SEEK_END);
    fclose(fp);
    return size;
}

// ���� ��ȣ�ָ� ���ϸ� ��ȯ
char* get_branch_file_name(int branch_num){
    switch(branch_num){
        case 1:
            return BRANCH_1_INFO;
        case 2:
            return BRANCH_2_INFO;
        case 3:
            return BRANCH_3_INFO;
        case 4:
            return BRANCH_4_INFO;
        case 5:
            return BRANCH_5_INFO;
        case 6:
            return BRANCH_6_INFO;
    }
}

// n�� ������ n�� ���͵�� ���ϸ� ��ȯ
char* get_room_file_name(int branch_num, int room_num){
    char* file = (char*)malloc(sizeof(char)*30);
    sprintf(file,room_format, branch_num, room_num);
    return file;
}

// ���� ��ȣ�ָ� ���������� ��ȯ
// FILE* get_file_pointer_with_num(int branch_num){
//     switch(branch_num){
//         case 1:
//             return branch_1_info;
//         case 2:
//             return branch_2_info;
//         case 3:
//             return branch_3_info;
//         case 4:
//             return branch_4_info;
//         case 5:
//             return branch_5_info;
//         case 6:
//             return branch_6_info;
//     }
// }

void pack(char* recordbuf, const RESERVE *s){
    sprintf(recordbuf,"%s#%s#%s#", s->user_id, s->reserved_time, s->using_time);
}

// void unpack(const char *recordbuf, RESERVE *s){
//     int idx=0;
//     int field_idx=0, field_num=0;
//     while(idx < SIZE_RESERVE){
//         switch(field_num){
//             case 0:
//                 s -> user_id[field_idx] = recordbuf[idx];
//                 s -> user_id[field_idx+1] = '\0';
//                 break;
//             case 1:
//                 s -> reserved_time[field_idx] = recordbuf[idx];
//                 s -> reserved_time[field_idx+1] = '\0';
//                 break;
//             case 2:
//                 s -> using_time[field_idx] = recordbuf[idx];
//                 s -> using_time[field_idx+1] = '\0';
//                 break;
//         }
//         field_idx++; idx++; field_idx=0;
//     }
// }