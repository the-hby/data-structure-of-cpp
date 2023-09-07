#include"BinTree.h"
#include "BinNode.h"
template<typename T>
int BinTree<T>::updateHeight(BinNode<T>*x)
{
    return x->height=1+std::max(stature(x->lc),stature(x->rc));
}
template<typename T>
void BinTree<T>::updateHeightAbove(BinNode<T>*x)
{
    while(x){updateHeight(x);x=x->parent;}
}
template<typename T>
BinNode<T>* BinTree<T>::insertAsRoot(const T &e)
{
    _size=1;return _root=new BinNode<T>(e);
}
template<typename T>
BinNode<T>* BinTree<T>::insertAsLC(BinNode<T>*x,const T&e)
{
    _size++;x->insertAsLC(e);updateHeightAbove(x);
    return x->lc;
}
template<typename T>
BinNode<T>* BinTree<T>::insertAsRC(BinNode<T>*x,const T&e)
{
    _size++;x->insertAsRC(e);updateHeight(x);
    return x->rc;
}
template<typename T>
BinNode<T>* BinTree<T>::attachAsLC(BinNode<T> *x,BinTree<T>*&S)
{
    if(x->lc=S->root){x->lc->parent=x;}
    _size+=S->_size;updateHeightAbove(x);
    S->_root=NULL;S->_size=0;release(S);S=NULL;return x;
}
template<typename T>
BinNode<T>* BinTree<T>::attachAsRC(BinNode<T> *x,BinTree<T>*&S)
{
    if(x->rc=S->root){x->rc->parent=x;}
    _size+=S->_size;updateHeightAbove(x);
    S->_root=NULL;S->_size=0;release(S);S=NULL;return x;
}
template<typename T>
static int removeAt(BinNode<T>*x)
{
    if(!x){return 0;}
    int n=1+removeAt(x->lc)+removeAt(x->rc);release(x->data);
    release(x);return n;
}
template<typename T>
int BinTree<T>::remove(BinNode<T>*x)
{
    FromParentTo(*x)=NULL;
    updateHeight(x->parent);
    int n=removeAt(x);_size-=n;return n;
}
