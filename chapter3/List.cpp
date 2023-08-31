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
template<typename T>
List<T>::List(listNode<T>*p,int n)
{
    copyNodes(p,n);
}
template<typename T>
List<T>::List(const List<T>&L)
{
    copyNodes(L.first(),L._size);
}
template<typename T>
List<T>::List(const List<T>&L,int r,int n)
{
    copyNodes(L[r],n);
}
template<typename T>
T List<T>::remove(listNode<T>*p)
{
    T e=p->data;
    p->pred->succ=p->succ;p->succ->pred=p->pred;
    delete p;_size--;
    return e;
}
template<typename T>
List<T>::~List()
{
    clear();
    delete header;
    delete trailer;
}
template<typename T>
int List<T>::clear()
{
    int oldSize=_size;
    while(0<_size)
    {
        remove(header->succ);
    }
    return oldSize;
}
template<typename T>
int List<T>::deduplicate()
{
    if(_size<2){return 0;}
    int oldSize=_size;
    listNode<T>*p=header;int r=0;
    while(trailer!=(p=p->succ))
    {
        listNode<T>*q=find(p->data,r,p);
        q?remove(q):r++;
    }
    return oldSize-_size;
}
template<typename T>
void List<T>::traverse(void(*visit)(T&))
{
    for(listNode<T>*p=header->succ;p!=trailer;p=p->succ)
    {
        visit(p->data);
    }
}
template<typename T>
template<typename VST>
void List<T>::traverse(VST &visit)
{
    for(listNode<T>*p=header->succ;p!=trailer;p=p->succ)
    {
        visit(p->data);
    }
}
template<typename T>
int List<T>::uniquify()
{
    if(_size<2){return 0;}
    int oldSize=_size;
    listNode<T>*p=first();
    listNode<T>*q;
    while(trailer!=(q=p->succ))
    {
        if(p->data!=q->data){p=q;}
        else{remove(q);}
    }
    return oldSize-_size;
}
template<typename T>
listNode<T>* List<T>::search(const T&e,int n,listNode<T>*p)const
{
    while(0<=n--)
    {
        if(((p=p->pred)->data)<=e)
        {
            break;
        }
    }
    return p;
}
template<typename T>
void List<T>::sort(listNode<T>*p,int n)
{
    switch(rand()%3)
    {
        case 1:insertionSort(p,n);break;
        case 2:selectionSort(p,n);break;
        default:mergeSort(p,n);break;
    }
}
template<typename T>
static bool lt(T*a,T*b){return lt(*a,*b);}
template<typename T>
static bool lt(T&a,T&b){return a<b;}
template<typename T>
listNode<T>* List<T>::selectMax(listNode<T>*p,int n)
{
    listNode<T>*max=p;
    for(listNode<T>*cur=p;1<n;n--)
    {
        if(!lt((cur=cur->succ)->data,max->data))
        {
            max=cur;
        }
    }
    return max;
}
template<typename T>
void List<T>::merge(listNode<T>*p,int n,List<T>&L,listNode<T>*q,int m)
{
    listNode<T>*pp=p->pred;
    while(0<m)
    {
        if((0<n)&&(p->data<=q->data))
        {
            if(q==(p=p->succ)){break;}
            n--;
        }
        else 
        {
            insertB(p,L.remove((q=q->succ)->pred));
            m--;
        }
    }
    p=pp->succ;
}
template<typename T>
void List<T>::mergeSort(listNode<T>*&p,int n)
{
    if(n<2){return;}
    int m=n>>1;
    listNode<T>*q=p;
    for(int i=0;i<m;i++)
    {
        q=q->succ;
    }
    mergeSort(p,m);
    mergeSort(p,n-m);
    merge(p,m,*this,q,n-m);
}
