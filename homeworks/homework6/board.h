#ifndef __board_h_
#define __board_h_
#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>     
#include <stdlib.h> 
#include <ctype.h>
#include "ship.h"

class Board{
public:
	//CONSTRUCTOR
	Board();
	Board(int maxlength,int maxheight,std::vector<std::string> &row, std::vector<std::string> &columns, 
		std::vector<Ship> &shipNames,std::vector < std::vector<std::string> > &constraintInfo);
	
	//ACCESSORS
	void print() const;
	const int getlength() const{return length;}
	const int getheight() const{return height;}
	std::vector< std::vector<char> >getSea(){return sea;}
	std::vector<int> getRow(){return lengths;}
	std::vector<int> getCol(){return heights;}
	std::vector<Ship> getShips(){return shipsonBoard;}


	//MODIFIERS
	void addShip(Ship newShip,int x,int y);
	void removeShip(Ship newShip,int x,int y);
	void addborder(Ship newShip,int x,int y);

	//HELPFUL MEMBER FUNCTIONS
	bool check_horizontal(int x,int y,Ship ship1);
	bool check_vertical(int x,int y,Ship ship1);


private:
	//REPRESENTATION
	int length;						 	 //length of the board
	int height;						 	 //height of the board
	std::vector<int> heights;			 //vector of all the column heights on the board,will be changed as ships are added
	std::vector<int> lengths;	 		 //vector of all the line lengths of the board,will be changed as ships are added

	std::vector<std::string> originalHeights;//vectors that will hold the original row and column constraits for printing the board
	std::vector<std::string> originalLengths;	

	std::vector< std::vector<std::string> > constraints;//vector of all the constraints on the board
	std::vector<Ship> shipsonBoard;  	 //vector containg all the ships on the board
	std::vector< std::vector<char> > sea;//representation of the battleship board
										 //open water will be represented by '.' until the see board is printed 
};
#endif

