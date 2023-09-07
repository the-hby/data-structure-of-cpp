#ifndef BinTree_h_
#define BinTree_h_
#include"./BinNode.h"
template<typename T>
static bool lt(T &a,T &b){return a<b;}
template<typename T>
static bool lt(T*a,T*b){return lt(*a,*b);}
template<typename T>
class BinTree
{
protected:
    int _size;
    BinNode<T>*_root;
    virtual int updateHeight(BinNode<T>*x);
    void updateHeightAbove(BinNode<T>*x);
public:
    BinTree():_size(0),_root(NULL){}
    ~BinTree(){if(_size>0){remove(_root);}}
    int size()const{return _size;}
    bool empty()const{return !_root;}
    BinNode<T>* root()const{return _root;}
    BinNode<T>* insertAsRoot(const T&e);
    BinNode<T>* insertAsLC(BinNode<T>*x,const T&e);
    BinNode<T>* insertAsRC(BinNode<T>*x,const T&e);
    BinNode<T>* attachAsLC(BinNode<T>*x,BinTree<T>*&);
    BinNode<T>* attachAsRC(BinNode<T>*x,BinTree<T>*&);
    int remove(BinNode<T>*x);
    BinTree<T>* secede(BinNode<T>*x);
    template<typename VST>
    void traLevel(VST&visit){_root->travLevel(visit,this);}
    template<typename VST>
    void travPre(VST&visit){_root->travPre(visit,this);}
    template<typename VST>
    void travPost(VST&visit){_root->travPost(visit,this);}
    template<typename VST>
    void travIn(VST&visit){_root->travIn(visit);}
    bool operator<(const BinTree<T>&t)
    {
        return _root&&t._root&&lt(_root,t._root);
    }
    bool operator==(const BinTree<T>&t)
    {
        return _root&&t._root&&(_root==t._root);
    }
};
#endif