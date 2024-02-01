#ifndef QuadlistNode_h_
#define QuadlistNode_h_
#include "Entry.h"
template<typename T>
struct QuadlistNode{
    T entry;
    QuadlistNode<T>*pred;
    QuadlistNode<T>*succ;
    QuadlistNode<T>*above;
    QuadlistNode<T>*below;
    QuadlistNode(
        T e=T(),QuadlistNode<T>*p=NULL,QuadlistNode<T>*s=NULL,QuadlistNode<T>*a=NULL,
        QuadlistNode<T>*b=NULL
    ):entry(e),pred(p),succ(s),above(a),below(b){}
    QuadlistNode<T>*insertAsSuccAbove(
        const T&e,QuadlistNode<T>*b=NULL
    );
};
#endif