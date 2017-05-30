//Player header file,used for function prototypes

#ifndef __player_h_
#define __player_h_
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;
class Player {
public:
	Player(string fname,string lname);
	//ACCESSORS
	void setfname(string firstname);
	void setlname(string lastname);
	//GETTING THE PLAYER'S NAME
	string getfname();
	string getlname();
	//GETTING THE PLAYERS STAT
	int getGamesWon();
	int getGamesLost();
	int getMatchesWon();
	int getMatchesLost();
	int getGamesPlayedTotal();
	int getMatchesPlayedTotal();
	//ADDING TO A PLAYER'S STAT
	void addGameWin(int win);
	void addGameLost(int loss);
	void addMatchLost(int loss);
	void addMatchWin(int win);

private: // REPRESENTATION
	//FIRST/LAST NAME
	string fname;
	string lname;
	//WIN/LOSS VARIABLES
	int matcheswon;
	int matcheslost;
	int gameslost;
	int gameswon;
	//TOTAL GAMES/MATCHES PLAYED
	int totalmatchesplayed;
	int totalgamesplayed;
};
double getGameWinPercentage(Player &p1);
double getMatchWinPercentage(Player &p1);
void addGameStats(Player &p1,vector<string> match);
bool NameSort(Player p1,Player p2);
bool CompareGameWins(Player p1,Player p2);
bool CompareMatchWins(Player p1,Player p2);
bool CompareTotalGamesPlayed(Player p1,Player p2);
#endif
