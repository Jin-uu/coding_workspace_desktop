#define DEBUG
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

const int BRANCH_NUM = 6;
const int MAX_ROOM_NUM = 10;
char BRANCH_INFO_FILE_NAME[] = "./branch_info.txt";
char ROOM_INFO_FILE_NAME[] = "./room_info.txt";

FILE *branch_info;
char branch_info_arr[6] = {'a','a','a','a','a','a'};
bool is_branch_able[6];

// input func
int  get_user_input(void);              // ����� �Է� �ޱ�
void wrong_input(void);                 // �Է� ������
void exit_program(void);                // ���α׷� ����
// init 
void mode_selection(void);              // �ʱ� ��� ���� ȭ��
// admin    
void mode_admin(void);                  // ������ ��� �۾�����
void mode_add_branch(int);             // ���� �߰� ���
void mode_mod_branch(int);             // ���� ���� ���
void mode_del_branch(int);             // ���� ���� ���
void get_branch_info(void);             // ���� ���� �ҷ�����
// user 
void mode_user(void);                   // ����� ��� ����
// file manage  
void open_file(FILE**, char*);          // ���� ����
bool is_file_empty(FILE*);              // ������ ����ִ��� �˻�
void init_branch_info(FILE*);           // branch_info.txt �ʱ�ȭ
void set_branch_info(char[]);           // brnach_info.txt ����

int main(void){
    while(1) mode_selection();

    return 0;
}

void exit_program(void){
    printf(">> ���α׷��� �����մϴ�...\n");
    exit(0);
}

void wrong_input(void){
    printf(">> �ùٸ��� ���� �Է��Դϴ�...\n");
    exit_program();
}

int get_user_input(void){
    int input;
    scanf("%d", &input);
    return input;
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

// ���� �߰� ���
void mode_admin(void){
    get_branch_info();                  // branch_info_arr �� ���� ����
    printf("--------<������ ���>--------\n");
    printf("---------<���� ��Ȳ>---------\n");
    for (int i = 1; i <= BRANCH_NUM; i++) {
        printf("    ���� %d", i);
        if(is_branch_able[i]){                  // ���� ���� �Ǿ�����
            printf(" (������)\n");
        }
        else { printf(" (�������� ����)\n"); }  // ���� �����̸�
    }
    printf("���α׷� ���� : (0)\n");
    printf("-----------------------------\n");
    printf("������ �����ϼ���.\n>> ");          // �������� �Է� �ޱ�
    int input_branch_selection = get_user_input();
    if(input_branch_selection == 0) exit_program();
    printf("%d ������ ���� �۾��� �����ϼ���.\n", input_branch_selection);   // ���õ� ������ ���� �۾� �Է� �ޱ�
    printf(" (1) �߰�    (2) ����    (3) ����   (4) ���α׷� ����\n");
    printf(">> ");
    switch(get_user_input()){
        case 1:
            mode_add_branch(input_branch_selection);
            break;
        case 2:
            // mode_mod_branch(input_branch_selection);
            break;
        case 3:
            // mode_del_branch(input_branch_selection);
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
    if(is_branch_able[branch_num]){          // �̹� ���� �� �������� �˻�
        printf(">> �̹� ������ �����Դϴ�.\n");
        return;
    }
    // �������� ���� �����̸�
    branch_info_arr[branch_num] = '1';
    set_branch_info(branch_info_arr);
    printf("%d ������ �����߽��ϴ�.\n", branch_num);
}

// ���� ���� ���
void mode_mod_branch(int branch_num){

}

// ���� ���� ���
void mode_del_branch(int branch_num){

}    

// ���� ���� �ҷ�����
void get_branch_info(void){
    open_file(&branch_info ,BRANCH_INFO_FILE_NAME);         // ���� ����
    if(is_file_empty(branch_info)){                         // ������ ���������
        init_branch_info(branch_info);                      // �ʱ�ȭ (���� ����)
        open_file(&branch_info ,BRANCH_INFO_FILE_NAME);     // ���� ����
    }
    
    fseek(branch_info, 0, SEEK_SET);            // ���� ������ ������ ����
    fread(branch_info_arr,strlen(branch_info_arr), sizeof(char),branch_info);   // �б�
    for (int i = 0; i < 6; i++) {
        if(branch_info_arr[i] == '0'){          // char ������ bool �� �迭�� ��ȯ
            is_branch_able[i] = false;          
        }
        else { is_branch_able[i] = true; }
    }

    fclose(branch_info);                        // ���� �� �а� ���� �ݱ�
}

// ������ ����ִ��� �˻�
bool is_file_empty(FILE *filestream){
    fseek(filestream, 0, SEEK_END);
    int file_size = ftell(filestream);

    if(file_size < 1) return true;          // ���� �����
    return false;                           // ���� �Ⱥ����
}

// branch_info.txt. �ʱ�ȭ
void init_branch_info(FILE* filestream){
    char branch_info_init_string[] = "000000";
    if(fwrite(branch_info_init_string, strlen(branch_info_init_string), sizeof(char),branch_info) < 1){
        printf("NULL!\n");
        exit(1);
    }
    fclose(branch_info);               // ���� �ݾƼ� ����
}

// branch_info.txt ����
void set_branch_info(char new_branch_info[]){
    open_file(&branch_info ,BRANCH_INFO_FILE_NAME);         // brnach_info.txt ���� ����
    if(fwrite(new_branch_info, strlen(new_branch_info), sizeof(char),branch_info) < 1){
        printf("NULL!\n");
        exit(1);
    }
    fclose(branch_info);               // ���� �ݾƼ� ����
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
