//
// Created by mfbut on 2/11/2019.
//

#ifndef LINKEDLIST_DOUBLELINKEDNODE_H
#define LINKEDLIST_DOUBLELINKEDNODE_H
#include <iostream>

//the class that represents a node in the list

template<typename T>
class DoubleLinkedNode {
public:
		T data;
		DoubleLinkedNode *pre;
		DoubleLinkedNode *next;
		DoubleLinkedNode(){}
		DoubleLinkedNode(const T &t):data(t),pre(nullptr),next(nullptr){}
		bool operator==(const DoubleLinkedNode<T>& other){
			return data==other.data&&pre==other.pre&&next==other.next;
		}
};


#endif //LINKEDLIST_DOUBLELINKEDNODE_H
