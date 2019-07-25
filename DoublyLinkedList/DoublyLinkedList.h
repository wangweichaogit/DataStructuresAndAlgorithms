//
// Created by mfbut on 2/11/2019.
//

#ifndef LINKEDLIST_DOUBLYLINKEDLIST_H
#define LINKEDLIST_DOUBLYLINKEDLIST_H

#include <vector>
#include <memory>
#include <iostream>
#include "DoubleLinkedNode.h"
#include "DoublyLinkedListIterator.h"
#include "ReverseDoublyLinkedListIterator.h"

template<typename T>
class DoublyLinkedList {
 public:
 	typedef T value_type;
  using Node_Ptr = DoubleLinkedNode<T>*;
  using Node = DoubleLinkedNode<T>;
	using CNode_Ptr = DoubleLinkedNode<const T>*;
	
  using iterator =  DoublyLinkedListIterator<T>;
  //using const_iterator =  ConstDoublyLinkedListIterator<T>;
  using const_iterator =  DoublyLinkedListIterator<const T>;
  using reverse_iterator = ReverseDoublyLinkedListIterator<T>;
  //using const_reverse_iterator =  ConstReverseDoublyLinkedListIterator<T>;
  using const_reverse_iterator =  ReverseDoublyLinkedListIterator<const T>;

  //create a Doubly Linked List that has the same values
  //as in the vector and in the same order
  explicit DoublyLinkedList(const std::vector<T>& values):head(nullptr),tail(nullptr),len(0){
  	for(auto v:values){
  		push_back(v);
  	}
  }

  //create an empty DoublyLinkedList
  DoublyLinkedList() {
  	 tail = head = nullptr;
  	 len = 0;
  }


  virtual ~DoublyLinkedList() {clear();}

  //remove all of the elements from your list
  void clear(){
  	iterator iter = begin();
  	while(iter !=end()){
  		 erase(iter++);
  	}
  }

  //get a reference to the front element in the list
  const T& front() const { 
  	return head->data;
 		//if (head != nullptr) return head->data;
 		//else  return T();
  }
  T& front() {
  	return head->data;
   	//if (head != nullptr) return head->data;
 		//else  return T();
  }

  //get a reference to the last element in the list
  const T& back() const {
  	return tail->data;
  	//if (tail != nullptr) return tail->data;
 		//else  return T();
  }
  T& back() {
  	return tail->data;
  //	if (tail != nullptr) return tail->data;
 	//	else  return T();
  }

  //add a value to the front of the list
  void push_front(const T& value) {
  	Node_Ptr ptr = new DoubleLinkedNode<T>(value) ;
  	if(head==nullptr){
  		head = tail = ptr;
  	} else {
  		ptr->next = head;
  		head->pre = ptr;
  		head = ptr;
  	}
  	len++;
  }

  //add a value to the back of the list
  void push_back(const T& value){
  	Node_Ptr ptr = new DoubleLinkedNode<T>(value) ;
  	if(head == nullptr){
  		head = tail = ptr;
  	} else {
  		tail->next = ptr;
  		ptr->pre = tail;
  		tail = ptr;
  	}
  	len++;
  }

  //is the list empty?
  bool empty() const {return len==0;}

  //return the number of elements in the list
  int size() const {return len;}

	const_iterator changeIteratorToConstIterator(Node_Ptr p)const{
		using nodeP =DoubleLinkedNode<const T>*;
		nodeP cp = (nodeP)p;
		return const_iterator(cp);
	}
  //return a constant bidirectional iterator to the front of the list
  const_iterator begin() const{ 
  	return const_iterator((CNode_Ptr)head);
  }
  const_iterator end() const  {return const_iterator(nullptr);}

  //return a nonconstant bidirectional iterator to the front of the list
  iterator begin() { return iterator(head);}
  iterator end()  { return iterator(nullptr);}

  const_reverse_iterator crbegin() const {return const_reverse_iterator((CNode_Ptr)tail);}
  const_reverse_iterator crend() const {return const_reverse_iterator(nullptr);}

  reverse_iterator rbegin() {return reverse_iterator(tail);}
  reverse_iterator rend() {return reverse_iterator(nullptr);}

  //insert the value at the position in the list
  //I promise not to use the iterator again after the insertion is done
  //An example if we had the list 1 <-> 9 <-> 17
  //And the iterator was pointing to the 9 and we wanted to
  //insert -22 the result would be
  //1 <-> 22 <-> 9 <-> 17
  void insert(iterator& position, const T& value){
  	
  	Node_Ptr ptr = new DoubleLinkedNode<T>(value);
  	Node_Ptr posPtr = position.getPtr();
  	if(head==nullptr){
  		head = tail = ptr;
  	} else {
  		if(posPtr){				
  			if(posPtr->pre){ 			
  				posPtr->pre->next=ptr;
  				ptr->pre = posPtr->pre;
  				ptr->next = posPtr;
  				posPtr->pre = ptr;
  			} else {  				
  					posPtr->pre = ptr;
  					ptr->next = posPtr;
  					head = ptr;
  				}
  		}  else{
  			tail->next = ptr;
  			ptr->pre = tail;
  			tail = ptr;
  		}
  	}
  	len++;
  	position=iterator(ptr);
  	  	
  }

  //remove the element at the position pointed to
  //by the iterator.
  //I promise not to use the iterator again after the erase is done
  //An example if we had the list 1 <-> 9 <-> 17
  //And when the wanted to erase the iterator was at the 9
  //1 <-> 17
  void erase(iterator& position){
  	Node_Ptr posPtr = position.getPtr();
  	if(posPtr){
  		len--;
  		if(posPtr->pre == nullptr && posPtr->next == nullptr){
  			head = tail = nullptr;
  		} else if(posPtr->pre == nullptr){
  			head = posPtr->next;
  			head->pre = nullptr;
  		} else if (posPtr->next == nullptr){
  			tail = tail->pre;
  			tail->next = nullptr;
  		} else {
  			posPtr->pre->next = posPtr->next;
  			posPtr->next->pre = posPtr->pre;
  		}
  		delete posPtr;
  	}
  }
  void erase(const iterator& position){
  	const Node_Ptr posPtr = position.getConstPtr();
  	if(posPtr){
  		len--;
  		if(posPtr->pre == nullptr && posPtr->next == nullptr){
  			head = tail = nullptr;
  		} else if(posPtr->pre == nullptr){
  			head = posPtr->next;
  			head->pre = nullptr;
  		} else if (posPtr->next == nullptr){
  			tail = tail->pre;
  			tail->next = nullptr;
  		} else {
  			posPtr->pre->next = posPtr->next;
  			posPtr->next->pre = posPtr->pre;
  		}
  		delete posPtr;
  	}
  }
 private:
  Node_Ptr head;
  Node_Ptr tail;
  int len;
};

//write to the stream each element in the list in order
//with a space in between them
template<typename T>
std::ostream& operator<<(std::ostream& out, const DoublyLinkedList<T>& doublyLinkedList){
	auto iter= doublyLinkedList.begin();
	while(iter != doublyLinkedList.end()){
		out<<" ";
		out<<*iter++;
	}
	out<<std::endl;
	return out;
}

//read elements from the stream as long as it is good
// or until a newline (\n) is encountered
//if a newline is encontered it should be consumed
template<typename T>
std::istream& operator>>(std::istream& in, DoublyLinkedList<T>& doublyLinkedList){
	 char buf[1024]={0};
	 while(in.good()){
        in.getline(buf,1024,' ');
        doublyLinkedList.push_back(buf);
   }
	return in;
}


#endif //LINKEDLIST_DOUBLYLINKEDLIST_H



// 
//https://github.com/zouxiaohang/TinySTL/blob/master/TinySTL/Detail/List.impl.h
//https://stackoverflow.com/questions/3582608/how-to-correctly-implement-custom-iterators-and-const-iterators?r=SearchResults
//https://stackoverflow.com/questions/2150192/how-to-avoid-code-duplication-implementing-const-and-non-const-iterators?r=SearchResults