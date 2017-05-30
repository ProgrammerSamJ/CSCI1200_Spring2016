#include "ingredient.h"
#include <iostream>
#include <string>
#include <sstream>
#include <list>
//============================
//CONSTRUCTOR
//============================
Ingredient::Ingredient(string ingredient_name,int ingredient_units) {
	name = ingredient_name;
	units = ingredient_units;
}

//============================
//ACCESSORS
//============================
//getting the ingredient's name
string Ingredient::get_name() const {
	return name;
}
//getting the ingredients unit
int Ingredient::get_units() const {
	return units;
}
//============================
//MODIFIERS
//============================
//changing the numbe rof units for an ingredient
//the units will be increased by n
void Ingredient::add_units(int n) {
	units+=n;
}
//the units will be decreased by n
void Ingredient::subtract_units(int n){
	units-=n;
}	
//=================================
//NON-MEMBER FUNCTIONS
//================================
//ATTEMPT AT CREATING THE SORT
// bool ingredient_sort(const Ingredient &ing1,const Ingredient &ing2){
// 	if (ing1.get_units() < ing2.get_units()){
// 		return true;
// 	}
// 	else {
// 		if (ing1.get_name() < ing2.get_name()) {
// 			return true;
// 		}
// 		else {
// 			return false;
// 		}
// 	}return false;
// }
