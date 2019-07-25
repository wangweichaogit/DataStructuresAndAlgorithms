//
// Created by mfbut on 2/11/2019.
//

#ifndef LINKEDLIST_GENERICDOUBLYLINKEDLISTITERATOR_H
#define LINKEDLIST_GENERICDOUBLYLINKEDLISTITERATOR_H
#include <iterator>

template<typename T>
class DoublyLinkedListIterator :public std::iterator<std::bidirectional_iterator_tag ,T>{
  //you must implement at least the methods below
  //you are free to add (and will likely need to add)
  //more members and methods

 public:
 	using Node_Ptr = DoubleLinkedNode<T>*;
 	DoublyLinkedListIterator(Node_Ptr p=nullptr):m_ptr(p){}
  DoublyLinkedListIterator(const DoublyLinkedListIterator& orig){
  	m_ptr = orig.m_ptr;
  }
  //are the two iterators equal?
  //they are if they are over the same doubly linked list
  //and (they are referring to the same element in the list
  //or they are out of bounds)
  bool operator==(const DoublyLinkedListIterator<T>& rhs) const{
  	return m_ptr == rhs.m_ptr;
  }

  //are the two iterators different?
  bool operator!=(const DoublyLinkedListIterator<T>& rhs) const{
  	return m_ptr != rhs.m_ptr;
  }

  //is the iterator safe to dereference?
  operator bool() const {
  	if(m_ptr) return true;
  	else	return false;
  }

  //go to the next element
  DoublyLinkedListIterator<T>& operator++() {
  	m_ptr=m_ptr->next;
  	return *this;
  }
  const DoublyLinkedListIterator<T> operator++(int){
  	auto temp(*this);
  	m_ptr=m_ptr->next;
  	return temp;
  }

  //go to the previous element
  DoublyLinkedListIterator<T>& operator--() {
  	m_ptr=m_ptr->pre;
  	return *this;
  }
  const DoublyLinkedListIterator<T> operator--(int){
  	auto temp(*this);
  	m_ptr=m_ptr->pre;
  	return temp;
  }

  //get a const reference to the value
  const T& operator*() const {return m_ptr->data;}

  //get a non const iterator
  T& operator*() {return m_ptr->data;}
  
  
  Node_Ptr getPtr() {return m_ptr;}
  Node_Ptr getConstPtr() const{return m_ptr;}
  private:
  Node_Ptr m_ptr;

};

#endif //LINKEDLIST_GENERICDOUBLYLINKEDLISTITERATOR_H
