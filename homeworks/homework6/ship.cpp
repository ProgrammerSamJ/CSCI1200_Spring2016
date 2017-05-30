#include "ship.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
//==================
//CONSTRUCTOR
//==================
Ship::Ship(std::string shipname){
	name = shipname;
	orientation = "horizontal"; //ship orientation will initially be horizontal
	x = 0;
	y = 0;

	if(name == "submarine")		//based on the name of the ship,the length will be set
		length = 1;
	if(name == "destroyer")
		length = 2;
	if(name == "cruiser")
		length = 3;
	if(name == "battleship")
		length = 4;
	if(name == "carrier")
		length = 5;
	if(name == "cargo")
		length = 6;
	if(name == "tanker")
		length = 7;
}
//===================
//MODIFIERS
//===================

//SET THE LOCATION OF THE LEFTMOST PIECE OF THE SHIP
void Ship::setorigin(int x_, int y_){
	x = x_;
	y = y_;
}

//ADD A HORIZONTAL LOCATION THE SHIP CAN BE PLACED
void Ship::addHorizontalLocation(std::vector<int> temp){
	horizontalLocations.push_back(temp);
}

//ADD A VERTICAL LOCATION THE SHIP CAN BE PLACED
void Ship::addVerticalLocation(std::vector<int> temp){
	verticalLocations.push_back(temp);
}

//SET THE ORIENTATION OF THE SHIP
void Ship::setorientation(std::string direction){
	orientation = direction;
}