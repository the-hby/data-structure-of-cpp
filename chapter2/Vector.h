#ifndef Vector_h_
#define Vector_h_
#include<iostream>
using namespace std;
typedef int Rank;
#define DEFAULT_CAPACITY 3
template<typename T>
class Vector{
protected:
    Rank _size;
    int _capacity;
    T* _elem;
    void copyFrom(const T*A,Rank lo,Rank hi);
    void expand();
    void shrink();
    bool bubble(Rank lo,Rank hi);
    Rank max(Rank lo,Rank hi);
    void selectionSort(Rank lo,Rank hi);
    void merge(Rank lo,Rank mi,Rank hi);
    void mergeSort(Rank lo,Rank hi);
    Rank partition(Rank lo,Rank hi);
    void quikSort(Rank lo,Rank hi);
    void heapSort(Rank lo,Rank hi);
public:
    Vector(int c=DEFAULT_CAPACITY,int s=0,T v=0)
    {
        _elem=new T[_capacity=c];
        for(_size=0;_size<s;_elem[_size++]=v);
    }
    Vector(const T*A,Rank n){copyFrom(A,0,n);}
    Vector(const T*A,Rank lo,Rank hi){copyFrom(A,lo,hi);}
    Vector(const Vector<T>&V){copyFrom(V._elem,0,V._size);}
    Vector(const Vector<T>&V,Rank lo,Rank hi){copyFrom(V._elem,lo,hi);}
    ~Vector(){delete[]_elem;}
    Rank size()const{return _size;}
    bool empty()const{return !_size;}
    int disordered()const;
    Rank find(const T&e,Rank lo,Rank hi)const;
    Rank search(const T&e)const
    {
        return (0>=_size)?-1:search(e,0,_size);
    }
    Rank search(const T&e,Rank lo,Rank hi)const;
    T& operator[](Rank r)const;
    Vector& operator=(Vector&);
    T remove(Rank r);
    int remove(Rank lo,Rank hi);
    Rank insert(Rank r,const T&e);
    Rank insert(const T&e){return insert(_size,e);}
    void sort(Rank lo,Rank hi);
    void sort(){sort(0,_size);}
    void unsort(Rank lo,Rank hi);
    void unsort(){unsort(0,_size);}
    int deduplicate();
    int uniquify();
    void traverse(void (*)(T&));
    template<typename VST>
    void traverse(VST&);
};
#endif