#include "board.h"
#include "ship.h"
#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>     
#include <stdlib.h> 
#include <ctype.h>
#include <algorithm>
#include "ship.h"

//=================
//CONSTRUCTOR
//=================
Board::Board(){}

Board::Board(int maxlength,int maxheight,std::vector<std::string> &rows, std::vector<std::string> &columns, 
	std::vector<Ship> &shipNames,std::vector < std::vector<std::string> > &constraintInfo){
	//member variable info can be found in the header file
	length = maxlength;
	height = maxheight;
	originalHeights = columns;
	originalLengths = rows;
	constraints = constraintInfo;

	//CREATING THE LENGTH CONSTRAINTS FOR EACH ROW
	for(int i=0;i < rows.size(); i++){
		int temp;
		if(rows[i] == "?"){
			temp = length;
			lengths.push_back(temp);
		}
		else{
			temp = atoi(rows[i].c_str());
			lengths.push_back(temp);
		}

	}

	//CREATING THE HEIGHT CONSTRAINTS FOR EACH COLUMN
	for(int i=0; i < columns.size(); i++){
		int temp;
		if(columns[i] == "?"){
			temp = height;
			heights.push_back(temp);
		}
		else{
			temp = atoi(columns[i].c_str());
			heights.push_back(temp);
		}
	}

	//initialize the representation of ythe board
	for(int i=0;i < length; i++){
		std::vector<char> temp(height,'.');
		sea.push_back(temp);
	}
	
	//ADDING CONSTRAINTS TO THE BOARD
	if (constraints.size() > 0){							//adding constraints to the board
		for(int i =0;i < constraints.size();i++){			//looping through all the constraints
			for(int j=0; j < constraints[i].size();j++){	//looking at a specific constraint
				int tempx = atoi(constraints[i][0].c_str());//temporary variables to store x,y and character
				int tempy = atoi(constraints[i][1].c_str());
				char tempchar = constraints[i][2][0];     
				sea[tempx][tempy] = tempchar;               //add the constraint to the board
			}
		}
	}
}
//================
//ACCESSORS
//================

//PRINTING THE BOARD
void Board::print() const{
	std::cout<< "Solution:" <<std::endl;
	for(int i = 0; i < shipsonBoard.size(); i++){
		std::cout<< shipsonBoard[i].getname() << ' ' << shipsonBoard[i].getx() << ' ' << 
		shipsonBoard[i].gety() << ' '<<shipsonBoard[i].getorientation() << std::endl;
	}

	std::cout << '+' << std::string(height, '-') << '+' <<std::endl;
	for(int i = 0; i < length; i++){
		for(int j = 0; j < height; j++){
			char temp = sea[i][j];
			if (temp == '.'){
				if (j == 0)
					std::cout<< "|" << temp;
				else if (j == height-1)
					std::cout<< temp << "|" << originalLengths[i] << std::endl;
				else
					std::cout<< temp;
			}
			else{
				if (j == 0)
					std::cout<< "|" << temp;
				else if (j == height-1)
					std::cout<< temp << "|" << originalLengths[i] << std::endl;
				else
					std::cout<< temp;
			}
		}
	}
	std::cout << '+' << std::string(height, '-') << '+' <<std::endl;
	std::cout<< ' ';

	for(int i = 0; i < height; i++){
		std::cout<< originalHeights[i];
	}
	std::cout<<' '<<std::endl;
}

//============
//MODIFIERS
//============

//ADDING A SHIP TO THE BOARD
//when a ship is added,the constraints for the board will change (-1 or -length of the ship depending on the location and orientation)
//the boards representation will change as well
void Board::addShip(Ship newShip,int x,int y){
	
	newShip.setorigin(x,y);			             //set the ship's leftmost or uppermost piece location
	
	shipsonBoard.push_back(newShip);  			 //adding the ship to the boards stored ships     

	if(newShip.getorientation() == "horizontal"){//if the ship was added horizontally
		lengths[x] -= newShip.getlength();   	 //it will also reduce each column a piece of theship falls in by one
		for(int i=y; i< y+newShip.getlength(); i++){
			heights[y] -= 1;
		}
		if(newShip.getname() == "submarine")	 //if the ship is a sub,one character will be changed
			sea[x][y] = 'o';
		else{
			for(int i=0; i < length;i++){		 //changing the characters of the columns the ship is being placed in
				if (i == x){
					for(int j=y; j< y+newShip.getlength(); j++){
						if(j == y)						  //front of the ship
							sea[x][j] = '<';
						else if(j == (y+newShip.getlength())-1)//the end of the ship
							sea[x][j] = '>';
						else							  //middle of the ship
							sea[x][j] = 'X';
					}
				}
			}
		}
	}


	if(newShip.getorientation() == "vertical"){ //if the ship was added vertically
		heights[y] -= newShip.getlength();		//it will also reduce each row a piece of the ship falls in by one
		for(int i=x;i < x+newShip.getlength(); i++){
			lengths[i] -= 1;
		}
		if(newShip.getname() == "submarine")	//if the ship is a sub,only one character will be changed
			sea[x][y] = 'o';
		else{
			for(int i=x; i < x+newShip.getlength();i++){//changing the rows the ship is being placed in	
				if(i == x){						 	 //front of the ship
					sea[i][y] = '^';
				}
				else if(i == (x+newShip.getlength())-1){	 //the end of the ship
					sea[i][y] = 'v';
				}
				else{							     //the midle of the ship
					sea[i][y] = 'X';
				}
			}
		}
	}
}

//REMOVE SHIP FROM THE BOARD
void Board::removeShip(Ship newShip,int x,int y){
	for(int i= 0;i < shipsonBoard.size();i++){
		//once we find the ship on the board
		if ((newShip.getx() == shipsonBoard[i].getx()) && (newShip.gety() == shipsonBoard[i].gety())){
			if(newShip.getorientation() == "horizontal"){          //if the ship was added horizontally
				lengths[x] += newShip.getlength();   	           //it will increase each column a piece of theship falls in by one
				for(int i=y; i< y+newShip.getlength(); i++){
					heights[y] += 1;
				}
				if(newShip.getname() == "submarine")	           //if the ship is a sub,one character will be reset
					sea[x][y] = '.';
				else{          
					for(int i=0; i < length;i++){		           //changing the characters of the columns the ship is being placed in
						if (i == x){
							for(int j=y; j< y+newShip.getlength(); j++){
								if(j == y)						  //front of the ship
									sea[x][j] = '.';
								else if(j == (y+newShip.getlength())-1)//the end of the ship
									sea[x][j] = '.';
								else							  //middle of the ship
									sea[x][j] = '.';
							}
						}
					}
				}
			}
			if(newShip.getorientation() == "vertical"){         //if the ship was added vertically
				heights[y] -= newShip.getlength();		        //it will also reduce each row a piece of the ship falls in by one
				for(int i=x;i < x+newShip.getlength(); i++){
					lengths[i] -= 1;
				}
				if(newShip.getname() == "submarine")	        //if the ship is a sub,only one character will be reset
					sea[x][y] = '.';
				else{
					for(int i=x; i < x+newShip.getlength()-2;i++){//changing the rows the ship is being placed in	
						if(i == x){						 	    //front of the ship
							sea[i][y+2] = '.';
						}
						else if(i == (x+newShip.getlength())-1){//the end of the ship
							sea[i][y] = '.';
						}
						else{							        //the midle of the ship
							sea[i][y] = '.';
						}
					}
				}
			}
			shipsonBoard.pop_back();              			    //remove the ship from the board's list of stored ships
		} 
	}
}

//ADDING A BORDERTO A SHIP TO PREVENT ADJACENT AND DIAGNOL PLACEMENT
void Board::addborder(Ship newShip,int x,int y){	
	//'X' wiil represent the border of a ship/an nother area that can't have a ship placed
	if(newShip.getorientation() == "horizontal"){		//if the ship is horizontal
		if(x == 0){										//top row of the board
			for(int i=0;i < y+newShip.getlength();i++){
				sea[x+1][y] ='x';
			}

		}
		if(x != 0){										//middle row of the board
			for(int i=0;i < y+newShip.getlength();i++){
				sea[x+1][y] = 'x';
				sea[x-1][y] ='x';
			}
		}
		if(x == length-1){								//last row of the board
			for(int i=0;i < y+newShip.getlength();i++){
				sea[x-1][y] = 'x';
			}
		}
	}	
	if(newShip.getorientation() == "vertical"){			//if the ship is vertical
		if(y == 0){										//first column of the board
			for(int i=0;i < y+newShip.getlength();i++){
				sea[x][y+1] ='x';
			}
		}
		if(y != 0){										//middle column of the board
			for(int i=0;i < y+newShip.getlength();i++){
				sea[x][y-1] = 'x';
				sea[x][y+1] ='x';
			}
		}
		if(y == length-1){								//last column of the board
			for(int i=0;i < y+newShip.getlength();i++){
				sea[x][y-1] = 'x';
			}
		}
	}
}

//===========================
//HELPING MEMBER FUNCTIONS
//===========================

//CHECK TO SEE IF THE SHIP WILL FIT HORIZONTALLY ON THE BOARD
//involves looking through at a single piece and looking at horizontal and vertical placement to see if 
//the ship's left piece can start at that location horizontally
bool Board::check_horizontal(int x,int y,Ship ship1){ //x and y will be the piece's location on the board
	if ((x >= length) || (y >= height)){ 		//if x or y go out of the boundaries of the board,it can't be added at that point
		
		return false;
	}
	
	if(sea[x][y] != '.'){						//if the space is already filled in,return false
		
		return false;
	}
	int rowConstraint =	lengths[x];				//getting the limits for the row the ship is being placed in
	if (rowConstraint< ship1.getlength()){
		
		return false;							//if the row is full,return false,the ship can't be added at this point
	}
	//check to see if at this placement,the ship will go off the board 
	if (ship1.getlength()+y > length){//if the length of the ship is greater than the length of the board,
		
		return false;				  //return false, the ship can't be added at this point
	}
	//can the columns hold the ship's pieces					
	for(int i=y;i < y+(ship1.getlength());i++){	//getting the heights of the columns in the range of the leftmost piece of the ship
		
											   	//to the last piece of the ship
		if (heights[i] == 0)					//if one of the columns that a piece of the ship is going into is full
			return false;						//or the constraint for one of the colums is 0,we can't add the ship at this point
	}
	//checking to see if the place we are putting the ship is all open water
	for(int i=0;i < length; i++){
		if(i == x){										//once we find the row we are looking for
			for(int j=0; j < height; j++){			    //check and see if the row is all open water(all '.')
				if(sea[i][j] != '.')					//if we find that the space where we are putting the ship isn't all open water
					
					return false;						//return false, the ship can't be added at this point
			}
		}
	}
	return true;								//if it passes all the cheks,the ship can be added horizontally
}

// //CHECK TO SEE IF THE PIECE WILL FIT VERTICALLY ON THE BOARD
//involves looking through at a single piece and looking down and to the right to see if 
//the ship's left piece can start at that location vertically
bool Board::check_vertical(int x,int y,Ship ship1){ //x and y will be the piece's location on the board
	if ((x >= length) || (y >= height))			//if x or y go out of the boundaries of the board,it can't be added at that point
		return false;

	if(sea[x][y] != '.') 						//if the space is already filled in,return false
		return false;

	int colConstraint =	heights[y];				//getting the limits for the column the ship is being placed in
	if (colConstraint< ship1.getlength())
		return false;							//if the column is full,return false,the ship can't be added at this point

	//check to see if at this placement,the ship will go off the board 
	if (ship1.getlength()+x > height) //if the length of the ship is greater than the max height of the board,
		return false;				  //return false, the ship can't be added at this point

					
	for(int i=x;i < x+(ship1.getlength());i++){	//getting the length of the columns in the range of the leftmost piece of the ship
											   	//to the last piece of the ship
		if (lengths[i] == 0)					//if one of the columns that a piece of the ship is going into is full
			return false;						//or the constraint for one of the colums is 0,we can't add the ship at this point
	}
	
	//seeing if the column we are putting the ship in is all open water(all '.')
	for(int i=0;i < length; i++){
		for(int j=0; j < height; j++){
			if(j == y){									//once we find the column we are looking for
				if(sea[i][j] != '.')					//if we find that the space where we are putting a piece isnt open water
					return false;						//return false, the ship can't be added at this point
			}
		}
	}

	return true;								//if it passes all the checks,the ship can be added vertically
}
