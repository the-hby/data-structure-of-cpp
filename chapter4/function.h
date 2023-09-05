#ifndef function_h_
#define function_h_
#include"./Stack.h"
void convert1(Stack<char>&S,int n,int base);
void convert(Stack<char>&S,int n,int base);
void trim(const char exp[],int &lo,int &hi);
int divide(const char exp[],int &lo,int &hi);
bool paren1(const char exp[],int lo,int hi);
bool paren2(const char exp[],int lo,int hi);
#define N_OPTR 9
typedef enum{ADD,SUB,MUL,DIV,POW,FAC,L_P,R_P,EOE}Operator;
const char pri[N_OPTR][N_OPTR]={
    '>','>','<','<','<','<','<','>','>',
    '>','>','<','<','<','<','<','>','>',
    '>','>','>','>','<','<','<','>','>',
    '>','>','>','>','<','<','<','>','>',
    '>','>','>','>','>','<','<','>','>',
    '>','>','>','>','>','>',' ','>','>',
    '<','<','<','>','<','<','<','=',' ',
    ' ',' ',' ',' ',' ',' ',' ',' ',' ',
    '<','<','<','<','<','<','<',' ','='
};
float evaluate(char*S,char*&RPN);
void readNumber(char*&p,Stack<double>&stk);
void append ( char* rpn, double opnd );
Operator optr2Rank(char op);
char priority(char op1,char op2);
double calcu ( double a, char op, double b );
double calcu ( char op, double b );
int facI(int n);
#endif