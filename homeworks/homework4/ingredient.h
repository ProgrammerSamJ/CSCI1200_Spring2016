#ifndef __ingredient_h_
#define __ingredient_h_
#include <iostream>
#include <string>
#include <sstream>
#include <list>
using namespace std;

//The ingredient object consists of a name and the number of units of the ingredient
class Ingredient {
public:
	//CONSTRUCTOR
	Ingredient(string ingredient_name,int ingredient_units); //default constructor for kitchen object
	
	//ACCESSORS
	string get_name() const;
	int get_units() const;

	//MODIFIERS
	void add_units(int n);
	void subtract_units(int n);

private: // REPRESENTATION
	string name; //list of all ingredients in the kitchen
	int units;
};
//bool ingredient_sort(const Ingredient &ing1,const Ingredient &ing2);
#endif