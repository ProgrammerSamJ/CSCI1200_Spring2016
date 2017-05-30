#include "player.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iomanip>
using namespace std;



//Preventing objects from being created twice
bool double_check(vector <Player> Players,Player p1) {
	for (int i = 0;i<Players.size();i++) {  //looping through [layer objects to check if they have already been created or not]
		if ((Players[i].getfname() == p1.getfname()) && (Players[i].getlname() == p1.getlname())) { //if the player we are looking at has the same
			//first and last name as one in the vector, then theat player has been created
			return true;
		}
	}
	return false;
}


//Parsing the file
vector <string> parsefile(char** &argv,string call) { //"call" string will let the function know to return names vector or matches vector
	ifstream input_file (argv[1]);//opening the file
	string line; //each line in the file will be a string
	vector <string> names;  //A string vector made up of all the strings in the file
	vector <string> matches;
	if (call == "names") {
		while (input_file >> line) { //inputing each line in the file to the string "line"
			if (line != "d." && !isdigit(line[0])) { //with this condition,all the names are pulled from the file and added to the vector
				names.push_back(line); //adding each piece name to a vector
			}
		}
		return names;
	}
	else {
		int counter = 0;
		while (getline(input_file,line)) { //inputing each line in the file to the string "line"
			matches.push_back(line);
		}
		return matches;
	}
}

//Find Longest Name
int LongestName(vector <Player> &Players) { //checking to see the longest name in the file for formatting
	int LongestNameSize = 0;
	for (int i=0;i<Players.size();i++){
		int lengthFname = (Players[i].getfname()).size();
		int lengthLname = (Players[i].getlname()).size();
		int totalLength = lengthFname + lengthLname + 1;
		if ( totalLength > LongestNameSize) { //if the current players first and last name are the lomgest,make them the longest name
			LongestNameSize = totalLength;
		}
	}return LongestNameSize;
}
//Creating each object and adding it to a vector
vector <Player> ObjectCreator(vector <string> &AllNames){ //Will create objects based on the names taken from the file
	vector <Player> players;  //the vector of objects that will be returned
	for (int i=0;i<AllNames.size();i+=2) { //Adding each player object to the vector "Players"
		Player TempPlayer = Player(AllNames[i],AllNames[i+1]); //creating the player object with a first and last name
		if (!double_check(players,TempPlayer)) { //checking to see if the player has already been created
			players.push_back(TempPlayer);
		}
	}
	return players;
}


int main(int argc,char* argv[]) {
	//ERROR CHECKING
	if (argc < 3) { //checking the number of arguments
		cerr << "Not enough Arguments." << endl;
	}
	if (argc != 3) {
		cerr << "Usage:\n " << argv[0] << " infile-sample_scores.txt\n";
		return 1;
	}
	ifstream in_str(argv[1]);
	if (!in_str) { //checking if the file can be opened
		cerr << "Could not open " << argv[1] << " to read\n";
		return 1;
	}
	ofstream out_str(argv[2]);
	if (!out_str) { //checking if the out file can be opened
		cerr << "Could not open " << argv[2] << " to write\n";
		return 1;
	}

	string name="names"; //will be used in parse to return a name vector or match vector
	string match="match";
	vector <string> AllNames = parsefile(argv,name); //calling the parse function to get all names
	vector <string> Matches = parsefile(argv,match); //calling the parse function to get all the matches
	vector <Player> Players = ObjectCreator(AllNames); //calling the objectcreator,will return a vector made up of player objects
	int MaxLength = LongestName(Players);

	//CHANGING ALL PLAYER STATS
	for (int i=0;i<Players.size();i++) { //using the info from the file to add stats to each player
		addGameStats(Players[i],Matches);
	}

	//integers are right justified in a field of width 5. The percentages are right justified in a field of width 13
	//set precision is 3
	//Writing the Win percentage to each file wins/totalgames
	ofstream output_file;
	output_file.open(argv[2]);
	output_file << "MATCH STATISTICS" <<endl;
	sort(Players.begin(),Players.end(),CompareMatchWins);

	output_file << setw(MaxLength+4) << left << "Player" <<setw(2) << "W" << right << setw(4)<< right <<"L" << setw(13) << "percentage" <<endl;

	for (int i=0;i<Players.size();i++) {
    	output_file<< setw(MaxLength) << left << Players[i].getfname()+" "+Players[i].getlname()<< setw(5) << right <<
    	Players[i].getMatchesWon()<< setw(5) << right << Players[i].getMatchesLost()<< setw(13) << right << fixed << setprecision(3) << getMatchWinPercentage(Players[i]) <<endl;
	}
	output_file << "\n";
	// //Writing the Match percentage to each file matchwins/totalmatches
	output_file << "GAME STATISTICS" <<endl;
	sort(Players.begin(),Players.end(),CompareGameWins);
	output_file << setw(MaxLength+4) << left << "Player" <<setw(2) << "W" << right << setw(4)<< right <<"L" << setw(13) << "percentage" <<endl;
	for (int i=0;i<Players.size();i++) {
    	output_file<< setw(MaxLength) << left << Players[i].getfname()+" "+Players[i].getlname()<< setw(5) << right <<
    	Players[i].getGamesWon()<< setw(5) << right << Players[i].getGamesLost()<< setw(13) << right << fixed << setprecision(3) << getGameWinPercentage(Players[i]) <<endl;
	}
	output_file << "\n";

	// //Writing the Total Games Played Comparison to the file
	output_file << "TOTAL GAMES PLAYED" <<endl;
	sort(Players.begin(),Players.end(),CompareTotalGamesPlayed);
	output_file << setw(MaxLength+4) << left << "Player" <<setw(2) << "W" << right << setw(4)<< right <<"L" << setw(13) << "total games" <<endl;
	for (int i=0;i<Players.size();i++) {
    	output_file<< setw(MaxLength) << left << Players[i].getfname()+" "+Players[i].getlname()<< setw(5) << right <<
    	Players[i].getGamesWon()<< setw(5) << right << Players[i].getGamesLost()<< setw(13) << right << fixed << setprecision(3) << (Players[i].getGamesWon()+Players[i].getGamesLost()) <<endl;
    }
	return 0;
}
