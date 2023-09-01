#include"../chapter2/Vector.h"
template<typename T>
class Stack:public Vector<T>
{
public:
    Stack(const T*A,Rank n):Vector<T>(A,n){}
    Stack(const T*A,Rank lo,Rank hi):Vector<T>(A,lo,hi){}
    void push(const T&e){insert(this->size(),e);}
    T pop(){return remove(this->size()-1);}
    T& top(){return (*this)[this->size()-1];}
};