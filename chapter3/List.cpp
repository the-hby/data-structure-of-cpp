#include"./List.h"
#include "listNode.h"
template<typename T>
void List<T>::init()
{
    header=new listNode<T>;
    trailer=new listNode<T>;
    header->succ=trailer;
    header->pred=NULL;
    trailer->pred=header;
    trailer->succ=NULL;
    _size=0;
}
template<typename T>
T& List<T>::operator[](int n)const
{
    listNode<T>*p=first();
    while(n-->0){p=p->succ;}
    return p->data;
}
template<typename T>
listNode<T>* List<T>::find(const T&e,int n,listNode<T>*p)const
{
    while(n-->0)
    {
        if(e==(p=p->pred)->data){return p;}
    }
    return NULL;
}
template<typename T>
listNode<T>* List<T>::insertAsFirst(const T &e)
{
    _size++;
    header->insertAsSucc(e);
}
template<typename T>
listNode<T>* List<T>::insertAsLast(const T&e)
{
    _size++;
    return trailer->insertAsPred(e);
}
template<class T>
listNode<T>* List<T>::insertA(listNode<T>*p,const T&e)
{
    _size++;
    return p->insertAsSucc(e);
}
template<typename T>
listNode<T>* List<T>::insertB(listNode<T>*p,const T&e)
{
    _size++;
    return p->insertAsPred(e);
}
template<typename T>
listNode<T>* listNode<T>::insertAsPred(const T &e)
{
    listNode<T>*x=new listNode(e,pred,this);
    pred->succ=x;this->pred=x;
}
template<class T>
listNode<T>* listNode<T>::insertAsSucc(const T &e)
{
    listNode<T>*x=new listNode(e,this,succ);
    succ->pred=x;this->succ=x;
}
template<typename T>
void List<T>::copyNodes(listNode<T>*p,int n)
{
    init();
    while(n--){insertAsLast(p->data);p=p->succ;}
}