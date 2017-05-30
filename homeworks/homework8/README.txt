HOMEWORK 8: QUAD TREES AND TREE ITERATION


NAME:  < Aaron Taylor >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< John Fantell, Adeel Minhas,ALAC Tutor Gwen,ALAC Tutor Sam,cplusplus.com,stackoverflow.com>

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 20 >



ORDER NOTATION ANALYSIS: 
Give the big O notation of each of the QuadTree operations and justify
your answer for the non trivial operations (please be concise!)
Analyze both the running time and the additional memory usage needed
(beyond the space allocated for the existing tree structure).  You may
assume that the tree is reasonably well balanced for all operations.


n = the number of elements in the tree


size()
  running time: O(1)
  memory usage: O(1)
-accesing memeber variable

insert()
  running time: O(log n)
  memory usage: O(log n)
-depending on the place of insertion, you would traverse the tree to the proper place
-you would never have to go through the entire tree because of the comparisons between the point to be inserted and the Nodes on the tree

find()
  running time: O(n)
  memory usage: O(n)
-the value that we could be trying to find could be the last element in the tree,thus forcing us to have to go through all the elements

height()
  running time: O(n)
  memory usage: O(n)
-function relies on a driver function to travel down to the bottom of the tree
-worst case would be that the lowest Node is at the end of the tree

begin()
  running time: O(1)
  memory usage: O(1)
-returning an iterator version ofthe root of the tree (member variable)

end()
  running time: O(1)
  memory usage: O(1)
-returning a NULL iterator

bf_begin()
  running time: O(1)
  memory usage: O(1)
-returning an iterator version ofthe root of the tree (member variable)

bf_end()
  running time: O(1)
  memory usage: O(1)
-returning a NULL iterator

operator++()
  running time: O(log n)
  memory usage: O(log n)
-since the helper functions used to traverse the tree follow strict paths, we wouldn't have to go through every single element
-we also don't have to go through every element because we have a "current location" function to give a Node's position on a tree

operator*()
  running time: O(1)
  memory usage: O(1)
-just retruning the member variable of an iterator

getLabel()
  running time: O(1)
  memory usage: O(1)
-returning a member variable of an iterator

getDepth()
  running time: O(log n)
  memory usage: O(log n)
-traveling up a tree, only taking in path starting at the Node

copy constructor
  running time: O(n)
  memory usage: O(n)
-going through all the Nodes in a tree and copying each aspect of them

assignment operator
  running time: O(1)
  memory usage: O(1)
-just creating a QuadTree and establishing member variables

destructor
  running time: O(n)
  memory usage: O(n)
-going through all the Nodes in the tree and deleting them



EXTRA CREDIT:  TREE BALANCING
How does the point insertion order affect the shape of the resulting
QuadTree object? What are specific examples of the worst case and best
case?  Discuss your stratgy for reordering the input to rebalance the
tree.  Paste example output with and without your rebalancing.






MISC. COMMENTS TO GRADER:  
(optional, please be concise!)


