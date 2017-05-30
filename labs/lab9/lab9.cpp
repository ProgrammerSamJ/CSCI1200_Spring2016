#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>
#include <stdio.h>     
#include <stdlib.h>

void print_mode(std::map< std::string,int > &newmap){
	int max = 0;
	for(std::map< std::string,int >::iterator it = newmap.begin();it != newmap.end();it++){
		if(it->second > max){
			max = it-> second;
		}
	}
	for(std::map< std::string,int >::iterator it = newmap.begin();it != newmap.end();it++){
		if(it->second == max){
			std::cout << "number: "<< it->first << " value: " << it->second <<std::endl;
		}
	}
}

int main(int argv,char* argc[]){
	//Check 1
	std::cout << "Check 1 Output:\n";
	std::map< std::string,int > newmap;
	std::ifstream file(argc[1]);
	std::string line;
	while(file >> line){
		++newmap[line];				
	}
	print_mode(newmap);

	//Check 2
	std::cout << "Check 2 Output:\n";
	while(file >> line){
		std::map<std::string,int>::iterator it = newmap.find(line);
		if(it == newmap.end())
			newmap.insert(std::make_pair(line,1));
		else
			it->second += 1;
	}
	print_mode(newmap);
	return 0;
}