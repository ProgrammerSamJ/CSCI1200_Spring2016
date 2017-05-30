// A simple "caller ID" program

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <string>
using namespace std;

// // add a number, name pair to the phonebook
// void add(vector<string> &phonebook, int number, string const& name) {
//   phonebook[number] = name;
// }

// // given a phone number, determine who is calling
// void identify(const vector<string> & phonebook, int number) {
//   if (phonebook[number] == "UNASSIGNED") 
//     cout << "unknown caller!" << endl;
//   else 
//     cout << phonebook[number] << " is calling!" << endl;
// }

// add a number, name pair to the phonebook
void add(std::map<int,string> &phonebook2, int number, string const& name) {
  phonebook2.insert(std::make_pair(number,name));
}

// given a phone number, determine who is calling
void identify(map<int,string> &phonebook2, int number) {
  string name = "";
  for (map<int,string>::iterator it = phonebook2.begin();it != phonebook2.end();it++){
    if(it->first == number){
      name = it->second;
      break;
    }
  } 
  if(name == "")
    cout << "unknown caller!" << endl;
  else 
    cout << name << " is calling!" << endl;
}

int main() {
  // create the phonebook; initially all numbers are unassigned
  // vector<string> phonebook(10000, "UNASSIGNED");
  std::map<int,string> phonebook2;

  // // add several names to the phonebook
  // add(phonebook, 1111, "fred");
  // add(phonebook, 2222, "sally");
  // add(phonebook, 3333, "george");

  // // test the phonebook
  // identify(phonebook, 2222);
  // identify(phonebook, 4444);

  add(phonebook2, 1111, "fred");
  add(phonebook2, 2222, "sally");
  add(phonebook2, 3333, "george");

  // add(phonebook2, 1234562020202027, "kiki");
  // add(phonebook2, 1224242242929292, "bobby");
  add(phonebook2, 1234567, "jenny");
  add(phonebook2, 1224242242, "rick");

  identify(phonebook2, 2222);
  identify(phonebook2, 4444);
  identify(phonebook2, 123456);
  identify(phonebook2, 1224242242);

}
