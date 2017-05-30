#include "kitchen.h"
#include "ingredient.h"
#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;
//============================
//CONSTRUCTOR
//============================
Kitchen::Kitchen() {
}

//============================
//ACCESSORS
//============================
//Seeing all the ingredients in the kitchen
//ingredients are sorted by name and printed with units forst
void Kitchen::printIngredients(std::ofstream &ostr){
	list<Ingredient>::iterator output_iterator; 									//creatng an iterator
	ostr << "In the kitchen:" <<endl;  												//writing the first statement
	// ingredients.sort(ingredient_sort); 												//sorting the ingrdient list by name
	for (output_iterator = ingredients.begin();output_iterator !=ingredients.end();output_iterator++){
		int unit = (*output_iterator).get_units();									//finding the unit for the ingredient
		if (unit == 0){
			continue;
		}
		if (unit < 2) {//custom statement when units are less than 1
			ostr << "  " << (*output_iterator).get_units() << " unit of " << (*output_iterator).get_name() <<endl;
		}
		else {//default statement
			ostr << "  " << (*output_iterator).get_units() << " units of " << (*output_iterator).get_name() <<endl;
		}
	}
}

//===================================
//MODIFIERS/OTHER HELPFUL FUNCTIONS
//===================================
//Adding an ingredient to the list of ingredients in the kitchen,
//the amount of times the name will appear in the string will be determined by the units parameter
void Kitchen::addIngredient(Ingredient& new_ingredient){
	list<Ingredient>::iterator it; 								  //declaring an iterator "it" to add the ingredients to the temporary list
	if (ingredients.size() > 0) {								  //if there are ingredients in the kitchen
		for(it = ingredients.begin();it != ingredients.end();it++) {//check if the ingredient is already in there
			if (new_ingredient.get_name() == (*it).get_name()) {  //if the ingredient is already in the list,increase it's units by those
				(*it).add_units(new_ingredient.get_units());	  //of the new ingredient being added
				break;
			}
			ingredients.push_back(new_ingredient);				  //if the ingredient object is not in the list,add it, then break out the loop
			break;
		}
	}
	else {
		ingredients.push_back(new_ingredient);				  
	}
}
//getting all the ingredients in the kitchen
//returns a pointer to the actual kitchen list so we know the inventory will actually change
list<Ingredient>* Kitchen::get_ingredients() {
	return &ingredients;
}
bool Kitchen::suggestions (list<Ingredient> &ingredients_needed) const{
	std::list<Ingredient>::iterator it2;                       								//declarig an iterator for the recipe's ingredients list
  	std::list<Ingredient>::const_iterator it3;                              				//2nd iterator for the kitchen's ingredient list
  	for (it2 = ingredients_needed.begin();it2 != ingredients_needed.end();it2++){           //checkin to see if the ingredients are in the kitchen
  		for(it3 = ingredients.begin();it3 != ingredients.end();it3++){						//looping throught the recipe's ingredientss 
        	if ((*it2).get_name() == (*it3).get_name()) {                                   //if the ingredient is found in both lists
          		if ((*it3).get_units() < (*it2).get_units()) {                              //check if there are not enough ingredients in the kitchen
            		return true;                                                    		//there are not enough ingredients 
          		}
          		else{
          			return false;
          		}
        	}
      	}
    }return false;
}
//============================
//NON-MEMBER FUNCTIONS
//============================
