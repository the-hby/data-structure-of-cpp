#include"./function.h"
#include<stdio.h>
#include<string.h>
#include"cmath"
void convert1(Stack<char>&S,int n,int base)
{
    static char digit[]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
    if(n>0)
    {
        S.push(digit[n%base]);
        convert(S,n/base,base);
    }
}
void convert2(Stack<char>&S,int n,int base)
{
   static char digit[]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
   while(n>0)
   {
        int remainder=(int)(n%base);
        S.push(digit[remainder]);
        n/=base;
   }
}
void trim(const char exp[],int &lo,int &hi)
{
    while((lo<=hi)&&(exp[lo]!='(')&&(exp[lo]!=')')){lo++;}
    while((lo<=hi)&&(exp[lo]!='(')&&(exp[lo]!=')')){hi--;}
}
int divide(const char exp[],int &lo,int &hi)
{
    int mi=lo;int crc=1;
    while((0<crc)&&(++mi<hi))
    {
        if(exp[mi]==')'){crc--;}
        if(exp[mi]=='('){crc--;}
    }
    return mi;
}
bool paren1(const char exp[],int lo,int hi)
{
    trim(exp,lo,hi);
    if(lo>hi){return true;}
    if(exp[lo]!='('){return false;}
    if(exp[hi]!=')'){return false;}
    int mi=divide(exp,lo,hi);
    if(mi>hi){return false;}
    return paren1(exp,lo+1,mi-1)&&paren1(exp,mi+1,hi);
}
bool paren2(const char exp[],int lo,int hi)
{
    Stack<char>S;
    for(int i=lo;i<=hi;i++)
    {
        switch(exp[i])
        {
            case '(':case '[':case '{':S.push(exp[i]);break;
            case ')':
            if((S.empty())||('('!=S.pop())){return false;}break;
            case ']':
            if((S.empty())||('['!=S.pop())){return false;}break;
            case '}':
            if((S.empty())||('{'!=S.pop())){return false;}break;
            default:break;
        }
    }
    return S.empty();
}
double calcu ( double a, char op, double b ) 
{ 
   switch ( op ) {
      case '+' : return a + b;
      case '-' : return a - b;
      case '*' : return a * b;
      case '/' : if ( 0==b ) exit ( -1 ); return a/b;
      case '^' : return pow ( a, b );
      default  : exit ( -1 );
   }
}
double calcu ( char op, double b ) 
{ 
   switch ( op ) {
      case '!' : return ( double ) facI ( ( int ) b );
      default  : exit ( -1 );
   }
}
Operator optr2Rank(char op)
{
    switch(op)
    {
        case '+':return ADD;
        case '-':return SUB;
        case '*':return MUL;
        case '/':return DIV;
        case '^':return POW;
        case '!':return FAC;
        case '(':return L_P;
        case ')':return R_P;
        case '\0':return EOE;
        default:exit(-1);
    }
    
}
char priority(char op1,char op2)
{
    return pri[optr2Rank(op1)][optr2Rank(op2)];
}
void readNumber(char *&p, Stack<double> &stk)
{
    stk.push((double)(*p-'0'));
    while(isdigit(*(++p)))
    {
        stk.push(stk.pop()*10+(*p-'0'));
    }
    if(*p=='.')
    {
        double franction=1;
        while(isdigit(*(++p)))
        {
            stk.push(stk.pop()+(*p-'0')*(franction/=10));
        }
    }
}
void append ( char* rpn, double opnd ) 
{ 
   char buf[64];
   if ( ( int ) opnd < opnd ) sprintf ( buf, "%6.2f \0", opnd ); 
   else                       sprintf ( buf, "%d \0", ( int ) opnd );
   strcat ( rpn, buf ); 
}
float evaluate(char*S,char*&RPN)
{
    Stack<double>opnd;Stack<char>optr;
    optr.push('\0');
    while(!optr.empty())
    {
        if(isdigit(*S))
        {
           readNumber(S,opnd);
           append(RPN,opnd.top()); 
        }
        else 
        {
            switch(priority(optr.top(),*S))
            {
                case '<':optr.push(*S);S++;break;
                case '=':optr.pop();S++;break;
                case '>':{char op=optr.pop();
                append(RPN,op);
                if('!'==op)
                {
                    float pOnd=opnd.pop();
                    opnd.push(calcu(op,pOnd));
                }
                else 
                {
                    float pOnd=opnd.pop();
                    float pOnd1=opnd.pop();
                    opnd.push(calcu(pOnd,op,pOnd1));
                }
                break;}
                default:exit(-1);
            }
            
        }
    }
    return opnd.pop();
}