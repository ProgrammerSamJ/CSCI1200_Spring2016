#include "recipe.h"
#include "ingredient.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;
//============================
//CONSTRUCTOR
//============================
Recipe::Recipe(string recipe_name){ //a recipe obsject is constructed with a name
	name = recipe_name;
}

//============================
//ACCESSORS
//============================
//just getting the name of the recipe
string Recipe::get_name() const{	
	return name; 
}
//returns the list of ingredients needed for the recipe
list<Ingredient> Recipe::get_ingredients() const{
	return ingredients;
}
//writes the ingredients for the recipe to the file
void Recipe::print_ingredients(std::ostream &ostr) {
	list<Ingredient>::iterator output_iterator;							     //establishing an itterator
	ostr << "To make " << name << ", mix together:" <<endl;					//writing the first statement
	ingredients.sort(ingredient_sort);								//sorting the list by name
	for (output_iterator = ingredients.begin();output_iterator !=ingredients.end();output_iterator++){  //looping through the ingrdient list
		int unit = (*output_iterator).get_units();									//getting the units for each ingrdient
		if ((unit != 0) &&(unit < 2)) {																//special statement for when there is only 1 unit
			ostr << "  " << unit << " unit of " << (*output_iterator).get_name() <<endl;
		}
		else if ((unit !=0) && (unit >= 2)){
			ostr << "  " << unit << " units of "<< (*output_iterator).get_name() <<endl;	//regular statement that will be written to the file
		}
	}
}

//====================================
//MODIFIERS/OTHER HELPFUL FUNCTIONS
//==================================== 
//adding an ingrdient to the recipe
void Recipe::addIngredient(Ingredient& new_ingredient){
	ingredients.push_back(new_ingredient);
}
//sorting the ingredient list by units
bool ingredient_sort(const Ingredient &ing1,const Ingredient &ing2){
	if (ing1.get_units() < ing2.get_units()){
		return true;
	}
	else {
		if (ing1.get_name() < ing2.get_name()) {
			return true;
		}
		else {
			return false;
		}
	}return false;
}
//sorting by name
bool ingredient_sort_name(const Ingredient &ing1,const Ingredient &ing2){
	if (ing1.get_name() < ing2.get_name()) {
		return true;
	}
	else {
		return false;
	}
}
