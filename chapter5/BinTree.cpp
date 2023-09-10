#include"BinTree.h"
#include "BinNode.h"
#include"../chapter4/Stack.h"
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
BinNode<T>* BinTree<T>::attachAsRC(BinNode<T>*x,BinTree<T>*&S)
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
template<typename T,typename VST>
static void visitAlongLeftBranch(BinNode<T>*x,VST&visit,Stack<BinNode<T>*>&S)
{
    while(x)
    {
        visit(x->data);
        S.push(x->rc);
        x=x->lc;
    }
}
template<typename T>template<typename VST>
void BinTree<T>::travPre_I2(BinNode<T>*x,VST&visit)
{
    Stack<BinNode<T>*>S;
    while(true)
    {
        visitAlongLeftBranch(x,visit,S);
        if(S.empty()){break;}
        x=S.pop();
    }
}
template<typename T>
static void goAlongLeftBranch(BinNode<T>*x,Stack<BinNode<T>*>&S)
{
    while(x)
    {
        S.push(x);
        x=x->lc;
    }
}
template<typename T>template<typename VST>
void BinTree<T>::travIn_I1(BinNode<T>*x,VST&visit)
{
    Stack<BinNode<T>*>S;
    while(true)
    {
        goAlongLeftBranch(x,S);
        if(S.empty()){break;};
        x=S.pop();visit(x->data);
        x=x->rc;
    }
}
template<typename T>
static void gotoHLVFL(Stack<BinNode<T>*>&S)
{
    while(BinNode<T>*x=S.top())
    {
        if(HasLChild(*x))
        {
            if(HasRChild(*x)){S.push(x->rc);}
            S.push(x->lc);
        }
        else
        {
            S.push(x->rc);
        }
    }
    S.pop();
}
template<typename T>template<typename VST>
void BinTree<T>::travPost_I(BinNode<T> *x, VST &visit)
{
    Stack<BinNode<T>*>S;
    if(x){S.push(x);}
    while(!S.empty())
    {
        if(S.top()!=x->parent)
        {
            gotoHLVFL(S);
        }
        x=S.pop();visit(x->data);
    }
}