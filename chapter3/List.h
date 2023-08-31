#ifndef List_h_
#define List_h_
#include"./listNode.h"
template<typename T>
class List
{
private:
    int _size;
    listNode<T>*header;
    listNode<T>*trailer;
protected:
    void init();
    int clear();
    void copyNodes(listNode<T>*,int);
    void merge(listNode<T>*,int,List<T>&,listNode<T>*,int);
    void mergeSort(listNode<T>*&,int);
    void selectionSort(listNode<T>*,int);
    void insertSort(listNode<T>*,int);
public:
    List(){init();}
    List(const List<T>&L);
    List(const List<T>&L,int r,int n);
    List(listNode<T>*p,int n);
    ~List();
    int size()const{return _size;}
    bool empty()const{return _size<=0;}
    T& operator[](int r)const;
    listNode<T>* first()const{return header->succ;}
    listNode<T>* last()const{return trailer->pred;}
    bool valid(listNode<T>*p){return p&&(trailer!=p)&&(header!=p);}
    int disordered()const;
    listNode<T>* find(const T&e)const{return find(e,_size,trailer);}
    listNode<T>* find(const T&e,int n,listNode<T>*p)const;
    listNode<T>* search(const T&e)const{return search(e,_size,trailer);}
    listNode<T>* search(const T&e,int n,listNode<T>*p)const;
    listNode<T>* selectMax(listNode<T>*p,int n);
    listNode<T>* selectMax(){return selectMax(header->succ,_size);}
    listNode<T>* insertAsFirst(const T&e);
    listNode<T>* insertAsLast(const T&e);
    listNode<T>* insertA(listNode<T>*p,const T&e);
    listNode<T>* insertB(listNode<T>*p,const T&e);
    T remove(listNode<T>*p);
    void merge(List<T>&L){merge(first(),_size,L,L.first(),L.size());}
    void sort(listNode<T>*p,int n);
    void sort(){sort(first(),_size);}
    int deduplicate();
    int uniquify();
    void reverse();
    void traverse(void (*)(T&));
    template<typename VST>
    void traverse(VST&);
};
#endif