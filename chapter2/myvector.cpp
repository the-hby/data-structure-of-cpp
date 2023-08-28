#include"./myvector.h"
template<typename T>
void my_vector<T>::copyFrom(const T*A,Rank lo,Rank hi)
{
    _elem=new T[_capacity=2*(hi-lo)];
    _size=0;
    while(lo<hi){_elem[_size++]=A[lo++];}
}
template<typename T>
my_vector<T>& my_vector<T>::operator=(my_vector<T> &V)
{
    if(_elem){delete [] _elem;}
    copyFrom(V._elem,0,V._size);
    return *this;
}
template<typename T>
void my_vector<T>::expand()
{
    if(_size<_capacity){return;}
    if(_capacity<DEFAULT_CAPACITY){_capacity=DEFAULT_CAPACITY;}
    T*oldElem=_elem;_elem=new T[_capacity<<=1];
    for(int i=0;i<_size;i++)
    {
        _elem[i]=oldElem[i];
    }
    delete [] oldElem;
}
template<typename T>
void my_vector<T>::shrink()
{
    if(_capacity<DEFAULT_CAPACITY<<1){return;}
    if(_size<<2>_capacity){return;}
    T*oldElem=_elem;_elem=new T[_capacity>>=1];
    for(int i=0;i<_size;i++)
    {
        _elem[i]=oldElem[i];
    }
    delete[]oldElem;
}
template<typename T>
T& my_vector<T>::operator[](Rank r)const
{
    return _elem[r];
}
template<typename T>
void my_vector<T>::unsort(Rank lo,Rank hi)
{
    T*V=_elem+lo;
    for(Rank i=hi-lo;i>0;i--)
    {
        swap(V[i-1],V[rand()%i]);
    }
}
template<typename T> static bool lt(T*a,T*b){return lt(*a,*b);}
template<typename T> static bool lt(T&a,T&b){return a<b;}
template<typename T> static bool eq(T*a,T*b){return eq(*a,*b);}
template<typename T> static bool eq(T&a,T&b){return a==b;}
template<typename T> 
Rank my_vector<T>::find(const T&e,Rank lo,Rank hi)const
{
    while((lo<hi--)&&(e!=_elem[hi]))
    {
        return hi;
    }
}
template<typename T>
Rank my_vector<T>::insert(Rank r,const T&e)
{
    expand();
    for(int i=_size;i>r;i--)
    {
        _elem[i]=_elem[i-1];
    }
    _elem[r]=r;_size++;
    return r;
}
template<typename T>
int my_vector<T>::remove(Rank lo,Rank hi)
{
    if(lo==hi)
    {
        return 0;
    }
    while(hi<_size)
    {
        _elem[lo++]=_elem[hi++];
    }
    _size=lo;
    shrink();
    return hi-lo;
}
template<typename T>
T my_vector<T>::remove(Rank r)
{
    T e=_elem[r];
    remove(r,r+1);
    return e;
}
template<typename T>
int my_vector<T>::deduplicate()
{
    int oldSize=_size;
    Rank i=1;
    while(i<_size)
    {
        (find(_elem[i],0,i))?i++:remove(i);
    }
    return oldSize-_size;
}
template<typename T>
int my_vector<T>::uniquify()
{
    Rank i=0,j=0;
    while(++j<_size)
    {
        if(_elem[i]!=_elem[j])
        {
            _elem[++i]=_elem[j];
        }
    }
    _size=++i;
    shrink();
    return j-i;
}
template<typename T>
static Rank binSearch(T*A,const T&e,Rank lo,Rank hi)
{
    Rank mi=(lo+hi)>>1;
    while(lo<hi)
    {
        if(e<A[mi]){hi=mi;}
        else if(A[mi]){lo=mi+1;}
        else{return mi;}
    }
    return -1;
}
template<typename T>
Rank my_vector<T>::search(const T&e,Rank lo,Rank hi)const
{
    return binSearch(_elem,e,lo,hi);
}
template<typename T>
void my_vector<T>::merge(Rank lo,Rank mi,Rank hi)
{
    T*A=_elem+lo;
    int lb=mi-lo;
    T*B=new T[lb];
    for(Rank i=0;i<lb;B[i]=A[i++]);
    int lc=hi-mi;T*C=_elem+mi;
    for(Rank i=0,j=0,k=0;(j<lb)||k<lc;)
    {
        if((j<lb)&&(!(k<lc)||(B[j]<=C[k]))){A[i++]=B[j++];}
        if((k<lc)&&(!(j<lb)||(C[k]<B[j]))){A[i++]=C[k++];}
    }
    delete []B;
}
template<typename T>
void my_vector<T>::mergeSort(Rank lo,Rank hi)
{
    if(hi-lo<2){return;}
    int mi=(lo+hi)/2;
    mergeSort(lo,mi);
    mergeSort(mi,hi);
    merge(lo,mi,hi);
}
