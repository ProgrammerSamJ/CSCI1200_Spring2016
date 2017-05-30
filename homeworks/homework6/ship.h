#ifndef __ship_h_
#define __ship_h_
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class Ship{
public:
	//CONSTRUCTOR
	Ship();
	Ship(std::string shipname);

	//ACCESSORS
	const std::string getname() const{return name;}
	const int getlength() const{return length;}
	const std::string getorientation() const{return orientation;}
	std::vector< std::vector<int> > getHorizontalLocations(){return verticalLocations;}
	std::vector< std::vector<int> > getVerticalLocations(){return horizontalLocations;}
	int getx() const{return x;}
	int gety() const{return y;}

	//MODIFIERS
	void setorigin(int x_,int y_);
	void setorientation(std::string direction);
	void addHorizontalLocation(std::vector<int>);
	void addVerticalLocation(std::vector<int>);

private:
	//REPRESENTATION
	std::string name;		//ship's name
	int x,y;				//integers representing the first piece of the object on the board
	std::vector< std::vector<int> > horizontalLocations; //horizontal ship locations
	std::vector< std::vector<int> > verticalLocations;	 //vertical ship locaitons
	int length;				//amount of space the ship takes up
	std::string orientation;//verticallly or horizontally placed
};
#endif


