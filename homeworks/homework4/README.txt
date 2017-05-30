HOMEWORK 4: GROCERY LISTS


NAME:  < Aaron Taylor >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< John Fantell, ALAC Tutors, TAs, cplusplus.com, Nathaniel Wheeler >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 15 >



ORDER NOTATION:
For each request/command,

i = # of different ingredients in the kitchen 
u = maximum units of a single ingredient in the kitchen 
r = # of different recipes 
k = maximum # of different ingredients in a single recipe 
v = maximum units of single ingredient in a single recipe
a = maximum # of different ingredients added with a single ’a’ command 
w = maximum units of a single ingredient added with a single ’a’ command 


command 'r' / add a recipe: O(r)

command 'a' / add ingredients to the kitchen: O(i)

command 'p' / print a recipe: O(r*k)

command 'm' / make a recipe: O(r*k*i)

command 'k' / print the contents of the kitchen: O(k)

command 's' / suggest recipes: O(r*k)


(extra credit) command 'd' / suggest dinner menu:



EXTRA CREDIT:
Describe your implementation of the "suggest dinner menu" option.



MISC. COMMENTS TO GRADER:  
(optional, please be concise!)
-the sort function was attempted at the bottom of ingredient.cpp
-the suggestion function was attempted by having the kitchen class check to see if the suggest recipe could be made,
-if the recipe could be made,the recipe would be added to a list,at the end,the list would be written to the file

