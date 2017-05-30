#ifndef __recipe_h_
#define __recipe_h_
#include "ingredient.h"
#include <iostream>
#include <string>
#include <sstream>
#include <list>
using namespace std;

//Recipe is a class consisting of a recipe's name and ingredients
class Recipe {
public:
	//CONSTRUCTOR
	Recipe(string recipe_name); //a recipe onject is constructed wiht a name
	
	//ACCESSORS
	string get_name() const;
	void print_ingredients(std::ostream &ostr);
	list<Ingredient> get_ingredients() const;

	//MODIFIERS/OTHER HELPFUL FUNCTIONS
	void addIngredient(Ingredient &new_ingredient);
private: // REPRESENTATION
	string name;
	list<Ingredient> ingredients;
};
//NON MEMBER FUNCTIONS
bool ingredient_sort(const Ingredient &ing1,const Ingredient &ing2);
bool ingredient_sort_name(const Ingredient &ing1,const Ingredient &ing2);
#endif
