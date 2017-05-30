// ===================================================================
//
// We provide the Point class and the implementation of several
// QuadTree member functions for printing.  
//
// IMPORTANT: You should modify this file to add all of the necessary
// functionality for the QuadTree class and its helper classes: Node,
// DepthIterator, and BreadthIterator.
//
// ===================================================================

#ifndef quad_tree_h_
#define quad_tree_h_

#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

// ==============================================================
// ==============================================================
// A tiny templated class to store 2D coordinates.  This class works
// with number_type = int, float, double, unsigned char (a 1 byte=8
// bit integer), short (a 2 byte=16 bit integer).

template <class number_type>
class Point {
public:
  Point(const number_type& x_, const number_type& y_) : x(x_),y(y_) {}
  // REPRESENTATION
  number_type x;
  number_type y;
};

// a helper function to print Points to STL output stream
template <class number_type>
inline std::ostream& operator<<(std::ostream &ostr, const Point<number_type> &pt) {
  ostr << "(" << pt.x << "," << pt.y << ")";
  return ostr;
}


//class declaration for Node
template <class number_type,class label_type>
class Node {
public:
  Node(const Point<number_type> pt_,const label_type& label_) : label(label_),pt(pt_),parent(NULL){
    for(int i=0;i < 4;i++){
      children[i] = NULL;
    }
  }
  label_type label;
  Point<number_type> pt;
  Node<number_type,label_type>* parent;
  Node<number_type,label_type>* children[4];

//==============================
//HELPER FUNCTIONS FOR NODES
//==============================

//function to check our Node's current location relatie to the parent
//we first check if the Node has a parent,if it does, we will iterate through their array of children,once we
//find our current Node in the array of children,we will return it'd index in the array
int current_location(){
  if (parent != NULL){
    for(int i=0;i < 4;i++){
      if (parent->children[i] != NULL){ 
        if ((pt.x == parent->children[i]->pt.x) && (pt.y == parent->children[i]->pt.y))
          return i; 
      }
    }
  }
  return 0;
}

//function for moving to the right on the level in a tree
//in this function we will look at the Node's parent and see if there is a child Node to the right of the current Node
//first we find out if out Node has a parent,then we find out where our current Node is relative to the parent
//if we find another Node in the array,we will return it immediately
//if we find that q sibling Node doesn't exist,return NULL
Node<number_type,label_type>* find_sibling(){
  if (parent != NULL){
    for(int i = this->current_location()+1;i < 4;i++){
      if (parent->children[i] != NULL){ 
         return parent->children[i]; 
      }
    }
  }
  return NULL;
}

//function to see if a node has children
//if we go through the Node's children array and find that all the elements are NULL pointers,we will know it is empty
//else,we will assume the Node has children
bool has_children(){
  unsigned int count = 0;
  for(int i=0;i < 4;i++){
    if (children[i] == NULL){count++;}
  }
  if (count == 4) { return false; }
  return true;
}

//function to find the location of a Node's child
//we will iterate through the Node's list of children,and once we find the child,we will return its index in the array
Node<number_type,label_type>* find_child(){
  for(int i=0;i < 4;i++){
    if (children[i] != NULL) { return children[i];}
  }
  return NULL;
}

//function that will return the first child of the Node's parent's sibling 
//we first find where we are relative to the current Node's parent
//we then get the parent's sibling Node(brother)
//we then find the parent's sibling's 1st child(cousin),which is found using find_child()
//then we return the cousin
//if the brother does not exist,we return NULL
//if we find that the Node's parent is a rote(parent->parent == NULL),we return the parent's first child's first child
Node<number_type,label_type>* find_cousin(){
  int i = this->current_location();
  Node<number_type,label_type>* brother = parent->find_sibling();
  if (parent->parent == NULL) {return parent->find_child()->find_child();}
  else if(brother == NULL) {return NULL;}
  else if(brother != NULL) {return brother->find_child();}
}

//function that will return the first child of the Node's parent's sibling 
//we first find where we are relative to the current Node's parent
//we then get the parent's sibling Node(brother)
//we then find the parent's sibling's 1st child(cousin)
//then we retrun the cousin
Node<number_type,label_type>* find_nephew(){
  int i = this->current_location();
  Node<number_type,label_type>* first_child = parent->find_child();
  return first_child->find_child();
}

};

template <class number_type,class label_type> class QuadTree;

//DEPTHITERATOR CLASS
template <class number_type,class label_type>
class DepthIterator {
public:
  DepthIterator() : ptr_(NULL){}
  DepthIterator(Node<number_type,label_type>* p) : ptr_(p) {}
  DepthIterator(const DepthIterator& old) : ptr_(old.ptr_) {}
  ~DepthIterator() {}
  DepthIterator& operator=(const DepthIterator& old) { ptr_ = old.ptr_;  return *this; }
  // operator* gives constant access to the value at the pointer
  const Point<number_type>& operator*() const { return ptr_->pt; }
  const label_type& getLabel() const { return ptr_->label;}
  //driver function for depth,we still start at out current Node and move up the tree
  //we will keep moving up and incrimenting depth until temp's parent is NULL
  int drive_depth(Node<number_type,label_type>* temp) {
    if (temp->parent== NULL) {return 0;}
    return 1+drive_depth(temp->parent);
  }
  int getDepth() { drive_depth(ptr_); }
  // comparions operators are straightforward
  bool operator== (const DepthIterator& rgt) { return ptr_ == rgt.ptr_; }
  bool operator!= (const DepthIterator& rgt) { return ptr_ != rgt.ptr_; }

  //pre-increment depth iterator
  //an array of visted Nodes (called visted) will be created to prevent traveling down the same path multiple times
  //if the Node has children,our iterator should be the Node's first child
  //if the Node has no children, we will check to see if it has siblings(Node's on the same level)
  //if we find that the Node has a sibling, we will return the sibling
  //if we find that the Node has no children and no siblings,we will search the tree and find a parent Node in which
  void operator++() {
    //Node has children and a sibling(we immediately return the child,because depth first moves down,not to the right)
    if ((ptr_->has_children()) && (ptr_->find_sibling() != NULL)) { 
       ptr_ =  ptr_->find_child();
    }
    //Node has no children and a sibling(we move to the right and look at the sibling)
    else if ((!ptr_->has_children()) && (ptr_->find_sibling() != NULL)) {
       ptr_ =  ptr_->find_sibling();
    }
    //Node has children and no sibling(we go to the first child)
    else if ((ptr_->has_children()) && (ptr_->find_sibling() == NULL)) { 
       ptr_ =  ptr_->find_child();
    }
    //Node has no children and no sibling(we look at the parent's sibling)
    else if ((!ptr_->has_children()) && (ptr_->find_sibling() == NULL)){
      ptr_ =  ptr_->parent->find_sibling();
    }
    else
      ptr_ = NULL;
  }
  //post-increment iterator
  DepthIterator<number_type,label_type> operator++(int) {
  DepthIterator<number_type,label_type> temp(*this);
  ++(*this);
  return temp;
  }
  

private:
  // representation
  Node<number_type,label_type>* ptr_;
};

//BreadthFirst ITERATOR CLASS
template <class number_type,class label_type>
class BreadthFirstIterator {
public:
  BreadthFirstIterator() : ptr_(NULL){}
  BreadthFirstIterator(Node<number_type,label_type>* p) : ptr_(p) {}
  BreadthFirstIterator(const BreadthFirstIterator& old) : ptr_(old.ptr_) {}
  ~BreadthFirstIterator() {}
  BreadthFirstIterator& operator=(const BreadthFirstIterator& old) { ptr_ = old.ptr_;  return *this; }
  // operator* gives constant access to the value at the pointer
  const Point<number_type>& operator*() const { return ptr_->pt; }
  const label_type& getLabel() const { return ptr_->label;}
  //driver function for depth,we still start at out current Node and move up the tree
  //we will keep moving up and incrimenting depth until temp's parent is NULL
  int drive_depth(Node<number_type,label_type>* temp) {
    if (temp->parent== NULL) {return 0;}
    return 1+drive_depth(temp->parent);
  }
  int getDepth() { return drive_depth(ptr_); }
  // comparions operators are straightforward
  bool operator== (const BreadthFirstIterator& rgt) { return ptr_ == rgt.ptr_; }
  bool operator!= (const BreadthFirstIterator& rgt) { return ptr_ != rgt.ptr_; }
  //pre-increment breadthfirst iterator
  void operator++() {
   //Node has children and a sibling
    if ((ptr_->has_children()) && (ptr_->find_sibling() != NULL)) {
        //Node is the 1st child to its parent
      if (ptr_->current_location() == 0){
         ptr_ =  ptr_->find_sibling();
      }
      //Node is the last child to its parent
      else if (ptr_->current_location() == 3){
        ptr_ =  ptr_->find_nephew();
      }
      else{
         ptr_ =  ptr_->find_sibling();
        }
    }
   //Node has no children and has a sibling
    else if ((!ptr_->has_children()) && (ptr_->find_sibling() != NULL)){
      ptr_ =  ptr_->find_sibling();
    }
   //Node has children and no sibling
    else if ((ptr_->has_children()) && (ptr_->find_sibling() == NULL)){
      if (ptr_->current_location() == 3){
        ptr_ = ptr_->find_nephew();
      }
      else
        ptr_=ptr_->find_child();
    }
   //Node has no children and no sibling
    else if ((!ptr_->has_children()) && (ptr_->find_sibling() == NULL) && (ptr_->parent != NULL)){
     ptr_ =  ptr_->find_cousin();
    }
    else{
      ptr_ = NULL;
    }
  }
  //post-increment iterator
  BreadthFirstIterator<number_type,label_type> operator++(int) {
  BreadthFirstIterator<number_type,label_type> temp(*this);
  ++(*this);
  return temp;
  }

private:
  // representation
  Node<number_type,label_type> *ptr_;
};

//class declaration for quad tree
template <class number_type,class label_type>
class QuadTree {
public:
  //constructors
  QuadTree() : root_(NULL), size_(0) , height_(-1){}
  QuadTree(const QuadTree<number_type,label_type>& old) : size_(old.size_),height_(old.height_) { 
    root_ = this->copy_tree(old.root_); }
  ~QuadTree() { this->destroy_tree(root_);  root_ = NULL; }
  QuadTree& operator=(const QuadTree<number_type,label_type>& old) {
    if (&old != this) {
      this->destroy_tree(root_);
      root_ = this->copy_tree(old.root_);
      size_ = old.size_;
      height_ = old.height_;
    }
    return *this;
  }
  //accessors
  const int size() const {return size_;}

  //driver fucntion for finding the height of the tree
  //we will start at a Node on the tree and check the height of each of its children
  //we are basically travelling down the tree and adding to the total when we reach the bottom
  int drive_height(Node<number_type,label_type> *temp){
    if(temp == NULL)
      return -1;
    else{
      int max1 = std::max(drive_height(temp->children[0]),drive_height(temp->children[1]));
      int max2 = std::max(drive_height(temp->children[2]),drive_height(temp->children[3]));
      return 1 + std::max(max1,max2);
    }
  }

  //finding the height of the tree,we start at the top and run the driver function 
  //the trees height memeber variable will be changed to the driver functions output
  int height() {

    height_ = drive_height(root_);
    return drive_height(root_);
  }

  typedef  DepthIterator<number_type,label_type> iterator;
  typedef  BreadthFirstIterator<number_type,label_type> bf_iterator;


  //driver fucntion for find, this is where the recursion will occur
  iterator drive_find(const number_type &x_,const number_type &y_,Node<number_type,label_type>* newroot){
  int position = -1;
  if (newroot == NULL)
    return iterator(NULL);
  if ((x_ == newroot->pt.x) && (y_ == newroot->pt.y)){
    return newroot;
  }
  //1st quadrant
  if ((x_ < newroot->pt.x) && (y_ < newroot->pt.y)){ position = 0; }
  //2nd quadrant
  else if ((x_ > newroot->pt.x) && (y_ < newroot->pt.y)){ position = 1; }
  //3rd quadrant
  else if ((x_ < newroot->pt.x) && (y_ > newroot->pt.y)){ position = 2; }
  //4th quadrant
  else if ((x_ > newroot->pt.x) && (y_ > newroot->pt.y)){ position = 3; }
  return drive_find(x_, y_,newroot->children[position]); 
}

  //find a node on the quad tree
  iterator find(const number_type x_,const number_type y_){
    return drive_find(x_,y_,root_);
  }

  //driver function for the insert
  //will take as parameters a node to be inserted into the tree (temp) and a root to place the node at (newroot)
  //the position will be set to an arbitrary number
  //if the point has already been added(the x and y coordinates are in the tree),we will immediately return false
  //then we will find the proper quadrant that the Node should be placed in(basically finding the proper placement in the child array)
  //if the we find that the position we are looking at is NULL,we want to insert the point there
  //if it is not NULL,we will step down the tree until we hit one of the conditions that return a bool
  std::pair<iterator,bool> insert_node(Point<number_type> pt_,label_type label_,Node<number_type,label_type>* newroot){
    int position = 20;
    if ((pt_.x == newroot->pt.x) && (pt_.y == newroot->pt.y)){ 
      return std::pair<iterator,bool>(newroot, false); 
    }
    //1st quadrant
    else if ((pt_.x < newroot->pt.x) && (pt_.y < newroot->pt.y)){ position = 0;}
    //2nd quadrant
    else if ((pt_.x > newroot->pt.x) && (pt_.y < newroot->pt.y)){ position = 1;}
    //3rd quadrant
    else if ((pt_.x < newroot->pt.x) && (pt_.y > newroot->pt.y)){ position = 2;}
    //4th quadrant
    else if ((pt_.x > newroot->pt.x) && (pt_.y > newroot->pt.y)){ position = 3;}

    if(newroot->children[position] == NULL) {
      Node<number_type,label_type>* temp = new Node<number_type,label_type>(pt_,label_);
      newroot->children[position] = temp;
      temp->parent = newroot;
      this->size_++;
      return std::pair<iterator,bool>(temp, true);
    }
    else {
      return insert_node(pt_,label_,newroot->children[position]);
    }
  }
  


  //INSERTING A NODE INTO THE QUAD TREE
  //the function takes a point object and a label as parameters,it then creates a pointer to a node with the parameters
  //if the tree is empty,the insert temp will become the root of the tree
  //the boolean "added" will determine if the element was actually added to the quad tree or not,
  //if added is true, we will return the pair, else, we will return a false pair
  std::pair<iterator,bool> insert(const Point<number_type> pt_,const label_type label_){
    if (root_ == NULL){
      root_ = new Node<number_type,label_type>(pt_,label_);
      this->size_++;
      return std::pair<iterator,bool>(iterator(root_), true);
     }
    else{
     return insert_node(pt_,label_, root_);
    }
  }

  
  //ITERATORS
  //iterator to the beginning of the quad tree
  iterator begin() const { 
    if (!root_) return iterator(NULL);
    Node<number_type,label_type> *temp = root_;
    return iterator(temp);
    
  }

  //iterator to the end of the quad tree
  iterator end() const { return iterator(NULL); }

  //iterator to the breadth first beginning of the quad tree
  bf_iterator bf_begin() const{
    if (!root_) return bf_iterator(NULL);
    Node<number_type,label_type> *temp = root_;
    return bf_iterator(temp);
   }

  //iterator to the breadth first end of the quad tree
  bf_iterator bf_end() const{return bf_iterator(NULL); }

  // ==============================================================
  // PROVIDED CODE : QUAD TREE MEMBER FUNCTIONS FOR PRINTING
  // ==============================================================

  // NOTE: this function only works for quad trees with non negative
  // integer coordinates and char labels

 // NOTE2: this function assumes that no two points have the same x
  // coordinate or the same y coordinate.

  // plot driver function
  // takes in the maximum x and y coordinates for these data points
  // the optional argument draw_lines defaults to true
  
  
  void plot(int max_x, int max_y, bool draw_lines=true) const {
    // allocate blank space for the center of the board
    std::vector<std::string> board(max_y+1,std::string(max_x+1,' '));
    // edit the board to add the point labels and draw vertical and
    // horizontal subdivisions
    plot(root_,board,0,max_x,0,max_y,draw_lines);
    // print the top border of the plot
    std::cout << "+" << std::string(max_x+1,'-') << "+" << std::endl;
    for (int i = 0; i <= max_y; i++) {
      // print each row of the board between vertical border bars
      std::cout << "|" << board[i] << "|" << std::endl;
    }
    // print the top border of the plot
    std::cout << "+" << std::string(max_x+1,'-') << "+" << std::endl;
  }

  // actual recursive function for plotting
  void plot(Node<number_type,label_type> *p, std::vector<std::string> &board,
            int x_min, int x_max, int y_min, int y_max, bool draw_lines) const {
    // base case, draw nothing if this node is NULL
    if (p == NULL) return;
    // check that the dimensions range of this node make sense
    assert (x_min >= 0 && x_min <= x_max);
    assert (y_min >= 0 && y_min <= y_max);
    assert (board.size() >= y_max);
    assert (board[0].size() >= x_max);
    // verify that the point stored at this node fits on the board
    assert (p->pt.y >= 0 && p->pt.y < board.size());
    assert (p->pt.x >= 0 && p->pt.x < board[0].size());
    // draw the vertical and horizontal bars extending across the
    // range of this node
    if (draw_lines) {
      for (int x = x_min; x <= x_max; x++) {
        board[p->pt.y][x] = '-';
      }
      for (int y = y_min; y <= y_max; y++) {
        board[y][p->pt.x] = '|';
      }
    }
    // draw this label
    board[p->pt.y][p->pt.x] = p->label;
    // recurse on the 4 children
    plot(p->children[0],board,x_min ,p->pt.x-1,y_min ,p->pt.y-1,draw_lines);
    plot(p->children[1],board,p->pt.x+1,x_max ,y_min ,p->pt.y-1,draw_lines);
    plot(p->children[2],board,x_min ,p->pt.x-1,p->pt.y+1,y_max ,draw_lines);
    plot(p->children[3],board,p->pt.x+1,x_max ,p->pt.y+1,y_max ,draw_lines);
  }


  // ==============================================================

  // prints all of the tree data with a pre-order (node first, then
  // children) traversal of the tree structure

  // driver function
  void print_sideways() const { print_sideways(root_,""); }

  // actual recursive function
  void print_sideways(Node<number_type,label_type>* p, const std::string &indent) const {
    // base case
    if (p == NULL) return;
    // print out this node
    std::cout << indent << p->label << " (" << p->pt.x << "," << p->pt.y << ")" << std::endl;
    // recurse on each of the children trees
    // increasing the indentation
    print_sideways(p->children[0],indent+"  ");
    print_sideways(p->children[1],indent+"  ");
    print_sideways(p->children[2],indent+"  ");
    print_sideways(p->children[3],indent+"  ");
  }

private:
  Node<number_type,label_type>* root_;
  unsigned int size_;
  int height_;


  Node<number_type,label_type>* copy_tree(Node<number_type,label_type>* old_root) {
    if (old_root != NULL)
    {
        Node<number_type,label_type>* temp = new Node<number_type,label_type>(old_root->pt,old_root->label);
        temp->children[0] = copy_tree(old_root->children[0]);
        temp->children[1] = copy_tree(old_root->children[1]);
        temp->children[2] = copy_tree(old_root->children[2]);
        temp->children[3] = copy_tree(old_root->children[3]);
        return temp;    
    }
    else
        return NULL; 
  }

  //destroy a tree
  void destroy_tree(Node<number_type,label_type>*& p) {
  if (p != NULL) {
    destroy_tree(p->children[0]);
    destroy_tree(p->children[1]);
    destroy_tree(p->children[2]);
    destroy_tree(p->children[3]);
    delete p;
    p = NULL;
    size_ = 0;
  }
}
};
// ==============================================================
// ==============================================================


#endif
