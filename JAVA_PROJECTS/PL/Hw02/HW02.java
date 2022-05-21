package PL.Hw02;

import java.io.IOException;

public class HW02 {
    /* Character classes */
    public final int LETTER = 0;
    public final int DIGIT = 1;
    public final int UNKNOWN = 99;

    /* Token codes */
    public final int INT_LIT = 10;
    public final int IDENT = 11;
    public final int ASSIGN_OP = 20;
    public final int ADD_OP = 21;
    public final int SUB_OP = 22;
    public final int MULT_OP = 23;
    public final int DIV_OP = 24;
    public final int LEFT_PAREN = 25;
    public final int RIGHT_PAREN = 26;
    public final static int EOF = -99;
    
    
    /* Global declarations */
    /* Variables */
    public static int charClass;
    public char[] lexeme;
    public char nextChar;
    public int lexLen;
    public int token;
    public int nextToken;
    public int cnt_R_paren=0;
    public int cnt_L_paren=0;

    public HW02(){
        lexeme = new char[100];
    }

    int stoi(char[] ch){
        int num=0;
        int digit =0;
        while(ch[digit] != 0){
            digit++;
        }
        for(int i=1; i<=digit; i++){
            num += Character.getNumericValue(ch[digit-i]) *Math.pow(10,i-1);
        }
        return num;
    }
    
    void print_error(){
        System.out.println("Syntax error!!");
    }

    int lookup(char ch){
        switch(ch){
            case '(': addChar(); nextToken = LEFT_PAREN;    cnt_L_paren++;  break; 
            case ')': addChar(); nextToken = RIGHT_PAREN;   cnt_R_paren++;  break;
            case '+': addChar(); nextToken = ADD_OP;         break;
            case '-': addChar(); nextToken = SUB_OP;         break;
            case '*': addChar(); nextToken = MULT_OP;        break;
            case '/': addChar(); nextToken = DIV_OP;         break;
            case '\r': addChar(); nextToken = EOF;           break;
            default : print_error(); System.exit(0);  break;
        }
        return nextToken;
    }

    void addChar(){        
        if(lexLen <= 98){
            lexeme[lexLen++] = nextChar;
            lexeme[lexLen] = 0;
        }
        else{
            System.out.println("ERROR - lexeme is too long");
            System.exit(0);
        }
    }
    
    void getChar() throws IOException{
        nextChar = (char) System.in.read();
        if(nextChar != '\r'){
            if(Character.isLetter(nextChar)){
                print_error();
                System.exit(0);
            }
            else if(Character.isDigit(nextChar))
                charClass = DIGIT;
                else charClass = UNKNOWN;
        }
        else{
            charClass = EOF;
        }
    }
    void getNonBlank() throws IOException{
        while((Character.isSpaceChar(nextChar) || nextChar == '\t') && nextChar != '\n')
            getChar();
    }

    int lex() throws IOException{
        lexLen = 0;
        getNonBlank();
        switch (charClass) {
            /* Parse identifiers */
            case LETTER:
                addChar();
                getChar();
                while (charClass == LETTER || charClass == DIGIT) { addChar(); getChar(); }
                nextToken = IDENT;
                break;
            /* Parse integer literals */
            case DIGIT:
                addChar();
                getChar();
                while (charClass == DIGIT) { addChar(); getChar(); }
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
        return nextToken;
    } /* End of function lex */

    double number() throws IOException{
        int curr_num = stoi(lexeme);
        lex();
        return curr_num;
    }
    
    double factor() throws IOException{
        Boolean isNegative = false;
        double curr_num=-1;
    
        if(nextToken == SUB_OP){
            lex();
            isNegative = true;
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
                System.exit(0);
            }
        }
        else{
            print_error();
            System.exit(0);
        }
        if(isNegative){
            return curr_num * -1;
        }
        else return curr_num;
    }
    
    double term() throws IOException{
        double curr_num = factor();
    
        while(nextToken == MULT_OP || nextToken == DIV_OP){
            int curr_Token = nextToken;
            lex();
            if(curr_Token == MULT_OP) curr_num *= factor();
            else curr_num /= factor();
    
        }
        return curr_num;
    }
    
    double expr() throws IOException{
        double
        curr_num = term();

        while(nextToken == ADD_OP || nextToken == SUB_OP){
            int curr_Token = nextToken;
            lex();
            if(curr_Token == ADD_OP) curr_num += term();
            else curr_num -= term();
        }
        return curr_num;
    }
    
    public static void main(String[] args) throws IOException {
        HW02 hw02 = new HW02();
        while(true){
            System.out.print(">> ");
            hw02.getChar();       
            if(charClass == EOF) {
                System.in.read();
                continue;
            }
            hw02.lex();
            
            double ans = hw02.expr();

            
            if(hw02.nextToken == hw02.INT_LIT){
                hw02.print_error();
                System.exit(0);
            }

            System.out.println(ans);
            System.in.read();
        }        
    }

}


