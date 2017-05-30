// CSCI 1200 Data Structures
// Homework 5: Multi-Linked Lists


// NOTE: You should not need to make any changes to this file, except
// to add your own test cases at the bottom of the file where
// indicated.


#include <iostream>
#include <cmath>
#include <string>
#include <list>
#include <vector>
#include <cassert>
#include <cstdlib>

#include "multi_linked_list.h"

void ProvidedTests();
void StudentTests();


// ================================================================================
// A simple function to test if two STL lists contain the "same" elements
// returns true if it contains the same number of elements in the same order
// otherwise returns false
template <class T> bool same(const std::list<T> &a, const std::list<T> &b) {
  if (a.size() != b.size()) return false;
  typename std::list<T>::const_iterator a_itr = a.begin();
  typename std::list<T>::const_iterator b_itr = b.begin();
  while (a_itr != a.end()) {
    if (*a_itr != *b_itr) return false;
    a_itr++;
    b_itr++;
  }
  return true;
}



// ================================================================================
// This program stress tests the templated MultiLL container class


int main() {
  ProvidedTests();
  StudentTests();
}


// ================================================================================
// ================================================================================

void ProvidedTests() {

  std::cout << "Begin ProvidedTests..." << std::endl;

  // The test data (stored in STL lists)
  std::list<std::string> songs;
  songs.push_back("hound dog");
  songs.push_back("poker face");
  songs.push_back("brown eyed girl");
  songs.push_back("let it be");
  songs.push_back("walk like an egyptian");
  songs.push_back("man in the mirror");
  songs.push_back("stairway to heaven");
  songs.push_back("dancing in the street");
  songs.push_back("every breath you take");
  songs.push_back("hotel california");
  // the same data, sorted!
  std::list<std::string> sorted_songs(songs);
  sorted_songs.sort();


  // create an empty multi-linked list and fill it with the test data
  MultiLL<std::string> my_list;
  for (std::list<std::string>::iterator itr = songs.begin(); itr != songs.end(); itr++) {
    my_list.add(*itr);
  }
  assert (songs.size() == my_list.size());

  // -------------------
  // iterator tests
            
  // test the chronological iterator (forwards)
  std::cout << "chronological order" << std::endl;
  std::list<std::string> chrono_order;
  MultiLL<std::string>::iterator itr = my_list.begin_chronological();
  while (itr != my_list.end_chronological()) {
    std::cout << "  " << *itr << std::endl;
    chrono_order.push_back(*itr);
    itr++;
  }
  std::cout << std::endl;
  assert (same(songs,chrono_order));


  // test the sorted order iterator (forwards)
  std::cout << "sorted order" << std::endl;
  std::list<std::string> sorted_order;
  itr = my_list.begin_sorted();
  while (itr != my_list.end_sorted()) {
    std::cout << "  " << *itr << std::endl;
    sorted_order.push_back(*itr);
    itr++;
  }
  std::cout << std::endl;
  assert (same(sorted_songs,sorted_order));


  // test the random order iterator
  std::cout << "random order" << std::endl;
  std::list<std::string> random_order;
  itr = my_list.begin_random();
  for (unsigned int i = 0; i < my_list.size(); i++,itr++) {
    std::cout << "  " << *itr << std::endl;
    random_order.push_back(*itr);
  }
  std::cout << std::endl;
  // loop through the elements a second time (the order should be the same!)
  std::list<std::string>::iterator itr2 = random_order.begin();
  for (unsigned int i = 0; i < my_list.size(); i++,itr++,itr2++) {
    // verify that the elements repeat the order
    assert (*itr == *itr2);
  }
  std::list<std::string> random_order_check(random_order);
  random_order_check.sort();
  // verify that all of the elements appeared in the initial loop
  assert (same(sorted_songs,random_order_check));



  // test the re-randomization by creating a new random iterator
  std::cout << "random order 2" << std::endl;
  std::list<std::string> random_order2;
  itr = my_list.begin_random();
  for (unsigned int i = 0; i < my_list.size(); i++,itr++) {
    std::cout << "  " << *itr << std::endl;
    random_order2.push_back(*itr);
  }
  std::cout << std::endl;
  // with over 3 million different possible permutations of 10
  // elements, it is highly unlikely they will be the same!
  assert (!same(random_order,random_order2));


  
//   // -------------------
//   // erase tests

  // erase the first element inserted
  itr = my_list.begin_chronological();
  assert (*itr == "hound dog");
  itr = my_list.erase(itr);
  assert (*itr == "poker face");
  assert (my_list.size() == 9);
  std::cout << "erased: hound dog" << std::endl;

  // erase the second to last element in sorted order
  itr = my_list.begin_sorted();
  for (int i = 0; i < 7; i++) { std::cout << *itr << std::endl;
    itr++; }
  assert (*itr == "stairway to heaven");
  itr = my_list.erase(itr);
  assert (*itr == "walk like an egyptian");
  assert (my_list.size() == 8);  
  std::cout << "erased: stairway to heaven" << std::endl;

  // erase the third element in the random order
  itr = my_list.begin_random();
  itr++;
  itr++;
  std::string tmp = *itr;
  // note that the return value of erase with a random iterator is undefined
  my_list.erase(itr);
  std::cout << "erased: " << tmp << std::endl;
  assert (my_list.size() == 7);
  assert (!my_list.empty());

  my_list.clear();
  assert (my_list.empty());
  assert (my_list.size() == 0);
  std::cout << "cleared the whole list!" << std::endl << std::endl;

  std::cout << "Finished ProvidedTests." << std::endl;
}

// // ================================================================================
// // ================================================================================

void StudentTests() {

  std::cout << "Begin StudentTests..." << std::endl;

  // ---------------------------
  // ADD YOUR OWN TEST CASES BELOW
  std::list<std::string> songs;
  songs.push_back("hound dog");
  songs.push_back("poker face");
  songs.push_back("brown eyed girl");
  songs.push_back("let it be");
  songs.push_back("walk like an egyptian");
  songs.push_back("man in the mirror");
  songs.push_back("stairway to heaven");
  songs.push_back("dancing in the street");
  songs.push_back("every breath you take");
  songs.push_back("hotel california");
  MultiLL<std::string> my_list;
  for (std::list<std::string>::iterator itr = songs.begin(); itr != songs.end(); itr++){
    my_list.add(*itr);
  }
  //-------------------TESTS------------------------------
  //COPY CONSTRUCTOR
  std::cout << "COPYING THE LIST(same size after call):" << std::endl;
  MultiLL<std::string> my_copied_list(my_list);
  std::cout <<"old list size: "<< my_list.size() <<std::endl;
  std::cout <<"new list size: "<< my_copied_list.size() <<std::endl;

  std::cout << "The lists are the same size"  << std::endl; 
  //-----ERASE CASES-------
  MultiLL<std::string>::iterator itr;
  std::cout<< "\nERASE A CHRONOLOGICAL HEAD" <<std::endl;
  itr = my_list.begin_chronological();
  std::cout << "before:" << *itr << std::endl;
  itr = my_list.erase(itr);
  std::cout << "after:" << *itr << std::endl;

  std::cout<< "\nERASE A SORTED HEAD" <<std::endl;
  itr = my_list.begin_sorted();
  std::cout << "before:" << *itr << std::endl;
  itr = my_list.erase(itr);
  std::cout << "after:" << *itr << std::endl;

  std::cout<< "\nERASE A RANDOM HEAD" <<std::endl;
  itr = my_list.begin_random();
  std::cout << "before:" << *itr << std::endl;
  itr = my_list.erase(itr);
  std::cout << "after:" << *itr << std::endl;

  std::cout<< "\nERASE A REGULAR ELEMENT" <<std::endl;
  itr = my_list.begin_sorted();
  itr++;
  std::cout << "before:" << *itr << std::endl;
  itr = my_list.erase(itr);
  std::cout << "after:" << *itr << std::endl;

  //DESTROY LIST
  my_list.clear();

  //MULTILL OF INTEGERS TEST
  std::list<int> numbers;
  numbers.push_back(1);
  numbers.push_back(5);
  numbers.push_back(21);
  numbers.push_back(3);
  numbers.push_back(0);
  numbers.push_back(98);
  MultiLL<int> my_int_list;
  

  //EMPTY TEST(BEFORE ELEMENTS ADDED)
  assert (my_int_list.empty() == true);
  std::cout << "The new integer list is empty";
  

  //EMPTY TEST(AFTER ELEMENTS ADDED)
  std::cout << "Elements are being added:" <<std::endl;
  for(std::list<int>::iterator itr = numbers.begin(); itr != numbers.end(); itr++) {
    my_int_list.add(*itr);
  }
  assert (numbers.size() == my_int_list.size());
  assert (my_int_list.empty() == false);
  std::cout << "The new integer list has elements" <<std::endl;

  std::cout << "\nCHRONOLOGICAL ORDER" <<std::endl;
  std::list<int> chrono_num_order;
  MultiLL<int>::iterator itr2= my_int_list.begin_chronological();
  while (itr2 != my_int_list.end_chronological()) {
    std::cout << "  " << *itr2 << std::endl;
    chrono_num_order.push_back(*itr2);
    itr2++;
  }

  std::cout << "\nSORTED ORDER" <<std::endl;
  std::list<int> sorted_num_order;
  itr2 = my_int_list.begin_sorted();
  while (itr2 != my_int_list.end_sorted()) {
    std::cout << "  " << *itr2 << std::endl;
    sorted_num_order.push_back(*itr2);
    itr2++;
  }

  //ERASE TEST
  std::cout << "\nERASING A HEAD" <<std::endl;
  itr2 = my_int_list.begin_chronological();
  std::cout << "before:" << *itr2 << std::endl;
  itr2 = my_int_list.erase(itr2);
  std::cout << "after:" << *itr2 << std::endl;

  //CLEAR TEST
  std::cout<<"\nClearing list:" <<std::endl;   
  my_int_list.clear();   
  assert (my_int_list.empty() == true);
  std::cout << "The new integer list is empty" <<std::endl;




  std::cout << "Finished StudentTests." << std::endl;
}

// // ================================================================================
