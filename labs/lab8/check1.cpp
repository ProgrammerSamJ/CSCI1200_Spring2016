#include <fstream>
#include <iostream>
#include <list>
#include <vector>
using namespace std;

void find_paths(int x,int y,int &j){
	if ((x == 0) || (y == 0)){
		j++;
		return;
	}
	if (x > 0){ //a pathis found when either x or y has been reduced to 0
		find_paths(x-1,y,j);
	}
	if (y > 0){
		find_paths(x,y-1,j);
	}
}


int main(){
	int j = 0;
	find_paths(2,2,j);
	cout << j <<endl;
	return 0;
}