#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <stdio.h>
#include <ctype.h>
using namespace std;

//FUNCTIONS FOR EACH OPERATION
//REPLACE OPERATION
vector <string> replace(const vector <string> & original_file,char* character,char* new_character) { //replace operation,changing one character to another
	vector <string> new_file; //will be the output for the function, a new string vector consisting of the edited text
	for (int i=0;i < (original_file.size());i++) { //looping through all the lines
		string new_line = ""; //new line created after the original line has been edited,will be added to the new string vector
		for (int j=0;j< (original_file[i].size());j++){  //looping through all the column
			if ((*character== original_file[i][j] ) && (original_file[i][j] != '.')) { //if the characters are the same and not '.',change it 
				new_line.push_back(*new_character); //adding the new character tp the line to replace the old character
			}
			else{
				new_line.push_back(original_file[i][j]); //adding the '.' character to the line to create the background
			}
		}
		//cout << new_line << endl;
		new_file.push_back(new_line); //adding the new line to the new string vector
	}return new_file; //returning the new version of the text document
}
// //EROSION OPERATION
vector <string> erosion(const vector <string> & original_file,char* character,char* replacer) {  //Parameters are the vector form of the text file and the arguments from the user
	//character is argv[4]  //establishing which character to dilate
	//replacer is argv[5] //character that is going to be replaced in erosion operation,really it is just a background character
	vector <string> new_file;  //vector for storing the edited text after dilation
	for (int i=0;i<original_file.size();i++) { //looping through every line in the file
		int length = original_file[i].size(); //length of each line,will be used when checking if j has reached the end of the line
		string new_line = "";  //new line created after the original line has been edited,will be added to the new string vector
		for (int j=0; j< length;j++) { //looping through every string in the file to get the character
			bool top,bottom,dot,first,last;
			bool left,right,up,down; //these booleans will be used to form the structure and check if the current pixel is connected to the the shape in the file
			//SYMBOL/LINE CHECK/POSTION CHECK BOOLEANS
			dot = (original_file[i][j] == *replacer); //checking to see if the current characer is a dot
			top = (i==0); //will return true if we are at the first line in the text file
			bottom = (i==(original_file.size()-1));  //will return true if we are at the last line in the text file
			first = (j==0); //checking to see if the character is the first in the row
			last = (j==(length-1)); //checking to see if the character is the last in the row
			//ADJACENT PIXEL BOOLEANS

			left = right = up = down = true; //initially we wil assume
			if (!first) //if not the first position in the line,consider this to be the left pixe
				left = (original_file[i][(j-1)]==*character); //each is checking to see if the pixel is the symbol that is to be replaced
			if (!last) //if not the last position in the line,consider this to be the right pixel
				right = (original_file[i][(j+1)]==*character);
			if (!top) //if not the first line in the file, consider this to be up
				up = (original_file[i-1][j]==*character);
			if (!bottom) //if not the last line in the file,consider this to be down
				down = (original_file[i+1][j]==*character);
			if ((top) && (first) && (!dot)) { //top left pixel, 
				if (!right || !down) { //the nested if for each scenario is saying,if one of the adjacent pixels is the character that is to be replaced,not both,change the current pixel to a background characer
					new_line.push_back(*replacer);
				}
			}
			else if ((top) && (last) && (!dot)) {  //top right pixel
				if (!left || !down)  {
					new_line.push_back(*replacer);
				}
			}
			else if ((bottom) && (first) && (!dot)) { //bottom left
				if (!right || !up) {
					new_line.push_back(*replacer);
				}
			}
			else if ((bottom) && (last) && (!dot)) {  //bottom right
				if (!left || !up) {
					new_line.push_back(*replacer);
				}
			}
			else if ((top) && (!dot)) {  //anything in top row
				if (!left || !right || !down) {
					new_line.push_back(*replacer);
				}
			}
			else if ((bottom) && (!dot)) {  //anything in bottom row
				if (!left || !right || !up ){
					new_line.push_back(*replacer);
				}
			}
			else if ((first) && (!dot)) { //first in line
				if (!right || !up || !down) {
					new_line.push_back(*replacer);
				}
			}
			else if ((last) && (!dot)) {  //last in line
				if (!left|| !up|| !down) {
					new_line.push_back(*replacer);
				}
			}
			else if (!dot) { //any other position in the file
				if (!left || !right || !up || !down) {
					new_line.push_back(*replacer);
				} else
					new_line.push_back(*character);
			} else
				new_line.push_back(*replacer); //if none of the conditions are met,just add a background character
		}
		new_file.push_back(new_line);
	}
	return new_file;
}

//DILATION ORPERation
vector <string> dilation(const vector <string> & original_file,char* replacer) {  //Parameters are the vector form of the text file and the arguments from the user
	//character is argv[4]  //establishing which character to dilate
	//replacer is argv[5] //character that is going to be replaced in erosion operation
	vector <string> new_file;  //vector for storing the edited text after dilation
	for (int i=0;i<original_file.size();i++) { //looping through every line in the file
		int length = original_file[i].size(); //length of each line,will be used when checking if j has reached the end of the line
		string new_line = "";  //new line created after the original line has been edited,will be added to the new string vector
		for (int j=0; j< length;j++) { //looping through every string in the file to get the character
			bool top,bottom,dot,first,last;
			bool left,right,up,down; //these booleans will be used to form the structure and check if the current pixel is connected to the the shape in the file
			//SYMBOL/LINE CHECK/POSTION CHECK BOOLEANS
			dot = (original_file[i][j] == *replacer); //checking to see if the current characer is a dot
			top = (i==0); //will return true if we are at the first line in the text file
			bottom = (i==(original_file.size()-1));  //will return true if we are at the last line in the text file
			first = (j==0); //checking to see if the character is the first in the row
			last = (j==(length-1)); //checking to see if the character is the last in the row
			//ADJACENT PIXEL BOOLEANS
			left = right = up = down = true;
			if (!first)
				left = (original_file[i][(j-1)]!=*replacer); //each is checking to see if the pixel is the symbol that is to be replaced
			if (!last)
				right = (original_file[i][(j+1)]!=*replacer);
			if (!top)
				up = (original_file[i-1][j]!=*replacer);
			if (!bottom)
				down = (original_file[i+1][j]!=*replacer);
			if ((top) && (first) && (!dot)) { //top left pixel
				if (!right || !down) {  //if one of the adjacent pixels is the same as the dilation character,but all the adjacent pixels are not eqaul,
					//change the character,else, add a backgroung character to the new line
					new_line.push_back(*replacer);
				}
				else{
					new_line.push_back('.');
				}
			}
			else if ((top) && (last) && (!dot)) {  //top right pixel
				if (!left || !down)  {
					new_line.push_back(*replacer);
				}
				else{
					new_line.push_back('.');
				}
			}
			else if ((bottom) && (first) && (!dot)) { //bottom left
				if (!right || !up) {
					new_line.push_back(*replacer);
				}
				else{
					new_line.push_back('.');
				}
			}
			else if ((bottom) && (last) && (!dot)) {  //bottom right
				if (!left || !up) {
					new_line.push_back(*replacer);
				}
				else{
					new_line.push_back('.');
				}
			}
			else if ((top) && (!dot)) {  //anything in top row
				if (!left || !right || !down) {
					new_line.push_back(*replacer);
				}
				else{
					new_line.push_back('.');
				}
			}
			else if ((bottom) && (!dot)) {  //anything in bottom row
				if (!left || !right || !up ){
					new_line.push_back(*replacer);
				}
				else{
					new_line.push_back('.');
				}
			}
			else if ((first) && (!dot)) { //first in line
				if (!right || !up || !down) {
					new_line.push_back(*replacer);
				}
				else{
					new_line.push_back('.');
				}
			}
			else if ((last) && (!dot)) {  //last in line
				if (!left|| !up|| !down) {
					new_line.push_back(*replacer);
				}
				else{
					new_line.push_back('.');
				}
			}
			else if (!dot) { //any other position in the file
				if (!left || !right || !up || !down) {
					new_line.push_back(*replacer);
				} else {
					new_line.push_back('.');
				}
			} else
				new_line.push_back(*replacer);
		}
		new_file.push_back(new_line);
	}
	return new_file;
}

//FLOODFILL OPERATION
void floodfill (vector <string> & original_file,int x,int y,char replacer,char original_character) {
	bool top,bottom,first,last; //booleans to stop each floodfill check from going out of bounds
	top = (y < 0); //will return true if we are outside the top of the file
	bottom = (y > (original_file.size()-1));  //will return true if we are outside the bottom of file
	first = (x < 0); //checking to see if the character is outside the left side of the file
	last = (x > (original_file[0].size()-1)); //checking to see if the character is outside the right side of the file
	if  ((!top) && (!bottom) && (!first) && (!last) && (original_file[x][y] == original_character)){ //if the current character is 
		//part of the shape,fill it in
		original_file[x][y] = replacer;
		floodfill (original_file,x-1,y,replacer,original_character); //flood fill cheking left pixel
		floodfill (original_file,x+1,y,replacer,original_character); //flood fill checking right pixel
		floodfill (original_file,x,y-1,replacer,original_character); //flood fill checking bottom pixel
		floodfill (original_file,x,y+1,replacer,original_character); //flood fill checking upper pixel
	}	
}

int main(int argc, char* argv[]) {
	//Error Checking
	//Checking number of arguments
	if ((argc < 5) or (argc > 7)) {
		cerr << "There are not enough or too many arguments.";
		return 1;
	}
	// If it has reached this point, it will start checking for an operation
	if (strcmp(argv[3], "replace") == 0) {
		//The argc for replace must conatain 6 argumets (execution,file name,output name,operation,character one,character two)
		if (argc < 6) {
			cerr << "Not enough commands given for replace.";
			return 1;
		}
		//Checking if characters are the same
		else if (strcmp(argv[4], argv[5]) == 0) {
			cerr << "Characters can't be the same.";
			return 1;
		}
	}
	if (strcmp(argv[3], "floodfill") ==0) {
		if (argc < 6) {
			cerr << "Not enough commands for floodfill.";
			return 1;
			}
			//Checking if the arguments are ints
			else if ((!isdigit(*argv[4])) and !isdigit(*argv[5])) {
				cerr << "Both arguments need to be integers.";
				return 1;
			}
			//Checking if the last arument is a character
			// else if (isdigit((*argv[5]))) {
			// 	cerr << "Last argument must be a character.";
			// 	return 1;
			// }
		}
	if ((strcmp(argv[3], "erosion") == 0) or (strcmp(argv[3], "dilation") == 0)) {
		//The argc for replace must conatain 5 or 6 argumets (execution,file name,output name,operation,character one,character two(could be a backslash))
		if (argc < 5) {
			cerr << "Not enough commands given.";
			return 1;
		}
	}
	//Checking to see if the file is open
	ifstream input_file (argv[1]);
	if (!input_file.is_open()) {//if the file is not open
		cerr << "Error while opening file";
		return 1;
	}
	else {
		string line;  //each line of the file
		vector <string> original_file; //string vector, original_file[0] will be the entire text document
		while (input_file >> line) { //sending each line from the file to input_file
			if (input_file.good()){ //if the file is not corrupted,add each line to the vector original_line
				original_file.push_back(line);
			}
		}
		//CALLING EACH FUNCTION AND WRITING IT TO A NEW TEXT FILE
		if ((strcmp(argv[3], "replace") == 0)) {
			vector <string> a = replace(original_file,argv[4],argv[5]);

			ofstream output_file;
			output_file.open(argv[2]);
			for (int i=0;i<a.size();i++) {
				output_file << a[i] << "\n";
			}
		}
		if ((strcmp(argv[3], "erosion") == 0)) {
			vector <string> a = erosion(original_file,argv[4],argv[5]);
			ofstream output_file;
			output_file.open(argv[2]);
			for (int i=0;i<a.size();i++) {
				output_file << a[i] << "\n";
			}
		}
		if ((strcmp(argv[3], "dilation") == 0)){
			vector <string> a = dilation(original_file,argv[4]);
			ofstream output_file;
			output_file.open(argv[2]);
			for (int i=0;i<a.size();i++) {
				output_file << a[i] << "\n";
			}
		}
		if ((strcmp(argv[3], "floodfill") == 0)){
			int i,j; //2 integers that will be used for recursion in floodfill
			i =atoi(argv[4]); j =atoi(argv[5]); //converting them to integers
			char original_character = original_file[i][j];
			floodfill(original_file,i,j,argv[6][0],original_character);
			ofstream output_file;
			output_file.open(argv[2]);
			for (int i=0;i<original_file.size();i++) {
				output_file << original_file[i] << "\n";
			}
		}
	}return 0;
}	
 