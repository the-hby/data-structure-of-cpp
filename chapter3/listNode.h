#ifndef listNode_h_
#define listNode_h_
#include<iostream>
template<typename T>
struct listNode
{
    T data;
    listNode<T>*pred;
    listNode<T>*succ;
    listNode(){}
    listNode(T e,listNode<T>*p=NULL,listNode<T>*s=NULL):data(e),pred(p),succ(s){}
    listNode<T>* insertAsPred(const T&e);
    listNode<T>* insertAsSucc(const T&e);
};
#endif