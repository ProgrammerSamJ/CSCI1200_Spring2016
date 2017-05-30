HOMEWORK 7: MINIBLAST


NAME:  < Aaron Taylor >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< John Fantell,Adeel Minhas, cplusplus.com >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 7 >



ANALYSIS OF PERFORMANCE OF YOUR ALGORITHM:
(order notation & concise paragraph, < 200 words)

L = length of the genome sequence
q - query length
p - number of different locations where key is found
k - key size (k-mer size)
n - number of keys

How much memory will the map data structure require (order notation for memory use)?
O(n)


What is the order notation for performance (running time) of each of
the commands?
genome filename - O(L)
kmer k - O(L log k)
query m query string - O(p*q +log p + k)
quit - O(1)
most -O(p)

EXTRA CREDIT
Add a new command to implement the database using one of the other
 data structures that we have covered so far in the course: 
vectors, lists, arrays etc. 

Compare the performance your alternative method to the homework method
by making a table of run times for each of the genomes and query 
sets provided with the homework  and compare the times to build
the index and the times to process the queries. 
Document any new commands you have added in your README file.

-New Command: "Most",finds the most common sequence of length k inside the map or vector we have created

RUNTIMES

Files:genome_small,input_small
						map				vector
build index			  0.046				  0(number too small)
process query		  0.016(longest time) 0(longest time)

Files:genome_medium,input_medium
						map				vector
build index	  		  0.141			      0.062
process query		  0.235(longest time) 0(longest time)

Files:genome_large,input_large
						map				vector
build index	  		  0.391   		      0.125
process query		  0.469(longest time) 0.016(longest time)

Files:genome_larger,input_larger
						map				vector
build index	  		  2.891			      0.266
process query		  1.656(longest time) 0.016(longest time)

These results show that while a vector may buld faster than a map,the time it takes to process each query is very similar.
MISC. COMMENTS TO GRADER:  
(optional, please be concise!)


