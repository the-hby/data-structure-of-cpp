#ifndef AVL_h_
#define AVL_h_
#include"./BST.h"
#include "../chapter5/BinNode.h"
template<typename T>
class AVL:public BST<T>
{
    BinNode<T>* insert(const T&e);
    bool remove(const T&e);
};
#define Balanced(x)(stature((x).lc)==stature((x).rc))
#define BalFac(x)(stature((x).lc)-stature((x).rc))
#define AvlBalanced(x)((-2<BalFac(x))&&(BalFac(x)<2))
#define tallerChild(x)(\
    stature((x)->lc)>stature((x)->rc)?(x)->lc:(\
    stature((x)->lc)<stature((x)->rc)?(x)->rc:(\
    IsLChild(*(x))?(x)->lc:(x)->rc\
    )\
    )\
)
template<typename T>
BinNode<T>* AVL<T>::insert(const T&e)
{
    BinNode<T>*&x=search(e);
    if(x){return x;}
    BinNode<T>*xx=x=new BinNode<T>(e,this->_hot);this->_size++;
    for(BinNode<T>*g=this->_hot;g;g=g->parent)
    {
        if(!AvlBalanced(*g))
        {
            FromParentTo(*g)=rotateAt(tallerChild(tallerChild(g)));
            break;
        }
        else {
            updateHeight(g);
        }
    }
    return xx;
}
template<typename T>
bool AVL<T>::remove(const T&e)
{
    BinNode<T>*&x=search(e);
    if(!x){return false;}
    removeAt(x,this->_hot);this->_size++;
    for(BinNode<T>*g=this->_hot;g;g=g->parent)
    {
        if(!AvlBalanced(*g))
        {
            g=FromParentTo(*g)=rotateAt(tallerChild(tallerChild(g)));
        }
        updateHeight(g);
    }
    return true;
}
#endif