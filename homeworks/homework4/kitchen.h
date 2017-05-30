#ifndef __kitchen_h_
#define __kitchen_h_
#include "ingredient.h"
#include <iostream>
#include <string>
#include <sstream>
#include <list>
using namespace std;

//The kitchen object consists 
class Kitchen {
public:
	//CONSTRUCTOR
	Kitchen(); //default constructor for kitchen object
	
	//ACCESSORS
	void printIngredients(std::ofstream &ostr);
	list<Ingredient>* get_ingredients();
	
	//MODIFIERS/OTHER HELPFUL FUNCTIONS
	void addIngredient(Ingredient& new_ingredient);
	bool suggestions (list<Ingredient> &ingredients_needed) const;

private: // REPRESENTATION
	list<Ingredient> ingredients; //list of all ingredients in the kitchen
};
#endif
bool ingredient_sort(const Ingredient &ing1,const Ingredient &ing2);