HOMEWORK 6: BATTLESHIP RECURSION


NAME:  < Aaron Taylor >



COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< Prof Gonsiorowski,ALAC tutor Gwen, Alac tutor Sam Wenninger, ALAC tutor Ezra Dowd,TA Katherine Colon,TA Joseph Grogan,TA Srinivasan Iyer,student John Fantell,student Adeel Minhas,
student Ethan Stackoff >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 40 >



ANALYSIS OF PERFORMANCE OF YOUR ALGORITHM:
(order notation & concise paragraph, < 200 words)
The dimensions of the board (w and h) O(w x h)
The number of ships (s)? O(s)
The total number of occupied cells (o) or open water (w)? O(o x w)
The number of constraints (c)? O(c)
The number of unknown sums (u) or unspecified ship types (t)? O(u x t)
Etc. 



SUMMARY OF PERFORMANCE OF YOUR PROGRAM ON THE PROVIDED PUZZLES:
# of solutions & approximate wall clock running time for different
puzzles for a single solution or all solutions.
Puzzle 1 = 1 solution,0.01s
Puzzle 2 = 1 solution, 0.02s
Puzzle 3 = unknown
Puzzle 4 = unknown
Puzzle 5 = unknown
Puzzle 6 = unknown
Puzzle 7 = 1 solution,0.06sPuzzle 8 = unknown
Puzzle 9 = unknown
Puzzle 10 = unknown



MISC. COMMENTS TO GRADER:  
(optional, please be concise!)
-If a constraint for a row or column was '?',it would become the maximum height or length of the row or column it was apart of. In other words, unknown constraints took on the 
 dimensions of the board
-I attempted to do as much as possible. It seems to find solutions for puzzles that have no horizontal ships(puzzle 2 for example) and known values.I also attemptred to implement
 a check to prevent diagnol or adjacent ship placement, a function to prevent the same board solutions from appearing twice, and a condition to prevent multiple solutions 
 from being found if the user did not ask for them. Other things I thought to implement but never attempted included a method to convert '.' characters to ' ' in the printing of 
 the board,a condition to check constraints on the board, and a condition to convert an unknown ship to whatever space was avaible after all other ships ahd been placed on the 
 board.




