HOMEWORK 5: MULTI LINKED LISTS


NAME:  < Aaron Taylor >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< John Fantell, ALAC Zaran Lalvani, tutor Jesse Freitas, Nathaniel Wheeler,cplusplus.com, stackoverflow.com >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.


ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 25 >



TESTING & DEBUGGING STRATEGY:
Please be concise!  



ORDER NOTATION of the member functions of MultiLL?
(in terms of n, the number of elements currently in the list)

default constructor= O(1)

copy constructor= O(n)

assignment operator= O(1)

destructor= O(n)

size= O(1)

empty= O(1)

clear= O(n)

add= O(n)

erase= O(1)

begin_chronological= O(1)

end_chronological= O(1)

begin_sorted= O(1)

end_sorted= O(1)

begin_random= O(n)


ITERATOR INVALIDATION:
In what cases will iterators of the MultiLL be invalidated?  Justify
the need for each of the restrictions placed on your implementation.
-iterating past the head or tail of a class would be a problem,depending on the iterator
you would have to make sure it's next or previous doesn't point to NULL



EXTRA CREDIT: 
Which function in your implementation can be improved by a
non-insertion sort sorting method?  Describe.




MISC. COMMENTS TO GRADER:  
Optional, please be concise!


