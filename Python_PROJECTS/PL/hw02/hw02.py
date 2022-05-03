
# Character classes #
from re import L
import sys
from sqlalchemy import false, true


LETTER = 0
DIGIT = 1
UNKNOWN = 99

# Token codes #
INT_LIT = 10
IDENT = 11
ASSIGN_OP = 20
ADD_OP = 21
SUB_OP = 22
MULT_OP = 23
DIV_OP = 24
LEFT_PAREN = 25
RIGHT_PAREN = 26
EOF = -1

# Global declarations #
# Variables #
charClass = 1
lexeme = [0 for i in range(100)]
nextChar = 'c'
lexLen = 1
token = 1
nextToken = 1
curr_index = 1
cnt_R_paren = 0
cnt_L_paren = 0

def stoi(ch) :
    num=0
    digit=0
    while ch[digit] != 0 :
        digit += 1
    for i in range (1,digit+1) :
        num += (int(ch[digit-i]) * pow(10,i-1))

    return num

def print_error() :
    print("Syntax error!!")

def lookup(ch) :
    global nextToken
    global cnt_L_paren
    global cnt_R_paren
    if ch == '(' :
        addChar()
        nextToken = LEFT_PAREN
        cnt_L_paren += 1
    elif ch == ')':
        addChar()
        nextToken = RIGHT_PAREN
        cnt_R_paren += 1
    elif ch == '+':
        addChar()
        nextToken = ADD_OP
    elif ch == '-':
        addChar()
        nextToken = SUB_OP
    elif ch == '*':
        addChar()
        nextToken = MULT_OP
    elif ch == '/':
        addChar()
        nextToken = DIV_OP
    elif ch == '\n' :
        addChar()
        nextToken = EOF
    else :
        print_error()
        exit()
    return nextToken



def addChar() :
    global lexLen
    if lexLen <= 98 :
        lexeme[lexLen] = nextChar
        lexLen += 1
        lexeme[lexLen] = 0
    else :
        print("ERROR - lexeme is too long")
        exit()

def getChar() :
    global charClass
    global nextChar
    nextChar = sys.stdin.read(1)
    if nextChar != '\n' :
        if nextChar.isalpha() :
            print_error()
            exit()
        elif nextChar.isdigit() :
            charClass = DIGIT
        else : 
            charClass = UNKNOWN
    else :
        charClass = EOF

def getNonBlank() :
    while nextChar.isspace() and nextChar != '\n':
        getChar()

def lex() :
    global nextToken
    global lexLen
    lexLen = 0
    getNonBlank()
    # Parse identifiers #
    if charClass == LETTER :
        addChar()
        getChar()
        while charClass == LETTER or charClass == DIGIT :
            addChar()
            getChar()
    # Parse integer literals #
    elif charClass == DIGIT:
        addChar()
        getChar()
        while charClass == DIGIT :
            addChar()
            getChar()
        nextToken = INT_LIT
    # Parentheses and operators #
    elif charClass == UNKNOWN:
        lookup(nextChar)
        getChar()
    # EOF #
    elif charClass == EOF:
        nextToken = EOF
        lexeme[0] = 'E'
        lexeme[1] = 'O'
        lexeme[2] = 'F'
        lexeme[3] = 0

    # print("Next token is: ",nextToken,", Next lexeme is ",stoi(lexeme))
    return nextToken

def number() :
    curr_num = stoi(lexeme)
    lex()
    return curr_num

def factor() :
    isNegative = False
    curr_num = -1

    if nextToken == SUB_OP :
        lex()
        isNegative = true
    
    if nextToken == INT_LIT:
        curr_num = number()
    elif nextToken == LEFT_PAREN :
        lex()
        curr_num = expr()
        if nextToken == RIGHT_PAREN :
            lex()
        else :
            print_error()
            exit(0)
    else:
            print_error()
            exit(0)
    
    if isNegative :
        return curr_num * -1
    else :
        return curr_num

def term() :
    curr_num = factor()

    while nextToken == MULT_OP or nextToken == DIV_OP :
        curr_Token = nextToken
        lex()
        if curr_Token == MULT_OP :
            curr_num *= factor()
        else :
            curr_num /= factor()
    
    return curr_num

def expr() :
    curr_num = term()

    while nextToken == ADD_OP or nextToken == SUB_OP :
        curr_Token = nextToken
        lex()
        if curr_Token == ADD_OP :
            curr_num += term()
        else :
            curr_num -= term()

    return curr_num

def main() :
    while True :
        print(">> ", end='', flush=True)
        getChar()
        lex()

        ans = expr()

        if cnt_L_paren != cnt_R_paren:
            print_error()
            exit(0)
        else :
            print(ans)
        

# main()
while True :
    print(">> ", end='', flush=True)
    getChar()
    lex()

    ans = expr()

    if cnt_L_paren != cnt_R_paren:
        print_error()
        exit(0)
    else :
        print(ans)




















