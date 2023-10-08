#ifndef BST_h_
#define BST_h_
#include"../chapter5/BinTree.h"
#include"../chapter5/BinTree.cpp"
template<typename T>
class BST:public BinTree<T>
{
protected:
    BinNode<T>*_hot;
    BinNode<T>*connect34(
        BinNode<T>*,BinNode<T>*,BinNode<T>*,
        BinNode<T>*,BinNode<T>*,BinNode<T>*,BinNode<T>*
    );
    BinNode<T>*rotateAt(BinNode<T>*x);
public:
    virtual BinNode<T>*& search(const T&e);
    virtual BinNode<T>* insert(const T&e);
    virtual bool remove(const T&e);
};
template<typename T>
static BinNode<T>*& searchIn(BinNode<T>*&v,const T&e,BinNode<T>*&hot)
{
    if(!v||(e==v->data)){return v;}
    hot=v;
    return searchIn(((e<v->data)?v->lc:v->rc),e,hot);
}
template<typename T>
BinNode<T>*& BST<T>::search(const T&e)
{
    return searchIn(this->_root,e,_hot=NULL);
}
template<typename T>
BinNode<T>* BST<T>::insert(const T &e)
{
    BinNode<T>*&x=search(e);
    if(x){return x;}
    x=new BinNode<T>(e,_hot);
    this->_size++;
    updateHeightAbove(x);
    return x;
}
template<typename T>
static BinNode<T>* removeAt(BinNode<T>*&x,BinNode<T>*&hot)
{
    BinNode<T>*w=x;
    BinNode<T>*succ=NULL;
    if(!HasLChild(*x))
    {
        succ=x=x->rc;
    }
    else if(!HasRChild(*x))
    {
        succ=x=x->lc;
    }
    else {
        w=w->succ();
        std::swap(x->data,w->data);
        BinNode<T>*u=w->parent;
        ((u==x)?u->rc:u->lc)=succ=w->rc;
    }
    hot=w->parent;
    if(succ){succ->parent=hot;}
    release(w->data);release(w);return succ;
}
template<typename T>
BinNode<T>* BST<T>::connect34(
    BinNode<T>*a,BinNode<T>*b,BinNode<T>*c,
    BinNode<T>*T0,BinNode<T>*T1,BinNode<T>*T2,BinNode<T>*T3
)
{
    a->lc=T0;if(T0){T0->parent=a;}
    a->rc=T1;if(T1){T1->parent=a;updateHeight(a);}
    c->lc=T2;if(T2){T2->parent=c;}
    c->rc=T3;if(T3){T3->parent=c;updateHeight(c);}
    b->lc=a;a->parent=b;
    b->rc=c;c->parent=b;updateHeight(b);
    return b;
}
template<typename T>
BinNode<T>* BST<T>::rotateAt(BinNode<T>*v)
{
    BinNode<T>*p=v->parent;
    BinNode<T>*g=p->parent;
    if(IsLChild(*p))
    {
        if(IsLChild(*v))
        {
            p->parent=g->parent;
            return connect34(v,p,g,v->lc,v->rc,p->rc,g->rc);
        }
        else {
            v->parent=g->parent;
             return connect34(p,v,g,p->lc,v->lc,v->rc,g->rc);
        }
    }
    else {
        if(IsRChild(*v))
        {
            p->parent=g->parent;
            return connect34(g,p,v,g->lc,p->lc,v->lc,v->rc);
        }
        else
        {
            v->parent=g->parent;
            return connect34(g,v,p,g->lc,v->lc,v->rc,p->rc);
        }
    }
}
#endif