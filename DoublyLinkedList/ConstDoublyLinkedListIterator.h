//
// Created by mfbut on 2/16/2019.
//

#ifndef TESTDOUBLELINKEDLIST_CONSTDOUBLYLINKEDLISTITERATOR_H
#define TESTDOUBLELINKEDLIST_CONSTDOUBLYLINKEDLISTITERATOR_H

template<typename T>
class ConstDoublyLinkedListIterator {
//you must implement at least the methods below
  //you are free to add (and will likely need to add)
  //more members and methods

 public:
 	using Node_Ptr = DoubleLinkedNode<T>*;
 	ConstDoublyLinkedListIterator(Node_Ptr p=nullptr):m_ptr(p){}
  ConstDoublyLinkedListIterator(const ConstDoublyLinkedListIterator& orig){
  	m_ptr = orig.m_ptr;
  }
  //are the two iterators equal?
  //they are if they are over the same doubly linked list
  //and (they are referring to the same element in the list
  //or they are out of bounds)
  bool operator==(const ConstDoublyLinkedListIterator<T>& rhs) const{
  	return m_ptr == rhs.m_ptr;
  }

  //are the two iterators different?
  bool operator!=(const ConstDoublyLinkedListIterator<T>& rhs) const{
  	return m_ptr != rhs.m_ptr;
  }

  //is the iterator safe to dereference?
  operator bool() const {
  	if(m_ptr) return true;
  	else	return false;
  }

  //go to the next element
  ConstDoublyLinkedListIterator<T>& operator++() {
  	m_ptr=m_ptr->next;
  	return *this;
  }
  const ConstDoublyLinkedListIterator<T> operator++(int){
  	auto temp(*this);
  	m_ptr=m_ptr->next;
  	return temp;
  }

  //go to the previous element
  ConstDoublyLinkedListIterator<T>& operator--(){
  	m_ptr=m_ptr->pre;
  	return *this;
  }
  const ConstDoublyLinkedListIterator<T> operator--(int){
  	auto temp(*this);
  	m_ptr=m_ptr->pre;
  	return temp;
  }

  //get a const reference to the value
  const T& operator*() const  {return m_ptr->data;}
private:
  Node_Ptr m_ptr;

};

#endif //TESTDOUBLELINKEDLIST_CONSTDOUBLYLINKEDLISTITERATOR_H
