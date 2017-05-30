#ifndef multi_linked_list_h_
#define multi_linked_list_h_
// A simplified implementation of a generic list container class,
// including the iterator, but not the const_iterators.  Three
// separate classes are defined: a Node class, an iterator class, and
// the actual list class.  The underlying list is doubly-linked, but
// there is no dummy head node and the list is not circular.
#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <cstddef>
#include <algorithm>
// -----------------------------------------------------------------
// NODE CLASS
template <class T>
class Node {
public:
  //default constructor
  Node() : chrono_next(NULL), chrono_prev(NULL),sorted_next(NULL), sorted_prev(NULL),random_next(NULL){}
  //constructor with a value
  Node(const T& v) : value_(v), chrono_next(NULL), chrono_prev(NULL),sorted_next(NULL), sorted_prev(NULL),random_next(NULL) {}

  // REPRESENTATION
  //each node will have a value, and a pointer to the next element and previous element 
  //depending on the type of list we are iterating through
  T value_;             
  Node<T>* chrono_next;
  Node<T>* chrono_prev;
  Node<T>* sorted_next;
  Node<T>* sorted_prev;
  Node<T>* random_next;
};

// A "forward declaration" of this class is needed
template <class T> class MultiLL;

// -----------------------------------------------------------------
// LIST ITERATOR
template <class T>
class list_iterator {
public:
  // default constructor, copy constructor, assignment operator, & destructor
  list_iterator() : ptr_(NULL) {}
  list_iterator(Node<T>* p, std::string name) : ptr_(p),type(name){}
  list_iterator(const list_iterator<T>& old) : ptr_(old.ptr_),type(old.type) {}
  list_iterator<T>& operator=(const list_iterator<T>& old) {
    ptr_ = old.ptr_;  type = old.type; return *this; }
  ~list_iterator() {}

  // dereferencing operator gives access to the value at the pointer
  T& operator*()  { return ptr_->value_;  }

  // increment & decrement operators
  list_iterator<T>& operator++() { // pre-increment, e.g., ++iter
    if (type == "chrono") {        //based on the current type the iterator object is,make that the next element
      ptr_ = ptr_->chrono_next;
      return *this;                //return the list_iterator's pointer
    }
    if (type == "sorted") {
      ptr_ = ptr_->sorted_next;
      return *this;
    }
    else {
      ptr_ = ptr_->random_next;
      return *this;
    }
  }
  list_iterator<T> operator++(int) { // post-increment, e.g., iter++
    list_iterator<T> temp(*this);
     if (type == "chrono") {         //based on the current type the iterator object is,make that the next element
      ptr_ = ptr_->chrono_next;
      return temp;                   //return the list_iterator's pointer
    }
    if (type == "sorted") {
      ptr_ = ptr_->sorted_next;
      return temp;
    }
    else {
      ptr_ = ptr_->random_next;
      return temp;
    }
  }
  list_iterator<T>& operator--() { //pre-decrement, e.g., --iter
    if (type == "chrono") {        //based on the current type the iterator object is,make that the prev element
      ptr_ = ptr_->chrono_prev;
      return *this;                //return the list_iterator's pointer
    }
    if (type == "sorted") {
      ptr_ = ptr_->sorted_prev;
      return *this;
    }
    else {
      ptr_ = ptr_->random_next;
      return *this;
    }
  }
  list_iterator<T> operator--(int) { // post-decrement, e.g., iter--
    list_iterator<T> temp(*this);      
     if (type == "chrono") {         //based on the current type the iterator object is,make that the prev element
      ptr_ = ptr_->chrono_prev;
      return temp;                   //return the list_iterator's pointer
    }
    if (type == "sorted") {
      ptr_ = ptr_->sorted_prev;
      return temp;
    }
    else {
      ptr_ = ptr_->random_next;
      return temp;
    }
  }
  // the MultiLL class needs access to the private ptr_ member variable
  friend class MultiLL<T>;

  // Comparions operators are straightforward
  bool operator==(const list_iterator<T>& r) const {
    return ptr_ == r.ptr_; }
  bool operator!=(const list_iterator<T>& r) const {
    return ptr_ != r.ptr_; }
  

private:
  // REPRESENTATION
  Node<T>* ptr_;    // ptr to node in the list
  std::string type; //will be used to determine  the iterator type
  };

// -----------------------------------------------------------------
// LIST CLASS DECLARATION
// Note that it explicitly maintains the size of the list.
template <class T>
class MultiLL {
public:
  typedef list_iterator<T> iterator;
  // default constructor copy constructor, assignment operator, & destructor
  MultiLL() : chrono_head(NULL), chrono_tail(NULL), sorted_head(NULL),sorted_tail(NULL),random_head(NULL),size_(0){}
  MultiLL(const MultiLL<T>& old) { this->copy_list(old); }
  MultiLL& operator= (const MultiLL<T>& old);
  ~MultiLL() { this->destroy_list(); }

  //ACCESSORS AND SIMPLE MODIFIERS
  unsigned int size() const { return size_; }
  bool empty() const { return chrono_head == NULL; }
  void clear() { this->destroy_list(); } //public call to destroy the MLL


  //MLL MODIFIERS
  void add(const T& v);
  iterator erase (iterator it);
  void random_element();
  
  //ACCESSORS FOR ITERATORS
  iterator begin_chronological(){return iterator(chrono_head,"chrono");};
  iterator begin_sorted(){return iterator(sorted_head,"sorted");};
  iterator begin_random(){random_element(); return iterator(random_head,"random");};
  iterator end_chronological(){return iterator(NULL,"chrono");};
  iterator end_sorted(){return iterator(NULL,"sorted");};
 
private:
  // private helper functions
  void copy_list(const MultiLL<T>& old);
  void destroy_list();

  //REPRESENTATION
  //Multiple heads and tails that will point to specific versions of the MLL
  Node<T>* chrono_head; 
  Node<T>* chrono_tail;
  Node<T>* sorted_head;
  Node<T>* sorted_tail;
  Node<T>* random_head;
  unsigned int size_;
};

// -----------------------------------------------------------------
// LIST CLASS IMPLEMENTATION

template <class T>
MultiLL<T>& MultiLL<T>::operator= (const MultiLL<T>& old) {
  // check for self-assignment
  if (&old != this) {
    this->destroy_list();
    this->copy_list(old);
  }
  return *this;
}
template <class T>
//ADD AN ELEMENT TO THE MLL
void MultiLL<T>::add(const T& v){
  Node<T>* newElement = new Node<T>;         //creating a Node to hold the new elements value
  newElement->value_ = v;                    //sending the value to the new Node
  if (chrono_head == NULL) {                 //if we don't have a head point everything to the new element      
    chrono_head = newElement; 
    chrono_tail = newElement;
    sorted_head = newElement;   
    sorted_tail = newElement;
    random_head = newElement; 
    random_head -> random_next = random_head;//random points to itself    
    ++size_;                                 //increase the size of the list by one
  }
  else{
    newElement->chrono_prev = chrono_tail;    //the new element is being added to the end, the tail points to it now
    newElement->chrono_next = NULL;           //the new element points to nothing, since it is the last in the list
    chrono_tail->chrono_next = newElement;    //the old chrono tail now points to the end
    chrono_tail = newElement;                 //the old chrono tail is now pointing to what will be the new tail
    ++size_;                                  //increase the list size by one
    iterator it;                              //new iterator for looking through the MLL 
    it = begin_sorted();                      //starting at the head 
    bool tailCase = true;                     //we have a boolean to determine if we are replacing the tail             
    for(it; it != end_sorted(); it++){
      if (it.ptr_ -> value_ > newElement -> value_){ //if the iterator is greater than the element, we are putting the element behind the iterator
        tailCase = false;                            //if this is a tail case,it wont be caught by the other conditions
        if (it.ptr_ -> sorted_prev == NULL) {    //if we are making the element the new head
          it.ptr_ -> sorted_prev = newElement;   //the old head points back to the new head(newElement)
          newElement -> sorted_next = it.ptr_;   //the new head will point to the old head
          sorted_head = newElement;              //the new head is now the new sorted head
          break;
        }
        else {                                                  //if we are dealing with adding the element to the middle
          newElement -> sorted_prev = it.ptr_ -> sorted_prev;   //the new element 
          newElement -> sorted_prev -> sorted_next = newElement;//the new element's previous element is the new element
          newElement -> sorted_next = it.ptr_;                  //newElement points to the iterator
          it.ptr_ -> sorted_prev = newElement;                  //temp value will be inserted befor the iterator
          break;
        }
      }
    }
    if (tailCase) {                             //if we are dealing with a tail case
      iterator it;                              //new iterator to look at the sorted tail
      it.ptr_ = sorted_tail;                       
      it.ptr_ -> sorted_next = newElement;      //the old tail points to the new tail
      newElement -> sorted_prev = it.ptr_;      //the new tail points backward to the old tail
      sorted_tail = newElement;                 //the new sorted tail is the newElement
    }
  }
}
template <class T>
//REMOVE AN SPECIFIC ELEMENT FROM THE MLL
typename MultiLL<T>::iterator MultiLL<T>::erase(iterator it){
  bool erased = false;                      //bool to see if the element was erased
  Node<T>* result;                          //saving the node after it is removed
  iterator it2;                             //iterator that will store the result node's iterator form 
  if(it.type == "chrono"){                  //if the iterator is chonological,we will return the chrono next                        
    result = it.ptr_->chrono_next;
    it2 = iterator(result,"chrono");
  }
  if (it.type == "sorted"){                 //if the iterator is sorted,we will return the sorted next
    result = it.ptr_->sorted_next;
    it2 = iterator(result,"sorted");
  }
  if (it.type == "random"){                 //if the iterator is random,we will return the random next
    result = it.ptr_ -> random_next;
    it2 = iterator(result,"random");
  }
  //IF THE ITERATOR IS EQUAL TO A HEAD AND A TAIL
  if ((it.ptr_) == (chrono_head) && chrono_head == (chrono_tail)){
    erased = true;
    chrono_head = NULL;
    chrono_tail = NULL;
  } 
   //IF THE ITERATOR IS A CHRONO HEAD
  else if ((it.ptr_) == (chrono_head)){
    erased = true;
    chrono_head = chrono_head->chrono_next;
    chrono_head->chrono_prev = NULL;
  }
  //IF THE ITERATOR IS THE A CHRONO TAIL
  else if ((it.ptr_) == (chrono_tail)){
    erased = true;
    chrono_tail = chrono_tail->chrono_prev;
    chrono_tail->chrono_next = NULL;
  }
   //IF THE ITERATOR IS A REGULAR CHRONO ELEMENT IN THE MLL
  else if ((it.ptr_-> chrono_prev != NULL) && (it.ptr_ -> chrono_next != NULL)) {//linking old values too each other
    erased = true;
    it.ptr_->chrono_prev -> chrono_next = it.ptr_->chrono_next;             //the previous for the iterator Node will point to the iterator Node's next
    it.ptr_->chrono_next -> chrono_prev = it.ptr_->chrono_prev;             //the next for the iterator Node will point to the iterator Node's previous
  }
  //IF THE ITERATOR IS EQUAL TO A SORTED HEAD AND SORTED TAIL(1 ELEMENT IN LIST)
  if ((it.ptr_) == (sorted_head) && sorted_head == (sorted_tail)){
    erased = true;
    sorted_head = NULL;
    sorted_tail = NULL;
  } 
  //IF THE ITERATOR IS ANY OF THE HEADS
  else if ((it.ptr_) == (sorted_head)){
    erased = true;
    sorted_head = sorted_head->sorted_next;
    sorted_head->sorted_prev = NULL;
  } 
  //IF THE ITERATOR IS THE ANY OF THE TAILS
  else if ((it.ptr_) == (sorted_tail)){
    erased = true;
    sorted_tail = sorted_tail->sorted_prev;
    sorted_tail->sorted_next = NULL;

  }
  //IF THE ITERATOR IS EQUAL TO A REGULAR SORTED ELEMENT
   else if ((it.ptr_-> sorted_prev != NULL) && (it.ptr_ -> sorted_next != NULL)) {//linking old values too each other
    erased = true;
    it.ptr_->sorted_prev -> sorted_next = it.ptr_->sorted_next;             //the previous for the iterator Node will point to the iterator Node's next
    it.ptr_->sorted_next -> sorted_prev = it.ptr_->sorted_prev;             //the next for the iterator Node will point to the iterator Node's previous 
  }
  //IF THE ELEMENT IS THE RANDOM HEAD
  if ((it.ptr_ == random_head)){
    erased = true;
    random_head = random_head -> random_next;
  }
  //IF THE ELEMENT IS CONFIRMED TO BE ERASED
  if(erased){
    size_--;                  //decrease size by one
    delete it.ptr_;           //delete the iterators's pointer
    return it2;               //return the new iterator
  }
  else 
    return it;                //if the iterator doesn't exist, return the iterator
}
//PULL A RANDOM ELEMENT FROM THE LIST AND SET IT AS THE RANDOM NEXT
template <class T>
void MultiLL<T>::random_element() {                     
  std::vector< Node<T>* > used_random_combinations;     //will hold list elements that will be shuffled
  iterator randomit = begin_chronological();            //starting the iterator at chrono_head
  for(int i=0; i<size_; i++){                           
     used_random_combinations.push_back(randomit.ptr_); //adding elements to the random list
    randomit++;
  }
  random_shuffle(used_random_combinations.begin(),used_random_combinations.end());//
  random_head =  used_random_combinations[0];                                         //
  for(int i=1; i < size_; i++){
     used_random_combinations[i-1] -> random_next = used_random_combinations[i];
  }
   used_random_combinations[size_-1] -> random_next = random_head;
}

//DO THESE LISTS LOOK THE SAME?
template <class T>
bool operator== (MultiLL<T>& left, MultiLL<T>& right) {
  if (left.size() != right.size()) return false;
  typename MultiLL<T>::iterator left_itr = left.begin();
  typename MultiLL<T>::iterator right_itr = right.begin();
  // walk over both lists, looking for a mismatched value
  while (left_itr != left.end()) {
    if (*left_itr != *right_itr) return false;
    left_itr++; right_itr++;
  }
  return true;
}

template <class T>
bool operator!= (MultiLL<T>& left, MultiLL<T>& right){ return !(left==right); }

//TRANSFER THE CONTENTS OF ONE LIST TO ANOTHER
template <class T>
void MultiLL<T>::copy_list(const MultiLL<T>&old) {
  iterator it;                             //similar to initializing,everything will initially be NULL
  chrono_head = chrono_tail =NULL;            
  sorted_head = sorted_tail =NULL;            
  random_head = NULL;     
  size_ = 0;                  
  for(it = begin_chronological(); it != end_chronological(); it++){//in chronological order
    add(it.ptr_ -> value_);               //add every element from the old to the new in chronological orders
  }
}

//DESTROY A LIST
template <class T>
void MultiLL<T>::destroy_list() {
  Node<T>* temp = chrono_head;                //temporary Node to save the head's location
  while(temp != NULL) {                       //while we have not reached the end of the list
    chrono_head = chrono_head -> chrono_next; //the new head will point to whatever the old head's next pointed to
    delete temp;                              //delete the old head since the new head is the next element
    temp = chrono_head;                       //save the new head's location since it will be changed each time the loop runs
    size_--;
  }
  chrono_head = chrono_tail = NULL;           //setting everything to NULL so the list is now empty
}
#endif
