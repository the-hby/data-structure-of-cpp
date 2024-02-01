#ifndef Quadlist_h_
#define Quadlist_h_
#include"QuadlistNode.h"
template<typename T>
class Quadlist{
private:
    int _size;
    QuadlistNode<T>*header;
    QuadlistNode<T>*trailer;
protected:
    void init();
    int clear();
public:
    Quadlist(){init();}
    ~Quadlist(){clear();delete header;delete trailer;}
    Rank size(){return _size;}
    bool empty(){return _size<=0;}
    QuadlistNode<T>* first()const {return header->succ;}
    QuadlistNode<T>* last()const {return trailer->pred;}
    bool valid(QuadlistNode<T>*p);
    bool valid(QuadlistNode<T>*p){
        return p&&(trailer!=p)&&(header!=p);
    }
    T remove(QuadlistNode<T>*p);
    QuadlistNode<T>*insertAfterAbove(const T&e,QuadlistNode<T>*p,QuadlistNode<T>*b=NULL);
    void traverse(void (*)(T&));
    template<typename VST>
    void traverse(VST&);
};
template<typename T>
void Quadlist<T>::init(){
    header=new QuadlistNode<T>;
    trailer=new QuadlistNode<T>;
    header->succ=trailer;
    header->pred=NULL;
    trailer->pred=header;
    trailer->succ=NULL;
    header->above=header->above=NULL;
    header->below=header->below=NULL;
}
#endif