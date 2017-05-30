#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>
#include <stdio.h>     
#include <stdlib.h>
#include <algorithm>
#include <time.h>

//Code for checking run time
//clock_t t1,t2;
// t1=clock();
// //code goes here
// t2=clock();
// float diff ((float)t2-(float)t1);
// float seconds = diff / CLOCKS_PER_SEC;
// cout<<seconds<<endl;
// system ("pause");

//function for the extra credit,finds which DNA string of length k appears the most 
void most_common_sequence(const std::map<std::string,std::vector<int> > &genome,int k){
	std::string most_common1;				  //string to hold the sequence that appears the most
	unsigned int max = 0;					  //int to hold the number of appearances of the sequence
	for(std::map< std::string,std::vector<int> >::iterator it = genome.begin();it != genome.end();it++){
		if(it->second.size() > max){		  //if the size of the sequences's vector(vector if indicies) is greater than the mac
			most_common1 = it->first;		  //the current sequence is the most frequent
			max = it->second.size();		  //the maximum number of appearances is now the current sequences
		}
	}
	std::cout<< "Most frequent sequence: " << most_common1 <<std::endl;
}

//function for the extra credit,finds which DNA string of length k appears the most(custom for vector)
void most_common_sequence2(const std::vector<std::string> &genome2,int k){
	std::string most_common2;				  //string to hold the sequence that appears the most
	unsigned int max = 0;					  //int to hold the number of appearances of the sequenceunsigned int max = 0;
	for(int i=0;i < genome2.size();i++){
		int mycount = std::count(genome2.begin(), genome2.end(), genome2[i]); //counting the number of times the sequence appears
		if(mycount > max){					  //if the number of appearances is greater than the max
			most_common2 = genome2[i];		  //the current sequence is the most frequent
			max = mycount;					  //the maximum number of appearances is now the current sequences
		}
	}
	std::cout<< "Most frequent sequence: " << most_common2 <<std::endl;
}

//Function to store entire genome sequence into a map 
void create_data_structure(const std::string &entireGenome,unsigned int k,const std::map<std::string,std::vector<int> > &genome){
   std::string temp;								 //temporary string to hold a substring of the genome
   //building the map 
   for(unsigned int i=0;i < entireGenome.size();i++){//going through every character in the genome
   	    std::vector<int> v;	 						 //holds the indicies of each char in the genome	
   	    temp = entireGenome.substr(i,k);			 //splitting the string
	   	int x = genome.count(temp);				  	 //checking to see if the key is already part of the map
	    if(x != 0)									 //if the key is already in the map
	    	genome[temp].push_back(i);				 //add the index to the map's key's vector of indexs
	   	else{
	   		v.push_back(i);						  //if the key isnt in the map,add it to the map/add the index to the vector
	    	genome.insert(std::make_pair(temp,v));//store the information,DNA sequence = key,vector of indicies= value
			temp = "";							  //reset the string to start the process over		
		}
	}
}

//Function to store entire genome sequence into a vector
void create_data_structure2(const std::string &entireGenome,unsigned int k,const std::vector<std::string> &genome2){
	std::string temp;								 //temporary string to hold a substring of the genome
   //building the vector(extra credit)
   for(unsigned int i=0;i < entireGenome.size();i++){//going through every character in the genome
   	    temp = entireGenome.substr(i,k);			 //splitting the string
	   	genome2.push_back(temp);					 //add the split string to the genome2 vector
		temp = "";							 		 //reset the string to start the process over		
	}
}

//Function to compare 2 sequences,returns number of mismatches
void compare(std::string query,const std::string &entireGenome,const std::vector<int> indexes,unsigned int m){
	bool nodiffs = true;							//boolean flag to see if there were any differences
	for(unsigned int i=0;i < indexes.size();i++){	//O(p),going through the indexes found
		int diffs = 0;								//counter for the number of differences/mismatches between the query and the genome
		std::string compared = entireGenome.substr(indexes[i],query.size()); //substring starting at index
		//std::cout << indexes[i] <<std::endl;
		for(unsigned int j=0;j < query.size();j++){//O(q)
			if(query[j] != compared[j]){     //if the sequence and query characters are different,there is one mismatch
				diffs++;					 //increase the number of mismatches by one
			}						 
		}
		if (diffs <= m){					//if the number of mismatches found is less than the allowed number of mismatches,print this
			std::cout << indexes[i] << ' ' << diffs << ' ' << compared <<std::endl;
			nodiffs = false;				//there has been a significant difference,so nodiffs is true
		}
	}
	 if(nodiffs == true)				    //if there arre no ignificant differences,we have no matches
	 	std::cout<< "No Match" <<std::endl;
}
//Function to compare 2 sequences,returns number of mismatches(custom for vector)
void compare2(std::string query,const std::string &entireGenome,const std::vector<int> indicies,unsigned int m){
	bool nodiffs = true;							//boolean flag to see if there were any differences
	for(unsigned int i=0;i < indicies.size();i++){	//going through the indexes found
		int diffs = 0;								//counter for the number of differences/mismatches between the query and the genome
		std::string compared = entireGenome.substr(indicies[i],query.size()); //substring starting at index
		//std::cout << indexes[i] <<std::endl;
		for(unsigned int j=0;j < query.size();j++){
			if(query[j] != compared[j]){     //if the sequence and query characters are different,there is one mismatch
				diffs++;					 //increase the number of mismatches by one
			}						 
		}
		if (diffs <= m){					//if the number of mismatches found is less than the allowed number of mismatches,print this
			std::cout << indicies[i] << ' ' << diffs << ' ' << compared <<std::endl;
			nodiffs = false;				//there has been a significant difference,so nodiffs is true
		}
	}
	 if(nodiffs == true)				    //if there arre no ignificant differences,we have no matches
	 	std::cout<< "No Match" <<std::endl;
}

//Function to find the query in the genome
void find_matches(const std::map <std::string, std::vector<int> > &genome,const std::string &entireGenome,
	std::string query,int k,unsigned int m){

	std::cout << "Query: " << query <<std::endl;
	std::string fragment = query;			   	 //string to hold a shotened query in case it is larger than k
	if (query.size() > k){					     //if the query is too long,cut it down so it can be compared to the keys
		fragment = query.substr(0, k);//O(k)
	}
	int x =genome.count(fragment);//O(log p)	 //looking for the query in the map
	if (x == 1){
		compare(query,entireGenome,genome[fragment],m);//O(p*q) //compare the query to the entire genome
	}
	else										 //if we can't find the query at all,there is no match
		std::cout<< "No Match" <<std::endl;
}

//Function to find the query in the genome(custom for vector)
void find_matches2(const std::vector<std::string> &genome2,const std::string &entireGenome,
	std::string query,int k,unsigned int m){

	std::cout << "Query: " << query <<std::endl;
	std::string fragment = query;			   	 //string to hold a shotened query in case it is larger than k
	std::vector<int> indicies;					 //vector to hold the indexes
	if (query.size() > k){//O(1)			     //if the query is too long,cut it down so it can be compared to the keys
		fragment = query.substr(0, k);//O(k)
	}
	for(int i=0;i < genome2.size();i++){//O(p)
		if(fragment == genome2[i])
			indicies.push_back(i);
	}
	if(indicies.size() > 0){
		compare2(query,entireGenome,indicies,m); //compare the query to the entire genome
	}
	else										 //if we can't find the query at all,there is no match
		std::cout<< "No Match" <<std::endl;
}

int main() {
	std::string command;			//temporary string to hold commands	
	int k = 0;						//int to the hold the 'k' integer
	int m = 0;						//int to the hold the numer of mismatches permitted during comparisons
	std::string query;				//holding the sequence the users wants to find in the genome sequence
	std::string entireGenome;		//storing the entire genome in a string,it will be converted into a vector and map
									//with the create data structure function
	std::map<std::string, std::vector<int> > genome;   //map to store each sequence as a key and its DNA positions
	std::vector<std::string> genome2;	 //store each string created from the create data structure function

	while(std::cin >> command){			 //until the user enters "quit",we will keep acting off the user's commands
		if (command == "quit")
			break;
		if (command == "genome"){
			std::cin >> command;
			std::ifstream in_str(command.c_str());//opening genome file 
			std::string line;			  //temporary string to hold each line in the file
			while (in_str >> line) {
    			entireGenome+=line;		  //adding each character from the file to create the entiregenome string 
    		}
    		in_str.close();
		}
		if (command == "kmer"){
			std::cin >> command;
			k = atoi(command.c_str());				          //getting the k value 
			create_data_structure(entireGenome,k,genome);	  //creating a map for the genome
			//create_data_structure2(entireGenome,k,genome2); //creating a vector for the genome
			//most_common_sequence(genome,k);				  //finding and outputting the most common sequence in the map
			//most_common_sequence2(genome2,k);				  //finding and outputting the most common sequence in the vector
		}
		if (command == "query"){
			std::cin >> command;
			m = atoi(command.c_str());    //getting the maximum permitted number of mismatches
			std::cin >> command;
			query = command;			  //pulling the query from the file
			find_matches(genome,entireGenome,query,k,m);	 //finding the seed in the map/comparing query to the entire genome
			//find_matches2(genome2,entireGenome,query,k,m); //finding the seed in the vector/comparing query to the entire genome
		}		
		if (command == "most"){
			most_common_sequence(genome,k);				  //finding and outputting the most common sequence in the map
			most_common_sequence2(genome2,k);			  //finding and outputting the most common sequence in the vector
		}
	}
return 0;
}