#include "tetris.h"
#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
using namespace std;
Tetris::Tetris(int w) {//constructors for the class will be first and last name
	width = w;
	max_height = 0;
	min_height = 0;
	heights = new int[width];
	for (int i=0;i<width;i++) {
		heights[i] = 0;
	}
	data = new char*[width];
	for (int i=0;i<width;i++) {
		data[i] = NULL;
	}
}
//getting the width of the tetris board
int Tetris::get_width() const{
	return width;
}
//getting the height of the highest column
int Tetris::get_max_height() const{
	int max_height = 0;
	for (int n=0;n<width;n++) { //looping throught the height array to see which is the highest
		if(heights[n] > max_height) {
			max_height = heights[n];
		}
	}
	return max_height;
}
//getting the minimum height
int Tetris::get_min_height() const{
	int min_height = 2000; //setting an extreme min just for the condition
	for (int n=0;n<width;n++) { //looping through the heights
		if(heights[n] < min_height) { //if the height 
			min_height = heights[n];
		}
	}
	return min_height;
}
//counting the number of squares on the tetris board
int Tetris::count_squares(){
	int squares = 0;
	for (int i=0;i<width;i++) {
		for (int j=0;j< heights[i];j++) {
			if (data[i][j]!=' ') { //if the charcter is not a space, that means there is a square
				squares += 1; //squares (a member variable of the total squares) increases by 1 if the condition is true
			}
		}
	}
	return squares;
}
//checking to see if the piece can be fit in at that rotation
bool Tetris::bound_check(int placement,int piece_width) {
	if (placement+piece_width > width) { //if the length of the piece stretches  past the board return false
		return false; //false signifies that it can not be fit on the board
	}
	else {
		return true;  //shows the piece is within the bounds of the board
	}
}

//will return the max of the heights of the columns in a range when adding a new piece
int Tetris::local_max_height(int range,int range2) { //range1 = leftmost place,range2 = rightmost place
	int max = 0; //setting an extreme for the max so it will easily be replaced
	for(int i = range;i <= range2;i++) {
		if (heights[i] > max) {
			max = heights[i];
		}
	}return max;
}
//function for resizing a column,deleting the old one, and replacing its values,also changes the heights array
void Tetris::resize(int old_placement,int new_column_height,int square_count,char piece) {
	new_column_height += square_count; //will be the now be the old column height + the number of squared being added
	char *pointer_column = new char[new_column_height]; //establishing a new column with the adjusted height
	for (int i=0;i<new_column_height;i++) { //bounds will be from the original highest height to the new highest height
		//this will result in the space character being added at all places
		pointer_column[i] = ' '; //now the character will be added to the column
	}
	for (int i=0;i<heights[old_placement];i++) { //loop storing the old coloumn's values in the new column,will replace spaces that should be blocks
		pointer_column[i] = data[old_placement][i];
	}
	for (int i=new_column_height-square_count;i<new_column_height;i++) { //bounds will be from the original highest height to the new highest height
		//this will result in the piece character being added at the start of the old height until the the top of the new column
		pointer_column[i] = piece; //now the character will be added to the column
	}
	delete []data[old_placement];  //deleting the old column from data
	data[old_placement] = pointer_column; //setting the old space in data equal to the new column
	heights[old_placement] = new_column_height;  //changing the height in the heights array
}
//special resize for L
void Tetris::resize_L(char piece,int rotation,int placement){
	int piece_max_height; ///will be used to determine the highest column
	if (piece == 'L') {
		if (rotation == 90) {
			piece_max_height = local_max_height(placement,placement+2); //finding the highest column
			if ((heights[placement] < heights[placement+1] || heights[placement] <= heights[placement+2])) { //if the 2nd column of 3rd column is the highest
				char *pointer_column = new char[piece_max_height+1]; //establishing a new column with the adjusted height
				char *pointer_column2 = new char[piece_max_height+1];
				char *pointer_column3 = new char[piece_max_height+1];
				for (int i=0;i<piece_max_height+1;i++) { 
					pointer_column[i] = ' '; //adding the ' ' character to every array as a default
					pointer_column2[i] = ' ';
					pointer_column3[i] = ' ';
				}
				for (int i=0;i<heights[placement];i++) { //loop storing the old coloumn's values in the new column,will replace spaces that should be blocks
					pointer_column[i] = data[placement][i];
				}
				for (int i=0;i<heights[placement+1];i++) { //loop storing the old coloumn's values in the new column,will replace spaces that should be blocks
					pointer_column2[i] = data[placement+1][i];
				}
				for (int i=0;i<heights[placement+2];i++) { //loop storing the old coloumn's values in the new column,will replace spaces that should be blocks
					pointer_column3[i] = data[placement+2][i];
				}
				///////ADDING NEW BLOCKS TO THE BOARD
				for (int i=piece_max_height;i<piece_max_height+1;i++) { //bounds will be from the original highest height to the new highest height
					pointer_column[i] = piece; //now the character will be added to the column
				}
				for (int i=piece_max_height;i<piece_max_height+1;i++) { //bounds will be from the original highest height to the new highest height
					pointer_column2[i] = piece; //now the character will be added to the column
					pointer_column3[i] = piece;
				}
				//DELETING DATA,REPLACING DATA,CHANGING HEIGHS ARRAY
				delete []data[placement]; 
				delete []data[placement+1];
				delete []data[placement+2]; 
				data[placement] = pointer_column;
				data[placement+1] = pointer_column2;
				data[placement+2] = pointer_column3;
				heights[placement] = piece_max_height+1;
				heights[placement+1] = piece_max_height+1;
				heights[placement+2] = piece_max_height+1;
			}
			else { //if the first column Is the highest
				char *pointer_column = new char[piece_max_height+2]; //establishing a new column with the adjusted height
				char *pointer_column2 = new char[piece_max_height+2];
				char *pointer_column3 = new char[piece_max_height+2];
				for (int i=0;i<piece_max_height+2;i++) { 
					pointer_column[i] = ' '; //addint the ' ' character to every array as a default
					pointer_column2[i] = ' ';
					pointer_column3[i] = ' ';
				}
				//ADDING OLD PIECES TO THE BOARD
				for (int i=0;i<heights[placement];i++) { //loop storing the old coloumn's values in the new column,will replace spaces that should be blocks
					pointer_column[i] = data[placement][i];
				}
				for (int i=0;i<heights[placement+1];i++) { //loop storing the old coloumn's values in the new column,will replace spaces that should be blocks
					pointer_column2[i] = data[placement+1][i];
				}
				for (int i=0;i<heights[placement+2];i++) { //loop storing the old coloumn's values in the new column,will replace spaces that should be blocks
					pointer_column3[i] = data[placement+2][i];
				}
				///////ADDING NEW BLOCKS TO THE BOARD
				for (int i=piece_max_height;i<piece_max_height+2;i++) { //bounds will be from the original highest height to the new highest height
					pointer_column[i] = piece; //now the character will be added to the column
				}
				for (int i=piece_max_height+1;i<piece_max_height+2;i++) { //bounds will be from the original highest height to the new highest height
					pointer_column2[i] = piece; //now the character will be added to the column
					pointer_column3[i] = piece;
				}
				//DELETING DATA,REPLACING DATA,CHANGING HEIGHS ARRAY
				delete []data[placement]; 
				delete []data[placement+1];
				delete []data[placement+2]; 
				data[placement] = pointer_column;
				data[placement+1] = pointer_column2;
				data[placement+2] = pointer_column3;
				heights[placement] = piece_max_height+2;
				heights[placement+1] = piece_max_height+2;
				heights[placement+2] = piece_max_height+2;
			}}
		if (rotation == 180) {
			piece_max_height = local_max_height(placement,placement+1);
			if ((heights[placement] <= heights[placement+1])) {
				char *pointer_column = new char[piece_max_height+3]; //establishing a new column with the adjusted height
				char *pointer_column2 = new char[piece_max_height+3];
				for (int i=0;i<piece_max_height+3;i++) { 
					pointer_column[i] = ' '; //addint the ' ' character to every array as a default
					pointer_column2[i] = ' ';
				}
				//ADDING OLD PIECES TO THE BOARD
				for (int i=0;i<heights[placement];i++) { //loop storing the old coloumn's values in the new column,will replace spaces that should be blocks
					pointer_column[i] = data[placement][i];
				}
				for (int i=0;i<heights[placement+1];i++) { //loop storing the old coloumn's values in the new column,will replace spaces that should be blocks
					pointer_column2[i] = data[placement+1][i];
				}
				///////ADDING NEW BLOCKS TO THE BOARD
				for (int i=piece_max_height+2;i<piece_max_height+3;i++) { //bounds will be from the original highest height to the new highest height
					pointer_column[i] = piece; //now the character will be added to the column
				}
				for (int i=piece_max_height;i<piece_max_height+3;i++) { //bounds will be from the original highest height to the new highest height
					pointer_column2[i] = piece;
				}
				delete []data[placement]; 
				delete []data[placement+1];
				data[placement] = pointer_column;
				data[placement+1] = pointer_column2;
				heights[placement] = piece_max_height+3;
				heights[placement+1] = piece_max_height+3;
			}
			else {
				char *pointer_column = new char[piece_max_height+1]; //establishing a new column with the adjusted height
				char *pointer_column2 = new char[piece_max_height+1];
				for (int i=0;i<piece_max_height+1;i++) { 
					pointer_column[i] = ' '; //adding the ' ' character to every array as a default
					pointer_column2[i] = ' ';
				}
				//ADDING OLD PIECES TO THE BOARD
				for (int i=0;i<heights[placement];i++) { //loop storing the old coloumn's values in the new column,will replace spaces that should be blocks
					pointer_column[i] = data[placement][i];
				}
				for (int i=0;i<heights[placement+1];i++) { //loop storing the old coloumn's values in the new column,will replace spaces that should be blocks
					pointer_column2[i] = data[placement+1][i];
				}
				///////ADDING NEW BLOCKS TO THE BOARD
				for (int i=piece_max_height;i<piece_max_height+1;i++) { //bounds will be from the original highest height to the new highest height
					pointer_column[i] = piece; //now the character will be added to the column
				}
				for (int i=piece_max_height-2;i<piece_max_height+1;i++) { //bounds will be from the original highest height to the new highest height
					pointer_column2[i] = piece;
				}
				delete []data[placement]; 
				delete []data[placement+1];
				data[placement] = pointer_column;
				data[placement+1] = pointer_column2;
				heights[placement] = piece_max_height+1;
				heights[placement+1] = piece_max_height+1;
			}	
		}
		if (rotation == 270) {
			piece_max_height = local_max_height(placement,placement+2);
			char *pointer_column = new char[piece_max_height+1]; //establishing a new column with the adjusted height
			char *pointer_column2 = new char[piece_max_height+1];
			char *pointer_column3 = new char[piece_max_height+2];
			for (int i=0;i<piece_max_height+1;i++) { 
				pointer_column[i] = ' ';
				pointer_column2[i] = ' ';
			}
			for (int i=0;i<piece_max_height+2;i++) {
				pointer_column3[i] = ' ';
			}
			for (int i=0;i<heights[placement];i++) { //loop storing the old coloumn's values in the new column,will replace spaces that should be blocks
				pointer_column[i] = data[placement][i];
			}
			for (int i=0;i<heights[placement+1];i++) { //loop storing the old coloumn's values in the new column,will replace spaces that should be blocks
				pointer_column2[i] = data[placement+1][i];
			}
			for (int i=0;i<heights[placement+2];i++) { //loop storing the old coloumn's values in the new column,will replace spaces that should be blocks
				pointer_column3[i] = data[placement+2][i];
			}
			///////ADDING NEW BLOCKS TO THE BOARD
			for (int i=piece_max_height;i<piece_max_height+2;i++) { //bounds will be from the original highest height to the new highest height
				pointer_column3[i] = piece; //now the character will be added to the column
			}
			for (int i=piece_max_height;i<piece_max_height+1;i++) { //bounds will be from the original highest height to the new highest height
				pointer_column[i] = piece; //now the character will be added to the column
				pointer_column2[i] = piece;
			}
			//DELETING DATA,REPLACING DATA,CHANGING HEIGHS ARRAY
			delete []data[placement]; 
			delete []data[placement+1];
			delete []data[placement+2]; 
			data[placement] = pointer_column;
			data[placement+1] = pointer_column2;
			data[placement+2] = pointer_column3;
			heights[placement] = piece_max_height+1;
			heights[placement+1] = piece_max_height+1;
			heights[placement+2] = piece_max_height+2;
		}
		if (rotation == 0){
			piece_max_height = local_max_height(placement,placement+1);
			char *pointer_column = new char[piece_max_height+3]; //establishing a new column with the adjusted height
			char *pointer_column2 = new char[piece_max_height+1];
			for (int i=0;i<piece_max_height+3;i++) { 
					pointer_column[i] = ' ';
			}
			for (int i=0;i<piece_max_height+1;i++) { 
					pointer_column2[i] = ' ';
			}
			//ADDING OLD PIECES TO THE BOARD
			for (int i=0;i<heights[placement];i++) { //loop storing the old coloumn's values in the new column,will replace spaces that should be blocks
				pointer_column[i] = data[placement][i];
			}
			for (int i=0;i<heights[placement+1];i++) { //loop storing the old coloumn's values in the new column,will replace spaces that should be blocks
				pointer_column2[i] = data[placement+1][i];
			}
			///////ADDING NEW BLOCKS TO THE BOARD
			for (int i=piece_max_height;i<piece_max_height+3;i++) { //bounds will be from the original highest height to the new highest height
				pointer_column[i] = piece; //now the character will be added to the column
			}
			for (int i=piece_max_height;i<piece_max_height+1;i++) { //bounds will be from the original highest height to the new highest height
				pointer_column2[i] = piece;
			}
			delete []data[placement]; 
			delete []data[placement+1];
			data[placement] = pointer_column;
			data[placement+1] = pointer_column2;
			heights[placement] = piece_max_height+3;
			heights[placement+1] = piece_max_height+1;
		}
	}
	if (piece == 'J') {
		if (rotation == 90) {
			piece_max_height = local_max_height(placement,placement+2);
			char *pointer_column = new char[piece_max_height+2]; //establishing a new column with the adjusted height
			char *pointer_column2 = new char[piece_max_height+1];
			char *pointer_column3 = new char[piece_max_height+1];
			for (int i=0;i<piece_max_height+2;i++) { 
				pointer_column[i] = ' '; //adding the ' ' character to every array as a default
			}
			for (int i=0;i<piece_max_height+1;i++) { 
				pointer_column2[i] = ' ';
				pointer_column3[i] = ' ';
			}
			for (int i=0;i<heights[placement];i++) { //loop storing the old coloumn's values in the new column,will replace spaces that should be blocks
				pointer_column[i] = data[placement][i];
			}
			for (int i=0;i<heights[placement+1];i++) { //loop storing the old coloumn's values in the new column,will replace spaces that should be blocks
				pointer_column2[i] = data[placement+1][i];
			}
			for (int i=0;i<heights[placement+2];i++) { //loop storing the old coloumn's values in the new column,will replace spaces that should be blocks
				pointer_column3[i] = data[placement+2][i];
			}
			///////ADDING NEW BLOCKS TO THE BOARD
			for (int i=piece_max_height;i<piece_max_height+2;i++) { //bounds will be from the original highest height to the new highest height
				pointer_column[i] = piece; //now the character will be added to the column
			}
			for (int i=piece_max_height;i<piece_max_height+1;i++) { //bounds will be from the original highest height to the new highest height
				pointer_column2[i] = piece; //now the character will be added to the column
				pointer_column3[i] = piece;
			}
			//DELETING DATA,REPLACING DATA,CHANGING HEIGHS ARRAY
			delete []data[placement]; 
			delete []data[placement+1];
			delete []data[placement+2]; 
			data[placement] = pointer_column;
			data[placement+1] = pointer_column2;
			data[placement+2] = pointer_column3;
			heights[placement] = piece_max_height+2;
			heights[placement+1] = piece_max_height+1;
			heights[placement+2] = piece_max_height+1;
		}	
		if (rotation == 180) {
			piece_max_height = local_max_height(placement,placement+1);
			if ((heights[placement] < heights[placement+1])) { //if column 1 is < column 2 in height
				char *pointer_column = new char[piece_max_height+1]; //establishing a new column with the adjusted height
				char *pointer_column2 = new char[piece_max_height+1];
				for (int i=0;i<piece_max_height+1;i++) { 
					pointer_column[i] = ' '; //addint the ' ' character to every array as a default
					pointer_column2[i] = ' ';
				}
				//ADDING OLD PIECES TO THE BOARD
				for (int i=0;i<heights[placement];i++) { //loop storing the old coloumn's values in the new column,will replace spaces that should be blocks
					pointer_column[i] = data[placement][i];
				}
				for (int i=0;i<heights[placement+1];i++) { //loop storing the old coloumn's values in the new column,will replace spaces that should be blocks
					pointer_column2[i] = data[placement+1][i];
				}
				///////ADDING NEW BLOCKS TO THE BOARD
				for (int i=piece_max_height-2;i<piece_max_height+1;i++) { //bounds will be from the original highest height to the new highest height
					pointer_column[i] = piece; //now the character will be added to the column
				}
				for (int i=piece_max_height;i<piece_max_height+1;i++) { //bounds will be from the original highest height to the new highest height
					pointer_column2[i] = piece;
				}
				delete []data[placement]; 
				delete []data[placement+1];
				data[placement] = pointer_column;
				data[placement+1] = pointer_column2;
				heights[placement] = piece_max_height+1;
				heights[placement+1] = piece_max_height+1;
			}
			else {
				char *pointer_column = new char[piece_max_height+3]; //establishing a new column with the adjusted height
				char *pointer_column2 = new char[piece_max_height+3];
				for (int i=0;i<piece_max_height+3;i++) { 
					pointer_column[i] = ' '; //adding the ' ' character to every array as a default
					pointer_column2[i] = ' ';
				}
				//ADDING OLD PIECES TO THE BOARD
				for (int i=0;i<heights[placement];i++) { //loop storing the old coloumn's values in the new column,will replace spaces that should be blocks
					pointer_column[i] = data[placement][i];
				}
				for (int i=0;i<heights[placement+1];i++) { //loop storing the old coloumn's values in the new column,will replace spaces that should be blocks
					pointer_column2[i] = data[placement+1][i];
				}
				///////ADDING NEW BLOCKS TO THE BOARD
				for (int i=piece_max_height;i<piece_max_height+3;i++) { //bounds will be from the original highest height to the new highest height
					pointer_column[i] = piece; //now the character will be added to the column
				}
				for (int i=piece_max_height+2;i<piece_max_height+3;i++) { //bounds will be from the original highest height to the new highest height
					pointer_column2[i] = piece;
				}
				delete []data[placement]; 
				delete []data[placement+1];
				data[placement] = pointer_column;
				data[placement+1] = pointer_column2;
				heights[placement] = piece_max_height+3;
				heights[placement+1] = piece_max_height+3;
			}	
		}	
		if (rotation == 270) {
			piece_max_height = local_max_height(placement,placement+2);
			if ((heights[placement] > heights[placement+2]) || (heights[placement+1] > heights[placement+2])) { //if the 2nd column is the highest
				char *pointer_column = new char[piece_max_height+1]; //establishing a new column with the adjusted height
				char *pointer_column2 = new char[piece_max_height+1];
				char *pointer_column3 = new char[piece_max_height+1];
				for (int i=0;i<piece_max_height+1;i++) { 
					pointer_column[i] = ' '; //adding the ' ' character to every array as a default
					pointer_column2[i] = ' ';
					pointer_column3[i] = ' ';
				}
				for (int i=0;i<heights[placement];i++) { //loop storing the old coloumn's values in the new column,will replace spaces that should be blocks
					pointer_column[i] = data[placement][i];
				}
				for (int i=0;i<heights[placement+1];i++) { //loop storing the old coloumn's values in the new column,will replace spaces that should be blocks
					pointer_column2[i] = data[placement+1][i];
				}
				for (int i=0;i<heights[placement+2];i++) { //loop storing the old coloumn's values in the new column,will replace spaces that should be blocks
					pointer_column3[i] = data[placement+2][i];
				}
				///////ADDING NEW BLOCKS TO THE BOARD
				for (int i=piece_max_height-1;i<piece_max_height+1;i++) { //bounds will be from the original highest height to the new highest height
					pointer_column3[i] = piece; //now the character will be added to the column
				}
				for (int i=piece_max_height+1;i<piece_max_height+1;i++) { //bounds will be from the original highest height to the new highest height
					pointer_column[i] = piece; //now the character will be added to the column
					pointer_column2[i] = piece;
				}
				//DELETING DATA,REPLACING DATA,CHANGING HEIGHS ARRAY
				delete []data[placement]; 
				delete []data[placement+1];
				delete []data[placement+2]; 
				data[placement] = pointer_column;
				data[placement+1] = pointer_column2;
				data[placement+2] = pointer_column3;
				heights[placement] = piece_max_height+1;
				heights[placement+1] = piece_max_height+1;
				heights[placement+2] = piece_max_height+1;
			}
			else {
				char *pointer_column = new char[piece_max_height+2]; //establishing a new column with the adjusted height
				char *pointer_column2 = new char[piece_max_height+2];
				char *pointer_column3 = new char[piece_max_height+2];
				for (int i=0;i<piece_max_height+2;i++) { 
					pointer_column[i] = ' '; //adding the ' ' character to every array as a default
					pointer_column2[i] = ' ';
					pointer_column3[i] = ' ';
				}
				for (int i=0;i<heights[placement];i++) { //loop storing the old coloumn's values in the new column,will replace spaces that should be blocks
					pointer_column[i] = data[placement][i];
				}
				for (int i=0;i<heights[placement+1];i++) { //loop storing the old coloumn's values in the new column,will replace spaces that should be blocks
					pointer_column2[i] = data[placement+1][i];
				}
				for (int i=0;i<heights[placement+2];i++) { //loop storing the old coloumn's values in the new column,will replace spaces that should be blocks
					pointer_column3[i] = data[placement+2][i];
				}
				///////ADDING NEW BLOCKS TO THE BOARD
				for (int i=piece_max_height;i<piece_max_height+2;i++) { //bounds will be from the original highest height to the new highest height
					pointer_column3[i] = piece; //now the character will be added to the column
				}
				for (int i=piece_max_height+1;i<piece_max_height+2;i++) { //bounds will be from the original highest height to the new highest height
					pointer_column[i] = piece; //now the character will be added to the column
					pointer_column2[i] = piece;
				}
				//DELETING DATA,REPLACING DATA,CHANGING HEIGHS ARRAY
				delete []data[placement]; 
				delete []data[placement+1];
				delete []data[placement+2]; 
				data[placement] = pointer_column;
				data[placement+1] = pointer_column2;
				data[placement+2] = pointer_column3;
				heights[placement] = piece_max_height+2;
				heights[placement+1] = piece_max_height+2;
				heights[placement+2] = piece_max_height+2;
			}
		}
		if (rotation == 0) {
			piece_max_height = local_max_height(placement,placement+1);
			char *pointer_column = new char[piece_max_height+1]; //establishing a new column with the adjusted height
			char *pointer_column2 = new char[piece_max_height+3];
			for (int i=0;i<piece_max_height+1;i++) { 
					pointer_column[i] = ' ';
			}
			for (int i=0;i<piece_max_height+3;i++) { 
					pointer_column2[i] = ' ';
			}
			//ADDING OLD PIECES TO THE BOARD
			for (int i=0;i<heights[placement];i++) { //loop storing the old coloumn's values in the new column,will replace spaces that should be blocks
				pointer_column[i] = data[placement][i];
			}
			for (int i=0;i<heights[placement+1];i++) { //loop storing the old coloumn's values in the new column,will replace spaces that should be blocks
				pointer_column2[i] = data[placement+1][i];
			}
			///////ADDING NEW BLOCKS TO THE BOARD
			for (int i=piece_max_height;i<piece_max_height+1;i++) { //bounds will be from the original highest height to the new highest height
				pointer_column[i] = piece; //now the character will be added to the column
			}
			for (int i=piece_max_height;i<piece_max_height+3;i++) { //bounds will be from the original highest height to the new highest height
				pointer_column2[i] = piece;
			}
			delete []data[placement]; 
			delete []data[placement+1];
			data[placement] = pointer_column;
			data[placement+1] = pointer_column2;
			heights[placement] = piece_max_height+1;
			heights[placement+1] = piece_max_height+3;
		}
	}
}
//special resize  for S and Z pieces
void Tetris::resize_S(char piece,int rotation,int placement){
	int piece_max_height;
	if (piece == 'S') {
		if ((rotation == 90) || (rotation == 270)) {
			piece_max_height = local_max_height(placement,placement+1); //finding the highest column
			if ((heights[placement] > heights[placement+1])) { //if the 2nd column is higher than the first
				char *pointer_column = new char[piece_max_height+2]; //establishing a new column with the adjusted height
				char *pointer_column2 = new char[piece_max_height+1];
				for (int i=0;i<piece_max_height+2;i++) { 
					pointer_column[i] = ' '; //adding the ' ' character to every array as a default
				}
				for (int i=0;i<piece_max_height+1;i++) { 
					pointer_column2[i] = ' ';
				}
				for (int i=0;i<heights[placement];i++) { //loop storing the old coloumn's values in the new column,will replace spaces that should be blocks
					pointer_column[i] = data[placement][i];
				}
				for (int i=0;i<heights[placement+1];i++) { //loop storing the old coloumn's values in the new column,will replace spaces that should be blocks
					pointer_column2[i] = data[placement+1][i];
				}
				///////ADDING NEW BLOCKS TO THE BOARD
				for (int i=piece_max_height;i<piece_max_height+2;i++) { //bounds will be from the original highest height to the new highest height
					pointer_column[i] = piece; //now the character will be added to the column
				}
				for (int i=piece_max_height-1;i<piece_max_height+1;i++) { //bounds will be from the original highest height to the new highest height
					pointer_column2[i] = piece; //now the character will be added to the column
				}
				//DELETING DATA,REPLACING DATA,CHANGING HEIGHS ARRAY
				delete []data[placement]; 
				delete []data[placement+1];
				data[placement] = pointer_column;
				data[placement+1] = pointer_column2;
				heights[placement] = piece_max_height+2;
				heights[placement+1] = piece_max_height+1;
			}
			else { //if the second column Is the highest
				char *pointer_column = new char[piece_max_height+3]; //establishing a new column with the adjusted height
				char *pointer_column2 = new char[piece_max_height+2];
				for (int i=0;i<piece_max_height+3;i++) { 
					pointer_column[i] = ' '; //addint the ' ' character to every array as a default
				}
				for (int i=0;i<piece_max_height+2;i++) { 
					pointer_column2[i] = ' ';
				}
				//ADDING OLD PIECES TO THE BOARD
				for (int i=0;i<heights[placement];i++) { //loop storing the old coloumn's values in the new column,will replace spaces that should be blocks
					pointer_column[i] = data[placement][i];
				}
				for (int i=0;i<heights[placement+1];i++) { //loop storing the old coloumn's values in the new column,will replace spaces that should be blocks
					pointer_column2[i] = data[placement+1][i];
				}
				///////ADDING NEW BLOCKS TO THE BOARD
				for (int i=piece_max_height+1;i<piece_max_height+3;i++) { //bounds will be from the original highest height to the new highest height
					pointer_column[i] = piece; //now the character will be added to the column
				}
				for (int i=piece_max_height;i<piece_max_height+2;i++) { //bounds will be from the original highest height to the new highest height
					pointer_column2[i] = piece; //now the character will be added to the column
				}
				//DELETING DATA,REPLACING DATA,CHANGING HEIGHS ARRAY
				delete []data[placement]; 
				delete []data[placement+1];
				data[placement] = pointer_column;
				data[placement+1] = pointer_column2;
				heights[placement] = piece_max_height+3;
				heights[placement+1] = piece_max_height+2;
			}
		}
		if ((rotation == 0) || (rotation == 180)) {
			piece_max_height = local_max_height(placement,placement+2);
			if ((heights[placement+2] > heights[placement]) && (heights[placement+2] > heights[placement+1])) { //if the 3rd column is the highest
				char *pointer_column = new char[piece_max_height]; //establishing a new column with the adjusted height
				char *pointer_column2 = new char[piece_max_height+1];
				char *pointer_column3 = new char[piece_max_height+1];
				for (int i=0;i<piece_max_height;i++) { 
					pointer_column[i] = ' '; //adding the ' ' character to every array as a default
				}
				for (int i=0;i<piece_max_height+1;i++) { 
					pointer_column2[i] = ' ';
					pointer_column3[i] = ' ';
				}
				for (int i=0;i<heights[placement];i++) { //loop storing the old coloumn's values in the new column,will replace spaces that should be blocks
					pointer_column[i] = data[placement][i];
				}
				for (int i=0;i<heights[placement+1];i++) { //loop storing the old coloumn's values in the new column,will replace spaces that should be blocks
					pointer_column2[i] = data[placement+1][i];
				}
				for (int i=0;i<heights[placement+2];i++) { //loop storing the old coloumn's values in the new column,will replace spaces that should be blocks
					pointer_column3[i] = data[placement+2][i];
				}
				///////ADDING NEW BLOCKS TO THE BOARD
				for (int i=piece_max_height-1;i<piece_max_height;i++) { //bounds will be from the original highest height to the new highest height
					pointer_column[i] = piece; //now the character will be added to the column
				}
				for (int i=piece_max_height-1;i<piece_max_height+2;i++) { //bounds will be from the original highest height to the new highest height
					pointer_column2[i] = piece; //now the character will be added to the column
				}
				for (int i=piece_max_height+1;i<piece_max_height+2;i++) { //bounds will be from the original highest height to the new highest height
					pointer_column3[i] = piece; //now the character will be added to the column
				}
				//DELETING DATA,REPLACING DATA,CHANGING HEIGHS ARRAY
				delete []data[placement]; 
				delete []data[placement+1];
				delete []data[placement+2]; 
				data[placement] = pointer_column;
				data[placement+1] = pointer_column2;
				data[placement+2] = pointer_column3;
				heights[placement] = piece_max_height;
				heights[placement+1] = piece_max_height+1;
				heights[placement+2] = piece_max_height+1;
			}
			else { //if the first column Is the highest
				char *pointer_column = new char[piece_max_height+1]; //establishing a new column with the adjusted height
				char *pointer_column2 = new char[piece_max_height+2];
				char *pointer_column3 = new char[piece_max_height+2];
				for (int i=0;i<piece_max_height+1;i++) { 
					pointer_column[i] = ' '; //addint the ' ' character to every array as a default
				}
				for (int i=0;i<piece_max_height+2;i++) { 
					pointer_column2[i] = ' ';
					pointer_column3[i] = ' ';
				}
				//ADDING OLD PIECES TO THE BOARD
				for (int i=0;i<heights[placement];i++) { //loop storing the old coloumn's values in the new column,will replace spaces that should be blocks
					pointer_column[i] = data[placement][i];
				}
				for (int i=0;i<heights[placement+1];i++) { //loop storing the old coloumn's values in the new column,will replace spaces that should be blocks
					pointer_column2[i] = data[placement+1][i];
				}
				for (int i=0;i<heights[placement+2];i++) { //loop storing the old coloumn's values in the new column,will replace spaces that should be blocks
					pointer_column3[i] = data[placement+2][i];
				}
				///////ADDING NEW BLOCKS TO THE BOARD
				for (int i=piece_max_height;i<piece_max_height+1;i++) { //bounds will be from the original highest height to the new highest height
					pointer_column[i] = piece; //now the character will be added to the column
				}
				for (int i=piece_max_height;i<piece_max_height+2;i++) { //bounds will be from the original highest height to the new highest height
					pointer_column2[i] = piece; //now the character will be added to the column
				}
				for (int i=piece_max_height+1;i<piece_max_height+2;i++) { //bounds will be from the original highest height to the new highest height
					pointer_column3[i] = piece;
				}
				//DELETING DATA,REPLACING DATA,CHANGING HEIGHS ARRAY
				delete []data[placement]; 
				delete []data[placement+1];
				delete []data[placement+2]; 
				data[placement] = pointer_column;
				data[placement+1] = pointer_column2;
				data[placement+2] = pointer_column3;
				heights[placement] = piece_max_height+1;
				heights[placement+1] = piece_max_height+2;
				heights[placement+2] = piece_max_height+2;
			}
		}
	}
	if (piece == 'Z') {
		if (rotation == 90 || rotation == 270) {
			if ((heights[placement] < heights[placement+1])) { //if the 2nd column is higher than the first
				piece_max_height = local_max_height(placement,placement+1);
				char *pointer_column = new char[piece_max_height+1]; //establishing a new column with the adjusted height
				char *pointer_column2 = new char[piece_max_height+2];
				for (int i=0;i<piece_max_height+1;i++) { 
					pointer_column[i] = ' '; //adding the ' ' character to every array as a default
				}
				for (int i=0;i<piece_max_height+2;i++) { 
					pointer_column2[i] = ' ';
				}
				for (int i=0;i<heights[placement];i++) { //loop storing the old coloumn's values in the new column,will replace spaces that should be blocks
					pointer_column[i] = data[placement][i];
				}
				for (int i=0;i<heights[placement+1];i++) { //loop storing the old coloumn's values in the new column,will replace spaces that should be blocks
					pointer_column2[i] = data[placement+1][i];
				}
				///////ADDING NEW BLOCKS TO THE BOARD
				for (int i=piece_max_height-1;i<piece_max_height+1;i++) { //bounds will be from the original highest height to the new highest height
					pointer_column[i] = piece; //now the character will be added to the column
				}
				for (int i=piece_max_height;i<piece_max_height+2;i++) { //bounds will be from the original highest height to the new highest height
					pointer_column2[i] = piece; //now the character will be added to the column
				}
				//DELETING DATA,REPLACING DATA,CHANGING HEIGHS ARRAY
				delete []data[placement]; 
				delete []data[placement+1];
				data[placement] = pointer_column;
				data[placement+1] = pointer_column2;
				heights[placement] = piece_max_height+1;
				heights[placement+1] = piece_max_height+2;
			}
			else { //if the second column Is the highest
				piece_max_height = local_max_height(placement,placement+1);
				char *pointer_column = new char[piece_max_height+2]; //establishing a new column with the adjusted height
				char *pointer_column2 = new char[piece_max_height+3];
				for (int i=0;i<piece_max_height+2;i++) { 
					pointer_column[i] = ' '; //addint the ' ' character to every array as a default
				}
				for (int i=0;i<piece_max_height+3;i++) { 
					pointer_column2[i] = ' ';
				}
				//ADDING OLD PIECES TO THE BOARD
				for (int i=0;i<heights[placement];i++) { //loop storing the old coloumn's values in the new column,will replace spaces that should be blocks
					pointer_column[i] = data[placement][i];
				}
				for (int i=0;i<heights[placement+1];i++) { //loop storing the old coloumn's values in the new column,will replace spaces that should be blocks
					pointer_column2[i] = data[placement+1][i];
				}
				///////ADDING NEW BLOCKS TO THE BOARD
				for (int i=piece_max_height;i<piece_max_height+2;i++) { //bounds will be from the original highest height to the new highest height
					pointer_column[i] = piece; //now the character will be added to the column
				}
				for (int i=piece_max_height+1;i<piece_max_height+3;i++) { //bounds will be from the original highest height to the new highest height
					pointer_column2[i] = piece; //now the character will be added to the column
				}
				//DELETING DATA,REPLACING DATA,CHANGING HEIGHS ARRAY
				delete []data[placement]; 
				delete []data[placement+1];
				data[placement] = pointer_column;
				data[placement+1] = pointer_column2;
				heights[placement] = piece_max_height+2;
				heights[placement+1] = piece_max_height+3;
			}
		}
		if (rotation == 0 || rotation == 180) {
			piece_max_height = local_max_height(placement,placement+2); //finding the highest column
			if ((heights[placement] > heights[placement+1]) && (heights[placement] > heights[placement+3])) { //if the 1st or thirs column is the highest
				char *pointer_column = new char[piece_max_height+1]; //establishing a new column with the adjusted height
				char *pointer_column2 = new char[piece_max_height+1];
				char *pointer_column3 = new char[piece_max_height];
				for (int i=0;i<piece_max_height;i++) { 
					pointer_column3[i] = ' '; //adding the ' ' character to every array as a default
				}
				for (int i=0;i<piece_max_height+1;i++) { 
					pointer_column[i] = ' '; //adding the ' ' character to every array as a default
					pointer_column2[i] = ' ';
				}
				for (int i=0;i<heights[placement];i++) { //loop storing the old coloumn's values in the new column,will replace spaces that should be blocks
					pointer_column[i] = data[placement][i];
				}
				for (int i=0;i<heights[placement+1];i++) { //loop storing the old coloumn's values in the new column,will replace spaces that should be blocks
					pointer_column2[i] = data[placement+1][i];
				}
				for (int i=0;i<heights[placement+2];i++) { //loop storing the old coloumn's values in the new column,will replace spaces that should be blocks
					pointer_column3[i] = data[placement+2][i];
				}
				///////ADDING NEW BLOCKS TO THE BOARD
				for (int i=piece_max_height-1;i<piece_max_height+1;i++) { //bounds will be from the original highest height to the new highest height
					pointer_column[i] = piece; //now the character will be added to the column
				}
				for (int i=piece_max_height;i<piece_max_height+1;i++) { //bounds will be from the original highest height to the new highest height
					pointer_column2[i] = piece; //now the character will be added to the column
					pointer_column3[i] = piece;
				}
				//DELETING DATA,REPLACING DATA,CHANGING HEIGHS ARRAY
				delete []data[placement]; 
				delete []data[placement+1];
				delete []data[placement+2]; 
				data[placement] = pointer_column;
				data[placement+1] = pointer_column2;
				data[placement+2] = pointer_column3;
				heights[placement] = piece_max_height+1;
				heights[placement+1] = piece_max_height+1;
				heights[placement+2] = piece_max_height;
			}
			else { //if the first column Is the highest
				char *pointer_column = new char[piece_max_height+2]; //establishing a new column with the adjusted height
				char *pointer_column2 = new char[piece_max_height+2];
				char *pointer_column3 = new char[piece_max_height+1];
				for (int i=0;i<piece_max_height+2;i++) { 
					pointer_column[i] = ' ';
					pointer_column2[i] = ' ';
				}
				for (int i=0;i<piece_max_height+1;i++) { 
					pointer_column3[i] = ' '; //addint the ' ' character to every array as a default
				}
				//ADDING OLD PIECES TO THE BOARD
				for (int i=0;i<heights[placement];i++) { //loop storing the old coloumn's values in the new column,will replace spaces that should be blocks
					pointer_column[i] = data[placement][i];
				}
				for (int i=0;i<heights[placement+1];i++) { //loop storing the old coloumn's values in the new column,will replace spaces that should be blocks
					pointer_column2[i] = data[placement+1][i];
				}
				for (int i=0;i<heights[placement+2];i++) { //loop storing the old coloumn's values in the new column,will replace spaces that should be blocks
					pointer_column3[i] = data[placement+2][i];
				}
				///////ADDING NEW BLOCKS TO THE BOARD
				for (int i=piece_max_height+1;i<piece_max_height+2;i++) { //bounds will be from the original highest height to the new highest height
					pointer_column[i] = piece; //now the character will be added to the column
				}
				for (int i=piece_max_height;i<piece_max_height+2;i++) { //bounds will be from the original highest height to the new highest height
					pointer_column2[i] = piece; //now the character will be added to the column
				}
				for (int i=piece_max_height;i<piece_max_height+1;i++) { //bounds will be from the original highest height to the new highest height
					pointer_column3[i] = piece;
				}
				//DELETING DATA,REPLACING DATA,CHANGING HEIGHS ARRAY
				delete []data[placement]; 
				delete []data[placement+1];
				delete []data[placement+2]; 
				data[placement] = pointer_column;
				data[placement+1] = pointer_column2;
				data[placement+2] = pointer_column3;
				heights[placement] = piece_max_height+2;
				heights[placement+1] = piece_max_height+2;
				heights[placement+2] = piece_max_height+1;
			}
		}
	}
}
//special resize for T piece
void Tetris::resize_T(char piece,int rotation,int placement){
	int piece_max_height;
	if (rotation == 90){
		piece_max_height = local_max_height(placement,placement+1); //finding the highest column
		if ((heights[placement] > heights[placement+1]) && (piece_max_height != 0)) { //if the 2nd column is higher than the first
			char *pointer_column = new char[piece_max_height+1]; //establishing a new column with the adjusted height
			char *pointer_column2 = new char[piece_max_height+2];
			for (int i=0;i<piece_max_height+1;i++) { 
				pointer_column[i] = ' '; //adding the ' ' character to every array as a default
			}
			for (int i=0;i<piece_max_height+2;i++) { 
				pointer_column2[i] = ' ';
			}
			for (int i=0;i<heights[placement];i++) { //loop storing the old coloumn's values in the new column,will replace spaces that should be blocks
				pointer_column[i] = data[placement][i];
			}
			for (int i=0;i<heights[placement+1];i++) { //loop storing the old coloumn's values in the new column,will replace spaces that should be blocks
				pointer_column2[i] = data[placement+1][i];
			}
			///////ADDING NEW BLOCKS TO THE BOARD
			for (int i=piece_max_height;i<piece_max_height+1;i++) { //bounds will be from the original highest height to the new highest height
				pointer_column[i] = piece; //now the character will be added to the column
			}
			for (int i=piece_max_height-1;i<piece_max_height+2;i++) { //bounds will be from the original highest height to the new highest height
				pointer_column2[i] = piece; //now the character will be added to the column
			}
			//DELETING DATA,REPLACING DATA,CHANGING HEIGHS ARRAY
			delete []data[placement]; 
			delete []data[placement+1];
			data[placement] = pointer_column;
			data[placement+1] = pointer_column2;
			heights[placement] = piece_max_height+1;
			heights[placement+1] = piece_max_height+2;
		}
		else { //if the second column Is the highest
			char *pointer_column = new char[piece_max_height+2]; //establishing a new column with the adjusted height
			char *pointer_column2 = new char[piece_max_height+3];
			for (int i=0;i<piece_max_height+2;i++) { 
				pointer_column[i] = ' '; //addint the ' ' character to every array as a default
			}
			for (int i=0;i<piece_max_height+3;i++) { 
				pointer_column2[i] = ' ';
			}
			//ADDING OLD PIECES TO THE BOARD
			for (int i=0;i<heights[placement];i++) { //loop storing the old coloumn's values in the new column,will replace spaces that should be blocks
				pointer_column[i] = data[placement][i];
			}
			for (int i=0;i<heights[placement+1];i++) { //loop storing the old coloumn's values in the new column,will replace spaces that should be blocks
				pointer_column2[i] = data[placement+1][i];
			}
			///////ADDING NEW BLOCKS TO THE BOARD
			for (int i=piece_max_height+1;i<piece_max_height+2;i++) { //bounds will be from the original highest height to the new highest height
				pointer_column[i] = piece; //now the character will be added to the column
			}
			for (int i=piece_max_height;i<piece_max_height+3;i++) { //bounds will be from the original highest height to the new highest height
				pointer_column2[i] = piece; //now the character will be added to the column
			}
			//DELETING DATA,REPLACING DATA,CHANGING HEIGHS ARRAY
			delete []data[placement]; 
			delete []data[placement+1];
			data[placement] = pointer_column;
			data[placement+1] = pointer_column2;
			heights[placement] = piece_max_height+2;
			heights[placement+1] = piece_max_height+3;
		}
	}
	if (rotation == 180) {
		piece_max_height = local_max_height(placement,placement+2);
		char *pointer_column = new char[piece_max_height+1]; //establishing a new column with the adjusted height
		char *pointer_column2 = new char[piece_max_height+2];
		char *pointer_column3 = new char[piece_max_height+1];
		for (int i=0;i<piece_max_height+2;i++) {
			pointer_column2[i] = ' '; //addint the ' ' character to every array as a default 
		}
		for (int i=0;i<piece_max_height+1;i++) {
			pointer_column[i] = ' '; //addint the ' ' character to every array as a default 
			pointer_column3[i] = ' ';
		}
		//ADDING OLD PIECES TO THE BOARD
		for (int i=0;i<heights[placement];i++) { //loop storing the old coloumn's values in the new column,will replace spaces that should be blocks
			pointer_column[i] = data[placement][i];
		}
		for (int i=0;i<heights[placement+1];i++) { //loop storing the old coloumn's values in the new column,will replace spaces that should be blocks
			pointer_column2[i] = data[placement+1][i];
		}
		for (int i=0;i<heights[placement+2];i++) { //loop storing the old coloumn's values in the new column,will replace spaces that should be blocks
			pointer_column3[i] = data[placement+2][i];
		}
		///////ADDING NEW BLOCKS TO THE BOARD
		for (int i=piece_max_height;i<piece_max_height+2;i++) { //bounds will be from the original highest height to the new highest height
			pointer_column2[i] = piece; //now the character will be added to the column
		}
		for (int i=piece_max_height;i<piece_max_height+1;i++) { //bounds will be from the original highest height to the new highest height
			pointer_column[i] = piece; //now the character will be added to the column
			pointer_column3[i] = piece;
		}
		//DELETING DATA,REPLACING DATA,CHANGING HEIGHS ARRAY
		delete []data[placement]; 
		delete []data[placement+1];
		delete []data[placement+2]; 
		data[placement] = pointer_column;
		data[placement+1] = pointer_column2;
		data[placement+2] = pointer_column3;
		heights[placement] = piece_max_height+1;
		heights[placement+1] = piece_max_height+2;
		heights[placement+2] = piece_max_height+1;
	}
	if (rotation == 270) {
		piece_max_height = local_max_height(placement,placement+1); //finding the highest column
		if ((heights[placement+2] > heights[placement]) && (piece_max_height != 0)) { //if the 2nd column is higher than the first
			char *pointer_column = new char[piece_max_height+2]; //establishing a new column with the adjusted height
			char *pointer_column2 = new char[piece_max_height+1];
			for (int i=0;i<piece_max_height+2;i++) { 
				pointer_column[i] = ' '; //adding the ' ' character to every array as a default
			}
			for (int i=0;i<piece_max_height+1;i++) { 
				pointer_column2[i] = ' ';
			}
			for (int i=0;i<heights[placement];i++) { //loop storing the old coloumn's values in the new column,will replace spaces that should be blocks
				pointer_column[i] = data[placement][i];
			}
			for (int i=0;i<heights[placement+1];i++) { //loop storing the old coloumn's values in the new column,will replace spaces that should be blocks
				pointer_column2[i] = data[placement+1][i];
			}
			///////ADDING NEW BLOCKS TO THE BOARD
			for (int i=piece_max_height-1;i<piece_max_height+2;i++) { //bounds will be from the original highest height to the new highest height
				pointer_column[i] = piece; //now the character will be added to the column
			}
			for (int i=piece_max_height;i<piece_max_height+1;i++) { //bounds will be from the original highest height to the new highest height
				pointer_column2[i] = piece; //now the character will be added to the column
			}
			//DELETING DATA,REPLACING DATA,CHANGING HEIGHS ARRAY
			delete []data[placement]; 
			delete []data[placement+1];
			data[placement] = pointer_column;
			data[placement+1] = pointer_column2;
			heights[placement] = piece_max_height+2;
			heights[placement+1] = piece_max_height+1;
		}
		else { //if the second column Is the highest
			char *pointer_column = new char[piece_max_height+3]; //establishing a new column with the adjusted height
			char *pointer_column2 = new char[piece_max_height+2];
			for (int i=0;i<piece_max_height+3;i++) { 
				pointer_column[i] = ' '; //addint the ' ' character to every array as a default
			}
			for (int i=0;i<piece_max_height+2;i++) { 
				pointer_column2[i] = ' ';
			}
			//ADDING OLD PIECES TO THE BOARD
			for (int i=0;i<heights[placement];i++) { //loop storing the old coloumn's values in the new column,will replace spaces that should be blocks
				pointer_column[i] = data[placement][i];
			}
			for (int i=0;i<heights[placement+1];i++) { //loop storing the old coloumn's values in the new column,will replace spaces that should be blocks
				pointer_column2[i] = data[placement+1][i];
			}
			///////ADDING NEW BLOCKS TO THE BOARD
			for (int i=piece_max_height;i<piece_max_height+3;i++) { //bounds will be from the original highest height to the new highest height
				pointer_column[i] = piece; //now the character will be added to the column
			}
			for (int i=piece_max_height+1;i<piece_max_height+2;i++) { //bounds will be from the original highest height to the new highest height
				pointer_column2[i] = piece; //now the character will be added to the column
			}
			//DELETING DATA,REPLACING DATA,CHANGING HEIGHS ARRAY
			delete []data[placement]; 
			delete []data[placement+1];
			data[placement] = pointer_column;
			data[placement+1] = pointer_column2;
			heights[placement] = piece_max_height+3;
			heights[placement+1] = piece_max_height+2;
		}
	}
	if (rotation == 0){
		piece_max_height = local_max_height(placement,placement+2);
		if ((heights[placement] > heights[placement+1]) || (heights[placement+2] > heights[placement+1])) { //if the 2nd column isnt the highest
			char *pointer_column = new char[piece_max_height+1]; //establishing a new column with the adjusted height
			char *pointer_column2 = new char[piece_max_height+1];
			char *pointer_column3 = new char[piece_max_height+1];
			for (int i=0;i<piece_max_height+1;i++) { 
				pointer_column[i] = ' '; //adding the ' ' character to every array as a default
				pointer_column2[i] = ' ';
				pointer_column3[i] = ' ';
			}
			for (int i=0;i<heights[placement];i++) { //loop storing the old coloumn's values in the new column,will replace spaces that should be blocks
				pointer_column[i] = data[placement][i];
			}
			for (int i=0;i<heights[placement+1];i++) { //loop storing the old coloumn's values in the new column,will replace spaces that should be blocks
				pointer_column2[i] = data[placement+1][i];
			}
			for (int i=0;i<heights[placement+2];i++) { //loop storing the old coloumn's values in the new column,will replace spaces that should be blocks
				pointer_column3[i] = data[placement+2][i];
			}
			///////ADDING NEW BLOCKS TO THE BOARD
			for (int i=piece_max_height-1;i<piece_max_height+1;i++) { //bounds will be from the original highest height to the new highest height
				pointer_column2[i] = piece; //now the character will be added to the column
			}
			for (int i=piece_max_height;i<piece_max_height+1;i++) { //bounds will be from the original highest height to the new highest height
				pointer_column[i] = piece; //now the character will be added to the column
				pointer_column3[i] = piece;
			}
			//DELETING DATA,REPLACING DATA,CHANGING HEIGHS ARRAY
			delete []data[placement]; 
			delete []data[placement+1];
			delete []data[placement+2]; 
			data[placement] = pointer_column;
			data[placement+1] = pointer_column2;
			data[placement+2] = pointer_column3;
			heights[placement] = piece_max_height+1;
			heights[placement+1] = piece_max_height+1;
			heights[placement+2] = piece_max_height+1;
		}
		else { //if the first column Is the highest
			char *pointer_column = new char[piece_max_height+2]; //establishing a new column with the adjusted height
			char *pointer_column2 = new char[piece_max_height+2];
			char *pointer_column3 = new char[piece_max_height+2];
			for (int i=0;i<piece_max_height+2;i++) {
				pointer_column[i] = ' '; //addint the ' ' character to every array as a default 
				pointer_column2[i] = ' ';
				pointer_column3[i] = ' ';
			}
			//ADDING OLD PIECES TO THE BOARD
			for (int i=0;i<heights[placement];i++) { //loop storing the old coloumn's values in the new column,will replace spaces that should be blocks
				pointer_column[i] = data[placement][i];
			}
			for (int i=0;i<heights[placement+1];i++) { //loop storing the old coloumn's values in the new column,will replace spaces that should be blocks
				pointer_column2[i] = data[placement+1][i];
			}
			for (int i=0;i<heights[placement+2];i++) { //loop storing the old coloumn's values in the new column,will replace spaces that should be blocks
				pointer_column3[i] = data[placement+2][i];
			}
			///////ADDING NEW BLOCKS TO THE BOARD
			for (int i=piece_max_height;i<piece_max_height+2;i++) { //bounds will be from the original highest height to the new highest height
				pointer_column2[i] = piece; //now the character will be added to the column
			}
			for (int i=piece_max_height+1;i<piece_max_height+2;i++) { //bounds will be from the original highest height to the new highest height
				pointer_column[i] = piece; //now the character will be added to the column
				pointer_column3[i] = piece;
			}
			//DELETING DATA,REPLACING DATA,CHANGING HEIGHS ARRAY
			delete []data[placement]; 
			delete []data[placement+1];
			delete []data[placement+2]; 
			data[placement] = pointer_column;
			data[placement+1] = pointer_column2;
			data[placement+2] = pointer_column3;
			heights[placement] = piece_max_height+2;
			heights[placement+1] = piece_max_height+2;
			heights[placement+2] = piece_max_height+2;
		}
	}
}
void Tetris::add_left_column(){
	width++; //increasing the width by 1

	char** temp_data = new char* [width]; //creating a new data array
	char* new_column = new char[0]; //creating a column for the new data array with a height of zero

	std::cout << "Checkpoint 1" << std::endl;

	for (int n=0;n<width-1;n++){
		temp_data[n+1] = data[n]; //storing all of the old data information into the new array
	}
	temp_data[0] = new_column;//adding a new column to the start of the temporary data array

	delete []data; //deleting the old data array
	data = temp_data; //setting data equal to the new data array


	std::cout << "Checkpoint 2" << std::endl;

	int* temp_heights = new int[width];
	for (int a=0;a<width-1;a++) {
		temp_heights[a+1] = heights[a]; //chaging the heights array to include the extra column
	}
	temp_heights[0] = 0;
	std::cout << "Checkpoint 3" << std::endl;
	delete []heights; //deleting the old height
	heights = temp_heights; //setting heights equal to the new heights array
}
void Tetris::add_right_column(){
	cout << width << endl;
	char** temp_data = new char* [width+1]; //creating a new data array
	for (int n=0;n<width;n++){ //copying the columns from the old data array into the new one
		temp_data[n] = data[n];
	}
	char* new_column = new char[0]; //new column array
	temp_data[width] = new_column; //putting the new column array in the place holder for temp_data
	delete []data; //deleting the old data array
	data = temp_data; //setting data equal to the new data array
	width++; //increasing the width by 1
	int* temp_heights = new int[width]; //temporary heights array
	for (int n=0;n<width-1;n++) { //copying the data from the old heights array to the new one
		temp_heights[n] = heights[n];
	}
	temp_heights[width-1] = 0; //setting the new column to be 0 in height
	delete []heights;
	heights = temp_heights; //setting the old heights array equal to the new one
}
void Tetris::remove_left_column(){
	delete []data[0]; //deleting the old column
	char** temp_data = new char* [width-1]; //creating a new data array
	for (int a=1;a<width-1;a++){ //copying everything from the old array into the new array except the left column
		temp_data[a-1] = data[a];
	}
	delete []data; //deleting the old data array
	data = temp_data; //setting data equal to the new data array
	width--; //decreasing the width by 1
	int* temp_heights = new int[width];
	for (int b=1;b<width;b++) { //copying everything from the old heighsts array into the new array except the left column height
		temp_heights[b-1] = heights[b];
	}
	delete []heights; //deleting the old heights array
	heights = temp_heights; //setting it equal to the new heights array
}
void Tetris::remove_right_column(){
	width--;
	delete []data[width]; //deleting the old column
	char** temp_data = new char* [width]; //creating a new data array
	for (int n=0;n<width;n++){ //copying everything from the old data array into the new data array except the right column
		temp_data[n] = data[n];
	}
	delete []data; //deleting the old data array
	data = temp_data; //setting data equal to the new data array
	int* temp_heights = new int[width]; //new temporary heights array
	for (int n=0;n<width+1;n++) {
		temp_heights[n] = heights[n]; //copying everything from the old heighsts array into the new array except the left column height
	}
	delete []heights; //deleting the old heights array
	heights = temp_heights; //replacing the old heights array
}
//adding pieces to the board based on the character,rotation of the piece, and the placemnt of the leftmost piece
void Tetris::add_piece(char piece,int rotation,int placement) {
	int piece_width; //represents how long the piece will be
	if (piece == 'O') { // 
		piece_width = 2;
		if (bound_check(placement,piece_width)) { //if the piece can land within the bounds of the tetris table
			max_height = max(heights[placement],heights[placement+1]); //checking to see what the highest column is between those we are looking at
			resize(placement,max_height,2,piece); //will go into the data and height arrays and update them while deleting the old ones
			resize(placement+1,max_height,2,piece);
		}
	}
	if (piece == 'I'){
		if (rotation == 90 || rotation == 270) {
			max_height = local_max_height(placement,placement+3);
			piece_width = 4; //will be used in bound check to see if a piece is too long
			if (bound_check(placement,piece_width)) { //checking to see if the piece is in bounds
				resize(placement,max_height,1,piece); //resizing columns 1-4 and updating them to the new heights and pieces
				resize(placement+1,max_height,1,piece);
				resize(placement+2,max_height,1,piece);
				resize(placement+3,max_height,1,piece);
			}
		}
		else {
			max_height = heights[placement];
			piece_width = 1; //it will be very rare that a shape with width 1 will be out of bounds,the check is unnecessary
			resize(placement,max_height,4,piece);
		}
	}
	if (piece == 'L') {
		if (rotation == 90 || rotation == 270) {
			piece_width = 3;
		}
		else if (rotation == 0 || rotation == 270) {
			piece_width = 2;
		}
		if (bound_check(placement,piece_width)) { //checking the width to see if its in bounds of the tetris board
			resize_L(piece,rotation,placement);
		}
	}
	if (piece == 'J') {
		if (rotation == 90 || rotation == 270) {
			piece_width = 3;
		}
		else if (rotation == 0 || rotation == 270) {
			piece_width = 2;
		}
		if (bound_check(placement,piece_width)) {
			resize_L(piece,rotation,placement);
		}
	}
	if (piece == 'S') {
		if (rotation == 90 || rotation == 270) {
			piece_width = 3;
		}
		else if (rotation == 0 || rotation == 270) {
			piece_width = 2;
		}
		if (bound_check(placement,piece_width)) {
			resize_S(piece,rotation,placement);
		}
	}
	if (piece == 'Z') {
		if (rotation == 90 || rotation == 270) {
			piece_width = 3;
		}
		else if (rotation == 0 || rotation == 270) {
			piece_width = 2;
		}
		if (bound_check(placement,piece_width)) { //if the piece can land within the bounds of the tetris table
			resize_S(piece,rotation,placement); //will go into the data and height arrays and update them while deleting the old ones
		}
	}
	if (piece == 'T') {
		if (rotation == 180 || rotation == 0) {
			piece_width = 3;
		}
		else if (rotation == 90 || rotation == 270) {
			piece_width = 2;
		}
		if (bound_check(placement,piece_width)) { //if the piece can land within the bounds of the tetris table
			resize_T(piece,rotation,placement);
		}
	}
}
//destroying the entire tetris board
void Tetris::destroy(){
	delete []heights; //destroying the heights array
	for (int n=0;n<width;n++) { //destroying the inner data arrays
		delete []data[n];
	}
	delete []data; //destroying the data array as a whole
}
//checking to see if a row is ful
bool Tetris::full_row_check(int row_position) {
	int counter = 0; //will be the counter for the number of pieces that are not spaces in the row
	for (int b=0;b<width;b++) { //looging through all the colums
		if (data[b][row_position] != ' ') { //checkin to see if the specific position of the column is a piece
			counter++; //if it is a piece the counter will increase by 1
			if (counter == width) { //if the counter is equal to the width,it will signify a full row
				return true;
			}
		}
	}
	return false; //if all the pieces in the row arent blocks, or the counter doenst equal the width,return false
}
//removing a row if it is full
void Tetris::remove_row(int a){
	//a represents the row i'm removing
	for(int i=0;i<width;i++) { //looping through columns
		for (int j=a;j<heights[i]-1;j++) { //looping through rows
			data[i][j] = data[i][j+1]; //setting each data row to the one above it
		}
	}
	for (int i=0;i<width;i++) {//looping through colums
		char* new_row = new char[heights[i]-1]; //creating new row array with the heights of the column
		for (int j=0;j<heights[i]-1;j++) { //copying the old data new data column
			new_row[j] = data[i][j];
		}
		delete [] data[i]; //deleting the old data
		data[i] = new_row; //replacing the old data
	}
	for (int i=0;i<width;i++) {
		heights[i]--; //decreading heights by 1 because a column was removed
	}
	for (int i=0;i<width;i++) {
		if (data[i][heights[i]-1] == ' ' && (heights[i] > 0)) { //if the character in the top of the column is a space
			int new_column_height = heights[i];
			int l = new_column_height - 1; //l is representing the pos. one below max height of col
			while ((l>=0) && (data[i][l] == ' ')) { //as long as the row is not less than the bottom, and the character is a space
				new_column_height--;
				l--;
			}
			char* new_column = new char [new_column_height]; //creating a new height array
			int m =0; //m represents the position in the new column
			while (m<new_column_height) { //setting the old column data to the new column data
				new_column[m] = data[i][m];
			}
			delete []data[i]; //deleting old column data
			data[i] = new_column; //replacing the old column with the new one
			heights[i] = new_column_height; //setting the new column height in the height array
		}
	}
}
//removing full rows
int Tetris::remove_full_rows() {
	//count will represent the number of rows removed
	int count = 0; //counter that will return the numbe of rows removed
	for (int n=0;n<get_min_height();n++) {//n represents row position
		if (full_row_check(n)) {//if the row s full remove it
			remove_row(n);
			count++; //when the row is removed,the count is increased by one
		}
	}
	return count; 
}
	
	
