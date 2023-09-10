#ifndef BinNode_h_
#define BinNode_h_
#include<iostream>
#include"../chapter4/queue.h"
#define stature(p)((p)?(p)->height:-1)
typedef enum{RB_RED,RB_BLACK}RBColor;
template<typename T>
struct BinNode
{
    T data;
    BinNode<T>*parent;BinNode<T>*lc;BinNode<T>*rc;
    int height;
    int npl;
    RBColor color;
    BinNode():parent(NULL),lc(NULL),rc(NULL),height(0),npl(1),color(RB_RED){}
    BinNode(T e,BinNode<T>*p=NULL,BinNode<T>*lc=NULL,BinNode<T>*rc=NULL,int h=0,int l=1,RBColor c=RB_RED)
    :data(e),parent(p),lc(lc),rc(rc),height(height),npl(l),color(c){}
    int size();
    BinNode<T>* insertAsLC(const T&);
    BinNode<T>* insertAsRC(const T&);
    BinNode<T>* succ();
    template<typename VST>void travLevel(VST&,BinNode<T>*);
    template<typename VST>void travPre(VST&,BinNode<T>*);
    template<typename VST>void travIn(BinNode<T>*p,VST&);
    template<typename VST>void travPost(VST&,BinNode<T>*);
    bool operator<(const BinNode<T>&bn){return data<bn.data;}
    bool operator==(const BinNode<T>&bn){return data==bn.data;}
};
template<typename T>
BinNode<T>* BinNode<T>::insertAsLC(const T&e)
{
    return lc=new BinNode(e,this);
}
template<typename T>
BinNode<T>* BinNode<T>::insertAsRC(const T &e)
{
    return rc=new BinNode(e,this);
}
template<typename T>template<typename VST>
void BinNode<T>::travLevel(VST&visit,BinNode<T>*p)
{
   Queue<BinNode<T>*>Q;
   Q.enqueue(this);
   while(!Q.empty())
   {
        BinNode<T>*x=Q.dequeue();visit(x->data);
        if(HasLChild(*x)){Q.enqueue(x->lc);}
        if(HasRChild(*x)){Q.enqueue(x->rc);}
   }
}
template<typename T>template<typename VST>
void BinNode<T>::travPre(VST&visit,BinNode<T>*p)
{
    if(p==NULL){return;}
    visit(p->data);
    travPre(visit,p->lc);
    travPre(visit,p->rc);
}
template<typename T>template<typename VST>
void BinNode<T>::travPost(VST &visit, BinNode<T> *p)
{
    if(p==NULL){return;}
    travPre(visit,p->lc);
    travPre(visit,p->rc);
    visit(p->data);
}
template<typename T>template<typename VST>
void BinNode<T>::travIn(BinNode<T>*p,VST &visit)
{
   travIn(p->lc,visit);
   visit(p->data);
   travIn(p->rc,visit);
}
#define IsRoot(x)(!((x).parent))
#define IsLChild(x)(!IsRoot(x)&&(&(x)==(x).parent->lc))
#define HasParent(x)(!IsRoot(x))
#define HasLChild(x)((x).lc)
#define HasRChild(x)((x).rc)
#define HasChild(x)(HasLChild(x)||HasRChild(x))
#define HasBothChild(x)(HasLChild(x)&&HasRChild(x))
#define IsLeaf(x)(!HasChild(x))
#define sibling(p)(IsLChild(*(p))?(p)->parent->rc:(p)->parent->parent->lc)
#define uncle(x)(*((x)->parent)?(x)->parent->parent->rc:(x)->parent->parent->lc)
#define FromParentTo(x)(IsRoot(x)?_root:(IsLChild(x)?(x).parent->lc:(x).parent->rc))
#endif