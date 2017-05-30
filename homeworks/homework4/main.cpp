//
// PROVIDED CODE FOR HOMEWORK 4: GROCERY LISTS
// 
// You may use none, a little, or all of this, as you choose, but we
// strongly urge you to examine it carefully.  You may modify this
// code as you wish to complete the assignment.
//


#include <cassert>
#include <cstdlib>
#include <iostream>
#include <fstream>

#include "recipe.h"
#include "kitchen.h"
#include "ingredient.h"
#include <list>
#include <algorithm>


// Helper functions
void readRecipe(std::istream &istr, std::ostream &ostr, std::list<Recipe> &recipes);
void addIngredients(std::istream &istr, std::ostream &ostr, Kitchen &kitchen);
void printRecipe(std::istream &istr, std::ostream &ostr,std::list<Recipe> &recipes);
void makeRecipe(std::istream &istr, std::ostream &ostr, const std::list<Recipe> &recipes, Kitchen &kitchen);
void recipeSuggestions(std::ostream &ostr, const std::list<Recipe> &recipes, const Kitchen &kitchen);

// The main loop parses opens the files for I/O & parses the input
int main(int argc, char* argv[]) {

  // Check the number of arguments.
  if (argc != 3) {
    std::cerr << "Usage: " << argv[0] << " in-file out-file\n";
    return 1;
  }
  // Open and test the input file.
  std::ifstream istr(argv[1]);
  if (!istr) {
    std::cerr << "Could not open " << argv[1] << " to read\n";
    return 1;
  }
  // Open and test the output file.
  std::ofstream ostr(argv[2]);
  if (!ostr) {
    std::cerr << "Could not open " << argv[2] << " to write\n";
    return 1;
  }

  // the kitchen & recipe list
  Kitchen kitchen;
  std::list<Recipe> recipes;

  // some variables to help with parsing
  char c;
  while (istr >> c) {
    if (c == 'r') {
      // READ A NEW RECIPE
      readRecipe(istr,ostr,recipes);

    } else if (c == 'a') {
      // ADD INGREDIENTS TO THE KITCHEN
      addIngredients(istr,ostr,kitchen);
      
    } else if (c == 'p') {
      // PRINT A PARTICULAR RECIPE
      printRecipe(istr,ostr,recipes);

    } else if (c == 'm') {
      // MAKE SOME FOOD
      makeRecipe(istr,ostr,recipes,kitchen);

    } else if (c == 'k') {
      // PRINT THE CONTENTS OF THE KITCHEN
      kitchen.printIngredients(ostr);

    } else if (c == 's') {
      // SUGGEST ALL RECIPES THAT CAN BE MADE INDIVIDUALLY FROM THE
      //   CURRENT CONTENTS OF THE KITCHEN
      recipeSuggestions(ostr,recipes,kitchen);

    } else if (c == 'd') {
      // EXTRA CREDIT: SUGGEST THE COLLECTION OF RECIPES THAT CAN BE
      // MADE TOGETHER THAT USE THE MAXIMUM NUMBER OF UNITS OF
      // INGREDIENTS
    } else {
      std::cerr << "unknown character: " << c << std::endl;
      exit(0);
    }
  }  
}

//creates a recipe class,checks to see if it already exists,if not,the recipe is added to the list
void readRecipe(std::istream &istr, std::ostream &ostr, std::list<Recipe> &recipes) {
  int units; //the number of units of the ingredient from the file
  std::string name, name2;                  //variables representing the string of each class
  istr >> name;                             //reading the first string in the file to the first name
  // build the new recipe
  Recipe r(name);                           //creating the recipe class
  while (1) {
    istr >> units;                          //converting the unit to an integer
    if (units == 0) break;
    assert (units > 0);                     //the function can't add zero ingrdients
    istr >> name2;                          //name2 will represent the ingrdient
    Ingredient new_ingredient(name2,units); //creating an ingredient object for the list
    r.addIngredient(new_ingredient);        //adding an ingredient object to the recipe class
  }
  bool doesnt_exist = true;                                           //bool being used when cheking to see if the recipe is in the list
  std::list<Recipe>::iterator it;                                     //declaring an iterator for the loop used for the check
  for (it = recipes.begin();it != recipes.end();it++) {               //looping through the list
    if ((*it).get_name() == name) {                                   //if one of the recipe's names = the recipe input name
      ostr << "Recipe for " << name << " already exists" << std::endl;//output this statement to the string
      doesnt_exist = false;                                           //the recipe does exist now
      break;
    }
  }
  if (doesnt_exist){                                                //if the recipe doesn't exist
    recipes.push_back(r);                                           //add it to the list
    ostr << "Recipe for " << name << " added" << std::endl;         //output this statement to the file
  }
}


void addIngredients(std::istream &istr, std::ostream &ostr, Kitchen &kitchen) {
  int units;                            //number of units of the ingredient
  std::string name;                     //name of the ingredient
  int count = 0;                        //the count will keep track of the number of ingredients being added
  while (1) {
    istr >> units;
    if (units == 0) break;              //if the units are ever zero,add nothing
    assert (units > 0);
    istr >> name;                       //send the ingrdient name to this string variable
    Ingredient new_ingredient(name,units); //creating an ingredient object for the list
                                        // add the ingredients to the kitchen object's list
    kitchen.addIngredient(new_ingredient); //adding an ingredient object to the kitchen class' ingredient list
    count++;                            //increase the count by 1 since we are counting unique ingrdients,not units added
  }
  if (count <2) {
    ostr << count << " ingredient added to kitchen" << std::endl;
  }
  else {
    ostr << count << " ingredients added to kitchen" << std::endl;
    }
}

//writing the recipe to the file
void printRecipe(std::istream &istr, std::ostream &ostr,std::list<Recipe> &recipes) {
  std::string name;                                    //given a name
  istr >> name;                                        //send the name from the file to this string
  std::list<Recipe>::iterator it;                      //declaring an iterator
  bool printed = false;                                //confirms if the name was matched and the print function ran
  for(it = recipes.begin();it !=recipes.end();it++){   //looping throught the recipe list
    if ((*it).get_name() == name) {                    //when the name and the name of the recipe object match up,
      (*it).print_ingredients(ostr);                   //writing the recipe to the file
      printed = true;                                  //run the print function that is part of the recipe
    }
  }
  if (printed == false) {                              //if the the recipe did not exist or wasn't printed,write thisw statement to the file
    ostr << "No recipe for " << name <<endl;
  }
}

//making a recipe by comparing the ingredients from the recipe to whats in the kitchen
//if we have ingredients, we will output a statement saying it was made, then the inventory in the kitchen 
//would be adjusted
void makeRecipe(std::istream &istr, std::ostream &ostr, const std::list<Recipe> &recipes, Kitchen &kitchen) {
  std::string name;                                                 //reading the erecipe name from thefile
  istr >> name;                                                     //sending the recipe name to the name string
  std::list<Recipe>::const_iterator it;                             //declaring an iterator for the recipe list
  std::list<Ingredient>::const_iterator it2;                        //declarig an iterator for the recipe's ingredients list
  std::list<Ingredient>::iterator it3;                              //3rd iterator for the kitchen's ingredient list
  std::list<Ingredient> missing_ingredients;                        //list of missing ingredients
  list<Ingredient> * kitchen_ingredients = kitchen.get_ingredients();//getting the list of all the ingredients in the kitchen
  list<Ingredient> ingredients_needed;                              //will be a list of the ingredients needed for the recipe
  bool enough_ingredients = true;                                   //boolean value to show there are enough ingredients
  for (it = recipes.begin();it != recipes.end();it++) {
    if ((*it).get_name() == name) {                                 //when we find the recipe in the list
      ingredients_needed = (*it).get_ingredients();                 //pull out the recipe's ingredients
      break;
    }
  }
  if (ingredients_needed.begin() == ingredients_needed.end()) {
    ostr << "Do not know how to make " << name <<endl;
    return;
  }
  else {
    for (it2 = ingredients_needed.begin();it2 != ingredients_needed.end();it2++){            //checkin to see if the ingredients are in the kitchen
      bool found = false;
      for(it3 = (*kitchen_ingredients).begin();it3 != (*kitchen_ingredients).end();it3++){   //looping throught the recipe's ingredientss 
        if ((*it2).get_name() == (*it3).get_name()) {                                        //if the ingredient is found in both lists
          found = true;
          if ((*it3).get_units() < (*it2).get_units()) {                                     //check if there are not enough ingredients in the kitchen
            enough_ingredients = false;                                                      //there are not enough ingredients 
            missing_ingredients.push_back(*it2);
          }
        }
      }
      if ((found == false) && (it3 == (*kitchen_ingredients).end())){  //special condition for when we dont find the ingredient for the recipe in the kitchen
        missing_ingredients.push_back(*it2);
      }
    }
    if ((missing_ingredients.size() > 0) && (enough_ingredients)){
      std::list<Ingredient>::iterator missing_iterator;
      ostr << "Cannot make " << name << ", need to buy:"<<endl; 
      for(missing_iterator = ingredients_needed.begin();missing_iterator != ingredients_needed.end();missing_iterator++){
        for(it3 = (*kitchen_ingredients).begin();it3 != (*kitchen_ingredients).end();it3++){    //looping throught the kitchen's ingredientss
          if ((*missing_iterator).get_name() == (*it3).get_name()) {
            int difference = (*missing_iterator).get_units() - (*it3).get_units();                //difference between requirement and kitchen inventory
            if (difference < 0) {                                                                 //if the difference is negative,give what the recip calls for
              ostr << "  " << (*missing_iterator).get_units() << " units of " << (*missing_iterator).get_name() <<endl;
            }
            else {
              if (difference < 2) {
                ostr << "  " << difference << " unit of " << (*missing_iterator).get_name() <<endl;
              }
              else{
                ostr << "  " << difference << " units of " << (*missing_iterator).get_name() <<endl; //default "not enough" statement
              }
            }
          }
        }
      }
    }
    if ((missing_ingredients.size() == 0) && (enough_ingredients)) { 
      ostr << "Made " << name <<endl;                                                           //if there are enough ingredients
      for (it2 = ingredients_needed.begin();it2 != ingredients_needed.end();it2++){             //look through the ingredients in the kitchen
        for(it3 = (*kitchen_ingredients).begin();it3 != (*kitchen_ingredients).end();it3++){   //looking through the recipe's ingrdients
          if ((*it2).get_name() == (*it3).get_name()) {                                   //when we find the ingredient in both lists
            (*it3).subtract_units((*it2).get_units());                                 //subtract the recipe's units from those from the kitchen
          }
        }
      }
    }
  }
}


void recipeSuggestions(std::ostream &ostr, const std::list<Recipe> &recipes, const Kitchen &kitchen) {
  list<string> suggestions;                                                    //list that will hold the names of recipes that can be made
  list<Recipe>::const_iterator recipe_it;                                      //iterator for the recipe list
  bool can_be_made = false;                                                    //bool to check if the recipe can be made
  for(recipe_it = recipes.begin(); recipe_it != recipes.end(); recipe_it++){   //looping through the recipe list
    list<Ingredient> ingredients_needed = (*recipe_it).get_ingredients();      //pulling out the ingredients necessary for the list
    can_be_made = kitchen.suggestions(ingredients_needed);                     //checking if there are enough ingredients
    if (can_be_made == true) {                                                 //if the recipe can be made
      suggestions.push_back((*recipe_it).get_name());                          //add it's name to the suggestion list
    }
  }
  list<string>::iterator suggestions_it = suggestions.begin();                 //iterator for suggestions list
  if (suggestions_it != suggestions.end()) {                                   //if there at least one recipe that can be made
    suggestions.sort();                                                        //sorting the names 
    ostr << "Recipes that can be prepared:" <<endl;                            //writing the first statement to the file
    for (suggestions_it = suggestions.begin();suggestions_it != suggestions.end();suggestions_it++) {
      ostr << "  " << *suggestions_it << endl;                                 //writing each name to the file
    }
  }
  else{
    ostr << "No recipes can be prepared" << endl;                              //if nothing can be made,write this to the file
  }
}

