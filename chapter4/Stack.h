#ifndef Stack_h_
#define Stack_h_
#include"../chapter2/Vector.h"
#include"../chapter2/Vector.cpp"
template<typename T>
class Stack:public Vector<T>
{
public:
    Stack(int c=DEFAULT_CAPACITY,int s=0,T v=0):Vector<T>(c,s,v){}
    Stack(const T*A,Rank n):Vector<T>(A,n){}
    Stack(const T*A,Rank lo,Rank hi):Vector<T>(A,lo,hi){}
    Stack(const Stack<T>&V);
    Stack(const Stack<T>&V,Rank lo,Rank hi);
    void push(const T&e){insert(this->size(),e);}
    T pop(){return this->remove(this->_size-1);}
    T& top(){return this->_elem[this->size()-1];}
};
template<typename T>
Stack<T>::Stack(const Stack<T>&V)
{
    this->copyFrom(V._elem,0,V.size());
}
template<typename T>
Stack<T>::Stack(const Stack<T>&V,Rank lo,Rank hi)
{
    this->copyFrom(V._elem,lo,hi);
}
#endif