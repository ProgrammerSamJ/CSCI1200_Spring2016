#ifndef priority_queue_h_
#define priority_queue_h_

#include <iostream>
#include <iomanip>
#include <vector>
#include <map>

// A custom templated priority queue.  The priority queue is a min
// heap (smallest values on top).  The heap is stored in a vector.
// The integer location for an element within the vector can be
// quickly looked up using a map.

// find out the current index of the element within the heap.

// ASSIGNMENT: The class implementation is incomplete.  Finish the
//   implementation of this class, and add any functions you need.


// =========================================================================

template <class T>
class PriorityQueue {
 public:
  // CONSTRUCTOR
  PriorityQueue() {}

  // =========================
  // ACCESSORS
  unsigned int size() const { return m_heap.size(); }
  T top() const;

  // =========================
  // MODIFIERS
  // add an element
  void push(T element);
  // remove the top element, or an element elsewhere in the structure
  void pop();
  void remove(T element);
  // update the priority of an element somewhere in the structure
  void update_position(T element);

  // =========================
  // for debugging
  void print_heap(std::ostream & ostr) const;
  bool check_heap() const;
  
 private:
  // =========================
  // PRIVATE ACCESSOR FUNCTIONS
  int last_non_leaf() const { return ((int)size()-1) / 2; }
  int get_parent(int i) const { assert (i > 0 && i < (int)size()); return (i-1) / 2; }
  bool has_left_child(int i) const { return (2*i)+1 < (int)size(); }
  bool has_right_child(int i) const { return (2*i)+2 < (int)size(); }
  int get_left_child(int i) const { assert (i >= 0 && has_left_child(i)); return 2*i + 1; }
  int get_right_child(int i) const { assert (i >= 0 && has_right_child(i)); return 2*i + 2; }
  // PRIVATE MODIFIER FUNCTIONS
  void percolate_up(int i);
  void percolate_down(int i);

  // =========================
  // REPRESENTATION
  // the heap is stored in a vector representation 
  // (the binary tree structure "unrolled" one row at a time)
  std::vector<T> m_heap;
  // the map stores a correpondence between elements & indices in the heap
  std::map<T,int> locations;

};

// =========================================================================


// access the top element (minimum value) in the heap
template <class T>
T PriorityQueue<T>::top() const  {
  assert(!m_heap.empty());
  return m_heap[0]; 
}


// add a new element to the heap
template <class T>
void PriorityQueue<T>::push(T element) {
  // first, verify that the element isn't already in the heap
  typename std::map<T,int>::iterator itr = locations.find(element);
  if (itr != locations.end()) {
    std::cout << "ERROR!  priority queue aleady contains " << element << std::endl;
    assert (element == itr->first);
  }
  assert (itr == locations.end());
  // add the element at the edge of heap vector and percolate up
  m_heap.push_back(element);
  locations[element] = m_heap.size()-1;
  this->percolate_up(int(m_heap.size()-1));
}


// remove the top element (minimum value) from the heap
template <class T>
void PriorityQueue<T>::pop() {
  assert(!m_heap.empty());
  int success = locations.erase(m_heap[0]);
  assert (success == 1);
  // place the last element temporarily at the top of the heap, but
  // push it down to a proper position using percolate down
  m_heap[0] = m_heap.back();
  m_heap.pop_back();
  this->percolate_down(0);
}


// remove a specific element that could be anywhere in the heap
// first we find the element in the tree
// the we check if the element is a root or not
// we then adjust all the elements it was connected to so they connect to each other
// we then percolate every element in the tree so it will be rebalanced after the removal
template <class T>
void PriorityQueue<T>::remove(T element) {
  //
  // ASSIGNMENT: Implement this function
  //
  // find the element inside the map
  typename std::map<T,int>::iterator itr =locations.find(element);
  // if the element is found, we will check its index in m_heap 
  if (itr) {
    // if the node has 0 children,we can just pop it off 
    if ( (!has_left_child(*itr)) && (!has_right_child(*itr)) ){
      // if the node is not the last node, we will replace the removed node with the last leaf node
      // this will prevent us from having to shift all the children, the tree will be balanceed
      // if it is the last leaf in the tree, we will just remove it, no shifting required
      if (*itr != m_heap[size()-1]){
        std::swap(m_heap[*itr],m_heap[size()-1]);
        *itr = get_parent(*itr);
        m_heap.erase(*itr);
        locations.erase(itr);
      }
      else{
        m_heap.erase(*itr);
        locations.erase(itr);
      }
    }
    else{
      // if the removed node has 1 child, we will shift the child node up to fill the gap 
      // the child wil become the parent
      if( (has_left_child(*itr)) || (!has_right_child(*itr)) ){
          std::swap(m_heap[*itr],m_heap[get_parent(*itr)]);
          *itr = get_parent(*itr);
          m_heap.erase(*itr); 
          locations.erase(itr);
      }
      // if the node has 2 children
      if( (!has_left_child(*itr)) && (!has_right_child(*itr)) ){
        // we comapare the children to see which is larger, the larger child will be percolated up
        unsigned int child = get_left_child(*itr);
        // if the right child is larger than the left, we will move it up the tree
        if (m_heap[get_right_child(*itr)] > m_heap[get_left_child(*itr)])
          child = get_right_child(*itr);
        percolate_up(child);
        bool twochildren = true;

        while(twochildren){
          // if after the percolate the child has 1 child,put the last leaf node in the 2nd child's place to fill the gap
          // we then percolate up to rebalance the tree
          if ((has_left_child(child)) && (!has_right_child(child))) {
            swap(m_heap[has_left_child(child)],m_heap[size()-1]);
            twochildren = false;
          }

          if( (!has_left_child(*itr)) && (!has_right_child(*itr)) ){
            // we comapare the children to see which is larger, the larger child will be percolated up
            child = get_left_child(*itr);
            // if the right child is larger than the left, we will move it up the tree
            if (m_heap[get_right_child(*itr)] > m_heap[get_left_child(*itr)])
              child = get_right_child(*itr);
          }
          // balance the tree again
          percolate_up(child);
        }
      }
    }
  }
}


// this element may have had its value change, so we should adjust the
// position of the element within the heap (it might need to move up
// or down)
template <class T>
void PriorityQueue<T>::update_position(T element) {
  typename std::map<T,int>::iterator itr = locations.find(element);
  assert (itr != locations.end());
  this->percolate_up(itr->second);
  this->percolate_down(itr->second);
}

// =========================================================================
// =========================================================================

// for debugging, print all of the data in the heap
template <class T>
void PriorityQueue<T>::print_heap(std::ostream & ostr) const {
  for (int i=0; i<(int)m_heap.size(); ++i)
    ostr << "[" << std::setw(4) << i << "] : " 
         << std::setw(6) << m_heap[i]->getPriorityValue() 
         << " " << *m_heap[i] << std::endl;
}


// for debugging, walk over the heap and check all of the elements &
// their values
template <class T>
bool PriorityQueue<T>::check_heap() const {
  if (m_heap.size() <= 1) return true;
  bool error_found = false;
  
  // first check to see if the element values are up-to-date
  for (int i=0; m_heap.size(); ++i) {
    if (m_heap[i]->CheckValue()) {
      error_found = true;
    }
  }
  
  // next loop over all nodes that have at least one child
  for (int i=0; has_left_child(i); ++i) {
    assert (has_left_child(i));
    int left_child = 2*i+1;
    // verify that this is a min heap
    // (parent is smaller value than both children
    if (m_heap[i]->getPriorityValue() > m_heap[left_child]->getPriorityValue()) {
      error_found = true;
      std::cout << "Error: at heap location " << i 
                << ", the value is greater than the value at the left child.\n";
      std::cout << "value@" << i<< "=" <<  m_heap[i]->getPriorityValue() 
                << "value@" << left_child << "=" << m_heap[left_child]->getPriorityValue() << std::endl;
      
    }
    int right_child = 2*i+2;
    if (right_child < (int)m_heap.size() && 
        m_heap[i]->getPriorityValue() > m_heap[right_child]->getPriorityValue()) {
      error_found = true;
      std::cout << "Error: at heap location " << i 
                << ", the value is greater than the value at the right child.\n";
      std::cout << "value@" << i<< "=" <<  m_heap[i]->getPriorityValue() 
                << "value@" <<right_child << "=" << m_heap[right_child]->getPriorityValue() << std::endl;
    }
  }

  if (error_found) {
    print_heap(std::cout);
  }
  return !error_found;
}


// =========================================================================
// =========================================================================

// allow the element at this location to move up
//we first check if our current Node (m_heap[i]) has a parent,if the parent is NULL or our current Node is greater then the parent,we break
//if  a parent exists,we will compare our current Node to it's parent
//if we find the current is less than the parent, we will std::swap the two
//now our current becomes the parent,we then call percolate_up until our base condition is met
template <class T>
void PriorityQueue<T>::percolate_up(int i) {
  //
  // ASSIGNMENT: Implement this function
  //
  // base case: no parent or current Node > parent
  if (!m_heap[get_parent(i)]) 
      return;
  // If our current is greater than the parent, we std::swap them
  if(m_heap[i] > m_heap[get_parent(i)]){
    std::swap(m_heap[i],m_heap[get_parent(i)]);

    // adjusting the heap vector to our std::swap
    i = get_parent(i);
    // keep moving up the queue until our base condition is met
    percolate_up(i);
  }
  return;
}

// allow the element at this location to move down
// we first check if our current Node has any children
// if a child exists,we see if 
template <class T>
void PriorityQueue<T>::percolate_down(int i) {
  //
  // ASSIGNMENT: Implement this function
  //
  //if at least one child exists
  if ((has_left_child(i)) || (has_right_child(i))) {
    // If there is a right child,see which child is greater
    if (m_heap[get_right_child(i)] && m_heap[get_right_child(i)] < m_heap[i]){
      // if the current Node is less than the left child, std::swap them
      if (m_heap[i] < m_heap[get_left_child(i)]) {
        std::swap(m_heap[i], m_heap[get_left_child(i)]);
        i = get_left_child(i);
        percolate_down(i);
      }
      // if the current Node is less than the right child, std::swap them
      if (m_heap[i] < m_heap[get_right_child(i)]) {
        std::swap(m_heap[i], m_heap[get_right_child(i)]);
        i = get_right_child(i);
        percolate_down(i);
      }
    }
    // If there is only 1 child(left child),compare current Node to it
    else if (m_heap[i] < m_heap[get_left_child(i)]) {
      std::swap(m_heap[i], m_heap[get_left_child(i)]); // value and other non-pointer member vars
      i = get_left_child(i);
      percolate_down(i);
    }
  }
 else
    return;
}

// =========================================================================
// =========================================================================
#endif
