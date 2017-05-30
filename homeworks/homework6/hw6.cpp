#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <stdio.h>     
#include <stdlib.h> 
#include <ctype.h>
#include "board.h"
#include <time.h>       /* clock_t, clock, CLOCKS_PER_SEC */
#include <math.h>       /* sqrt */

//=======================
//HELPER FUNCTIONS
//=======================

int frequency_of_primes (int n) {
  int i,j;
  int freq=n-1;
  for (i=2; i<=n; ++i) for (j=sqrt(i);j>1;--j) if (i%j==0) {--freq; break;}
  return freq;
}

//CHECK TO SEE IF THE BOARDS ARE THE SAME(will prevent same solutions from being saved to the board solutions list)
bool sameboard(Board BoardA,Board &BoardB){
	std::vector< std::vector<char> > sea1 = BoardA.getSea(); //get the representations of the boards
	std::vector< std::vector<char> > sea2 = BoardB.getSea();
	for(int i = 0;i < sea1.size();i++){	
		for(int j = 0;j < sea1[i].size(); j++){
			if (sea1[i][j] != sea2[i][j])					//if we find that 2 characters on each of the boards
				return false;								//are not equal,we know that the boards are different 
		}
	}
	return true;											//if all of the characters are the same, we know the boards are the same
}

//ADDING SHIPS TO BOARD
//takes a board,a vector to be filled with board solutions,list of ships to add,an int to indicate the ship we want in the vector of 
//ship objects,x and y coordinates for location on the board,and a boolean all_boards that will tell the function to...get all solutions
// if true,get one solution is false
bool find_shiplocations(Board Board1,std::vector<Board> &BoardSolutions,std::vector<Ship> &shipNames,int shipnum,int x,int y,bool &all_boards){
	
	//Base Case for finding one solution
	if ((all_boards == false) && (BoardSolutions.size() == 1)){
		return true;
	}
	else{
		//Base Case 2 
		if (Board1.getShips().size() == shipNames.size()){		//if a boards vector of ships is the same size as the main vector of ships
																//the board is full
			bool sameBoard = false;								//boolean to show if the solution has already been suggested
			if (BoardSolutions.size() > 1){						//checking to see of the solution has already been found
				for(int i=0;i < BoardSolutions.size();i++){		//comparing the newly created board to every board in teh file
					sameBoard = sameboard(Board1,BoardSolutions[i]);
				}
			}
			if(sameBoard){										//if the board was already a solution
				return false;									//return false to make a new solution
			}
			else{
				Board1.print();
				BoardSolutions.push_back(Board1);				//the board is full,so add it to the list of solutions		
				return true;	
			}								
		}
		for(int i=0;i < Board1.getlength();i++){
			for(int j=0; j < Board1.getheight();j++){
				bool foundHspot = false;									//booleans that will determine it a ship can fit horizontally/vertically
				bool foundVspot = false;
				int a[] = {i,j};											//vector holding our current location on the board
				std::vector<int> location (a, a + sizeof(a) / sizeof(int) );//initialing the location vector

				foundHspot = Board1.check_horizontal(i,j,shipNames[shipnum]);//check if the board can fit horizontally or vertically 
				foundVspot = Board1.check_vertical(i,j,shipNames[shipnum]);			
				if (foundHspot){											//if the ship can fit horizontally
					shipNames[shipnum].addHorizontalLocation(location);		//add the location to the ship's vector of horizontal locations
					shipNames[shipnum].setorientation("horizontal");		//set the ships's orientation to horizontal
					Board1.addShip(shipNames[shipnum],i,j);  				//add the ship to the board	

					//Recursion -search every place in the board to try and fit the ship
					bool foundLocations = find_shiplocations(Board1,BoardSolutions,shipNames,shipnum+1,i,j,all_boards);
					if (!foundLocations){						  //if putting the ship at the curent location fails
						Board1.removeShip(shipNames[shipnum],i,j);//return the board to its previous state by removing the board
						return false;			
					}
				}
				else if (foundVspot){										//if the ship can fit vertically
					shipNames[shipnum].addVerticalLocation(location);		//same logic as the horizontal check above
					shipNames[shipnum].setorientation("vertical");					
					Board1.addShip(shipNames[shipnum],i,j);
					
					//Recursion -search every place in the board to try and fit the ship
					bool foundLocations = find_shiplocations(Board1,BoardSolutions,shipNames,shipnum+1,i,j,all_boards);
					if (!foundLocations){						//if putting the ship at the curent location fails
						Board1.removeShip(shipNames[shipnum],i,j);//return the board to its previous state by removing the board
						return false;
					}
				}
			}
		}
	}
 	return false;
}


//SORTING A LIST OF SHIP OBJECTS(greatest to list)
bool lengthsort(const Ship &ship1,const Ship &ship2){//sort function for ships based on size
	return ship1.getlength() > ship2.getlength();    //will sort greatest to least 
}

int main(int argc,char* argv[]) {
//=====================
//ERROR CHECKING
//=====================

	if (argc < 0) {	//are there enough arguments?
		std::cerr << "Please provide a board to read." << std::endl;
		return 1;
	}

	//OPENING THE FILE
	std::ifstream in_str(argv[1]);
	if (!in_str) { //checking if the file can be opened
		std::cerr << "Could not open " << argv[0] << " to read\n" << std::endl;
		return 1;
	}

	bool all_boards = false;  //boolean that will let us know if we need to find all solutions to the board
	//if there are less than 2 arguments given,we will just find one solution to the board
	//if there are 2 arguments given,we will assume the user wants to find all solutions to the board
	if (argc == 2){
		all_boards = true;
	}
//======================================
//PARSING THE FILE/GETTING ALL THE INFO
//======================================
	std::string word;					 //temporary string to hold words/characters from the file
	std::vector<std::string> all;		 //vector containing all information from the file
	int maxlength;						 //dimensions to be used when constructing the board
	int maxheight;			
	std::vector<std::string> rows;		 	//temporary vector to store row info
	std::vector<std::string> columns;	 	//temporary vector to store column info
	std::vector<Ship> shipNames;		 	//temporary vector to store the ship objects on the board
	std::vector< std::vector<std::string> >constraintInfo;//temporary vector to store constraint locations

	while(in_str >> word) {			  //sending wach string to the word in the file
		all.push_back(word);		  //adding everything in the file to the "all" vector
	}
	in_str.close();

	for(int i=0;i < all.size(); i++){ //getting the dimensions of the board
		if(all[i] == "board"){
			maxlength = atoi(all[i+1].c_str());	//converting the length and heignt to ints,will be used to initialize board
			maxheight = atoi(all[i+2].c_str());
		}
		if(all[i] == "rows")
				break;
	}

	for(int i=0; i < all.size(); i++){ //getting all the row sizes
		if(all[i] == "rows"){
			for(int j=i; j < all.size(); j++){
				if(!isdigit(all[j+1][0]))
					break;
				else
					rows.push_back(all[j+1]);
			}
		}
	}
	
	int constraintStart; 			   //placeholder for indice that starts constraint info in the file
	bool ColsCutoff = false;	       //boolean that will tell us when we have reached the end of the column information in the file
	for(int i=0; i < all.size(); i++){ //getting all the column sizes,the ships on the board,and the constraints
		if(all[i] == "constraint"){	   //finding the constraint placeholder
			constraintStart = i;	   //the constraint information will be one indicie after the word "constraint"
			break;
		}
		if(all[i] == "cols"){
			for(int j=i; j < all.size(); j++){
				if(!isdigit(all[j+1][0])){	  //when we see that a character is not a number,we know we are done with the col info
					ColsCutoff = true;		  //we have now reached the cutoff point for the column info
					i++;				
					break;
				}
				if(!ColsCutoff)					//if we haven't reached the cut
					columns.push_back(all[j+1]);//keep adding the column info to the vector
			}
		}
		if ((ColsCutoff) && (!isdigit(all[i][0]))){  //getting all the ships
			Ship tempShip = Ship(all[i]);			 //creating a temporary ship to hold the new ship object
			shipNames.push_back(tempShip);
		}
	}
	std::sort (shipNames.begin(), shipNames.end(), lengthsort); //Sorting all the ships by length(greatest to least)

	// std::vector<std::string> tempconstraint;		  //vector that will hold 1 constraint 
	// for(int j = constraintStart;j < all.size(); j++){ //in range of start of constraint information to the end of the file
	// 	if (all[j] == "constraint"){			      //when we reach the word "constraint",we are at 
	// 								                  //the start of a new set of constraint  information

	// 		constraintInfo.push_back(tempconstraint); //add the tempconstraint vector to the list of constraints
	// 		tempconstraint.clear();					  //clear the temp constraint vector so it can be used again
	// 	}
	// 	else{
	// 		tempconstraint.push_back(all[j]); //add the 3 constraint characters to the temp constraint vector(x,y,char)
	// 	}
	// }
//===========================
//CREATING THE BOARD OBJECTS
//===========================
	Board Board1(maxlength,maxheight,rows,columns,shipNames,constraintInfo); //saving the original board's contents
		std::vector<Board> BoardSolutions;	//vector of all the solutions to the given boards

	int x =0;							//starting at the bottom left of the board,x and y will change in find_ship
	int y = 0;
	int shipnum = 0;					//the indicie in which we start at in the list of ships

	//calling the function to find solutions to the board
	find_shiplocations(Board1,BoardSolutions,shipNames,shipnum,x,y,all_boards);

	bool sameBoard = false;								//boolean to show if the solution has already been suggested
	if (BoardSolutions.size() > 1){						//checking to see of the solution has already been found
		for(int i=0;i < BoardSolutions.size();i++){		//comparing the newly created board to every board in teh file
			sameBoard = sameboard(Board1,BoardSolutions[i]);
		}
	}
	if(sameBoard){										//if the board was already a solution
		return false;									//return false to make a new solution
	}
	else{												//if the board is not already part of the list
		BoardSolutions.push_back(Board1);				//the board is full,so add it to the list of solutions		
		return true;	
	}

	std::cout<< "Found " << BoardSolutions.size() <<" solution(s)" <<std::endl;
	//printing the boards
	for(int i=0; i < BoardSolutions.size();i++)
		BoardSolutions[i].print();
	clock_t t;
  	int f;
  	t = clock();
  	printf ("Calculating...\n");
  	f = frequency_of_primes (99999);
  	std::cout << "The number of primes lower than 100,000 is: %d\n" << f <<std::endl;
  	t = clock() - t;
  	std::cout << "It took me clicks "<< f << "seconds\n" << t << ((float)t)/CLOCKS_PER_SEC) <<std::endl;

	return 0;
}