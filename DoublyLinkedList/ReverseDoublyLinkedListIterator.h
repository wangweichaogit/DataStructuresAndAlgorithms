//
// Created by mfbut on 2/13/2019.
//

#ifndef LINKEDLIST_GENERICREVERSEDOUBLYLINKEDLISTITERATOR_H
#define LINKEDLIST_GENERICREVERSEDOUBLYLINKEDLISTITERATOR_H

template<typename T>
class ReverseDoublyLinkedListIterator  {
 public:
  //you must implement at least the methods below
  //you are free to add (and will likely need to add)
  //more members and methods
	ReverseDoublyLinkedListIterator(DoubleLinkedNode<T> *p =nullptr):m_ptr(p){}
  //copy constructor
  ReverseDoublyLinkedListIterator(const ReverseDoublyLinkedListIterator& orig){m_ptr = orig.m_ptr;}
  //are the two iterators equal?
  //they are if they are over the same doubly linked list
  //and (they are referring to the same element in the list
  //or they are out of bounds)
  bool operator==(const ReverseDoublyLinkedListIterator<T>& rhs) const {
  	return m_ptr == rhs.m_ptr;
  }

  //are the two iterators different?
  bool operator!=(ReverseDoublyLinkedListIterator<T>& rhs) const{
  	return m_ptr != rhs.m_ptr;
  }

  //is the iterator safe to dereference?
  operator bool() const{
  	if (m_ptr) return true;
  	else       return false;
  }

  //go to the next element
  ReverseDoublyLinkedListIterator<T>& operator++(){
  	m_ptr=m_ptr->pre;;
  	return *this;
  }
  const ReverseDoublyLinkedListIterator<T> operator++(int){
  	auto temp(*this);
  	m_ptr=m_ptr->pre;
  	return temp;
  }

  //go to the previous element
  ReverseDoublyLinkedListIterator<T>& operator--(){
  	m_ptr=m_ptr->next;
  	return *this;
  }
  const ReverseDoublyLinkedListIterator<T> operator--(int){
  	auto temp(*this);
  	m_ptr=m_ptr->next;
  	return *this;
  }

  //get a const reference to the value
  const T& operator*() const {return m_ptr->data;}

  //get a non-const reference to the value
  T& operator*() {return m_ptr->data;}
private:
	DoubleLinkedNode<T> *m_ptr;
};

#endif //LINKEDLIST_GENERICREVERSEDOUBLYLINKEDLISTITERATOR_H
