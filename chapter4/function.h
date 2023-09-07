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
struct Queen{
    int x,y;
    Queen(int xx=0,int yy=0):x(xx),y(yy){}
    bool operator==(const Queen&q)const
    {
        return (x==q.x)||(y==q.y)||(x+y==q.x+q.y)||(x-y==q.x-q.y);
    }
    bool operator!=(const Queen&q)const
    {
        return !((*this)==q);
    }
};
void placeQueens(int N);
extern int nSolu;
extern int nCheck;
typedef enum{AVAILABLE,ROUTE,BACKRACKED,WALL}Status;
typedef enum{UNKNOWN,EAST,SOUTH,WEST,NORTH,NO_WAY}ESWN;
inline ESWN nextESWN(ESWN eswn){return ESWN(eswn+1);}
struct Cell{
    int x,y;
    Status status;
    ESWN incoming,outgoing;
};
#define LABY_MAX 24
Cell laby[LABY_MAX][LABY_MAX];
#endif 