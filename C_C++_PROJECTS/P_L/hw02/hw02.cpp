// #define DEBUG

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
using namespace std;

/* Character classes */
#define LETTER 0
#define DIGIT 1
#define UNKNOWN 99

/* Token codes */
#define INT_LIT 10
#define IDENT 11
#define ASSIGN_OP 20
#define ADD_OP 21
#define SUB_OP 22
#define MULT_OP 23
#define DIV_OP 24
#define LEFT_PAREN 25
#define RIGHT_PAREN 26


/* Global declarations */
/* Variables */
int charClass;
char lexeme[100];
char nextChar;
int lexLen;
int token;
int nextToken;
int curr_index;
vector<char> user_input;
string user_input_string;

/* Function declarations */
int lookup(char);
void addChar();
char getc();
void getChar();
void getNonBlank();
int lex();
double expr();
double term();
double factor();
double number();

void print_error(){
    cout << "Syntax error!!" << endl;
}

int lookup(char ch){
    switch(ch){
        case '(':
            addChar();
            nextToken = LEFT_PAREN;
            break;
        case ')':
            addChar();
            nextToken = RIGHT_PAREN;
            break;
        case '+':
            addChar();
            nextToken = ADD_OP;
            break;
        case '-':
            addChar();
            nextToken = SUB_OP;
            break;
        case '*':
            addChar();
            nextToken = MULT_OP;
            break;
        case '/':
            addChar();
            nextToken = DIV_OP;
            break;
        default :
            addChar();
            nextToken = EOF;
            break;
    }
    return nextToken;
}

void addChar(){
    if(lexLen <= 98){
        lexeme[lexLen++] = nextChar;
        lexeme[lexLen] = 0;
    }
    else{
        cout << "ERROR - lexeme is too long" << endl;
        exit(0);
    }
}

void getChar(){
    if((nextChar = getc(stdin)) != '\n'){
        if(isalpha(nextChar))
            charClass = LETTER;
        else if(isdigit(nextChar))
            charClass = DIGIT;
            else charClass = UNKNOWN;
    }
    else{
        charClass = EOF;
    }
}

void getNonBlank(){
    while(isspace(nextChar) && nextChar != '\n')
        getChar();
}

int lex(){
    lexLen = 0;
    getNonBlank();
    switch (charClass) {
        /* Parse identifiers */
        case LETTER:
            addChar();
            getChar();
            while (charClass == LETTER || charClass == DIGIT) {
                addChar();
                getChar();
            }
            nextToken = IDENT;
            break;
        /* Parse integer literals */
        case DIGIT:
            addChar();
            getChar();
            while (charClass == DIGIT) {
                addChar();
                getChar();
            }
            nextToken = INT_LIT;
            break;
        /* Parentheses and operators */
        case UNKNOWN:
            lookup(nextChar);
            getChar();
            break;
        /* EOF */
        case EOF:
            nextToken = EOF;
            lexeme[0] = 'E';
            lexeme[1] = 'O';
            lexeme[2] = 'F';
            lexeme[3] = 0;
            break;
    } /* End of switch */
    #ifdef DEBUG
    printf("Next token is: %d, Next lexeme is %s\n", nextToken, lexeme);
    #endif
    return nextToken;
} /* End of function lex */

double number(){
    #ifdef DEBUG
    cout << "Enter <number>" << endl;
    #endif
    int curr_num = stoi(lexeme);
    lex();
    #ifdef DEBUG
    cout << "Exit <number>" << endl;
    #endif
    return curr_num;
}

double factor(){
    #ifdef DEBUG
    cout << "Enter <factor>" << endl;
    #endif
    bool isSUB = false;
    double curr_num;

    if(nextToken == SUB_OP){
        lex();
        isSUB = true;
    }
    if(nextToken == INT_LIT){
        curr_num = number();
    }
    else if(nextToken == LEFT_PAREN){
        lex();
        curr_num = expr();
        if(nextToken == RIGHT_PAREN)
            lex();
        else{
            print_error();
            exit(0);
        }
    }
    else{
        print_error();
        exit(0);
    }
    #ifdef DEBUG
    cout << "Exit <factor>" << endl;
    #endif
    if(isSUB){
        return curr_num * -1;
    }
    else return curr_num;
}

double term(){
    #ifdef DEBUG
    cout << "Enter <term>" << endl;
    #endif

    bool isOP = false;

    double curr_num = factor();

    while(nextToken == MULT_OP || nextToken == DIV_OP){
        isOP = true;
        int curr_Token = nextToken;
        lex();
        if(curr_Token == MULT_OP) curr_num *= factor();
        else curr_num /= factor();

    }
    #ifdef DEBUG
    cout << "Exit <term>" << endl;    
    #endif
    return curr_num;
}

double expr(){
    #ifdef DEBUG
    cout << "Enter <expr>" << endl;
    #endif

    double
    curr_num = term();

    while(nextToken == ADD_OP || nextToken == SUB_OP){
        int curr_Token = nextToken;
        lex();
        if(curr_Token == ADD_OP) curr_num += term();
        else curr_num -= term();
    }
    #ifdef DEBUG
    cout << "Exit <expr>" << endl;
    #endif
    return curr_num;
}

int main(void){
    while(1){
        cout << ">> ";
        getChar();
        lex();

        double ans = expr();

        if((ans - (int)ans) == 0){      // ans = 정수
            cout << ans << endl;
        }
        else{
            cout << fixed;
            cout.precision(6);
            cout << ans <<endl;
        }
    }
    return 0;
}