#ifndef queue_h_
#define queue_h_
#include"../chapter3/List.h"
#include"../chapter3/List.cpp"
template<typename T>
class Queue:public List<T>
{
public:
    Queue():List<T>(){}
    Queue(const Queue<T>&e);
    Queue(const Queue<T>&e,int lo,int hi);
    T& operator[](int n)const;
    void enqueue(const T&e){this->insertAsLast(e);}
    T dequeue(){return this->remove(this->first());}
    T& front(){return this->first()->data;}
};
template<typename T>
Queue<T>::Queue(const Queue<T>&e)
{
    this->copyNodes(e.first(),e.size());
}
template<typename T>
Queue<T>::Queue(const Queue<T>&e,int lo,int hi)
{
    this->copyNodes(e[lo],hi);
}
template<typename T>
T& Queue<T>::operator[](int n)const
{
    listNode<T>*tmp=this->first();
    while(n-->0){tmp=tmp->succ;}
    return tmp->data;
}
#endif