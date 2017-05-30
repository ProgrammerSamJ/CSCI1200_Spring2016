//Player.cpp file,where we build the functions
#include <algorithm>
#include "player.h"
#include <iostream>
#include <string>
#include <sstream>
#include <cstring>
#include <cstdlib>
#include <iomanip>
using namespace std;
//CONSTRUCTOR
Player::Player(string firstname,string lastname) {//constructors for the class will be first and last name
	setfname(firstname); //setting first and last name for the class
	setlname(lastname);
	matcheswon = 0;
	matcheslost = 0;
	gameslost = 0;
	gameswon = 0;
	totalmatchesplayed = matcheswon + matcheslost;
	totalgamesplayed = gameswon + gameslost;
}
//setting the first name
void Player::setfname(string firstname) {
	fname = firstname;
}
//setting the last name
void Player::setlname(string lastname) {
	lname = lastname;
}
// //getting the first name
string Player::getfname() {
	return fname;
}
// //getting the last name
string Player::getlname() {
	return lname;
}
//getting games won
int Player::getGamesWon(){
	return gameswon;
}
//getting games lost
int Player::getGamesLost(){
	return gameslost;
}
//getting matches won
int Player::getMatchesWon(){
	return matcheswon;
}
//getting matches lost
int Player::getMatchesLost(){
	return matcheslost;
}
//getting the total number of games played
int Player::getGamesPlayedTotal(){
	return totalgamesplayed;
}
//getting the total number of matches played
int Player::getMatchesPlayedTotal(){
	return totalmatchesplayed;
}
// add a game win
void Player::addGameWin(int win) {
	gameswon +=win;
}
//add a game loss
void Player::addGameLost(int loss){
	gameslost +=loss;
}
//add a match win
void Player::addMatchWin(int win){
	matcheswon +=win;
}
//add a match loss
void Player::addMatchLost(int loss){
	matcheslost +=loss;
}


//Non Memeber Functions
//calculating game win percentage
double getGameWinPercentage(Player &p1){
	double gamewinpercentage;
	gamewinpercentage = (double(p1.getGamesWon())/(p1.getGamesWon() + p1.getGamesLost()));
	return gamewinpercentage;
}
//chalculating match win percentage
double getMatchWinPercentage(Player &p1){
	double matchwinpercentage;
	matchwinpercentage = (double(p1.getMatchesWon())/(p1.getMatchesWon() + p1.getMatchesLost()));
	return matchwinpercentage;
}

//sorting by last name
bool NameSort(Player p1,Player p2) {
	if (p1.getlname() == p2.getlname())
		return p1.getfname() < p2.getfname();
	else if (p1.getlname() > p2.getlname())
		return false;
	else 
		return true;
}
//sorting by match win percentage
bool CompareGameWins(Player p1,Player p2) {
	if (getGameWinPercentage(p1) < getGameWinPercentage(p2))
		return false;
	else if (getGameWinPercentage(p1) == getGameWinPercentage(p2))
		return NameSort(p1,p2);
	else 
		return true;
}
//sorting by game win percentage
bool CompareMatchWins(Player p1,Player p2) {
	if (getMatchWinPercentage(p1) < getMatchWinPercentage(p2))
		return false;
	else if (getMatchWinPercentage(p1) == getMatchWinPercentage(p2))
		return NameSort(p1,p2);
	else 
		return true;
}
//Comparison to see who has played the most games
bool CompareTotalGamesPlayed(Player p1,Player p2) {
	if ((p1.getGamesWon()+p1.getGamesLost()) < (p2.getGamesWon()+p2.getGamesLost()))
		return false;
	else if ((p1.getGamesWon()+p1.getGamesLost()) == (p2.getGamesWon()+p2.getGamesLost()))
		return NameSort(p1,p2);
	else 
		return true;
}
//Adding to the stats of 2 players
void addGameStats(Player &p1,vector<string> match) { //parameters are 2 player objects and a vector of lines from the file
	for (int i=0;i<match.size();i++) {  //looking through each string in the vector (each line in the file)
		vector <int> allgames; //vector made up of all the integers or "games" for each match
		int foundp1Fname; //cheking the line for the position if the first and last name to see if the 
		int foundp1Lname; //player won the match or not
		string temp;
		stringstream matchStream;
		matchStream.str(match[i]);
		// bool findfname= string::npos != (match[i].find(p1.getfname())); //bools to see if both player names are found in the string
		// bool findlname= string::npos != (match[i].find(p1.getlname())); 
		// if (findfname && findlname) { //if both names are found in the line,we have found a match
		// 	foundp1Fname = match[i].find(p1.getfname()); //depending on the names position,we see who won the match 
		// 	foundp1Lname = match[i].find(p1.getlname());
		// 	for(int j=0;j<match[i].size();j++) { //2nd loop through the string (a line in a file)
		// 		if (isdigit(match[i][j])) { //if we find the striing is a digit,
		// 			allgames.push_back(atoi(&match[i][j])); //convert it to an integer and add it to the all games vector
		// 		}
		// 	}
		// }
		while (matchStream >> temp) {
			if (temp == p1.getfname())
				foundp1Fname = 0;
			else
				foundp1Fname = 3;
			matchStream>>temp>>temp>>temp>>temp;
			while (matchStream>>temp) {
				int i = temp.find('-');
				int games_won = atoi(temp.substr(0,i).c_str());
				int games_lost = atoi(temp.substr(i+1,temp.size()-i-1).c_str());
				allgames.push_back(games_won);
				allgames.push_back(games_lost); //convert it to an integer and add it to the all games vector
			}
		}

		if (allgames.size() > 0) { //checking to see if we actually did find a match and games were added
			if (foundp1Fname == 0) { //if the position of p1 is lower than p2 in the string,p1 is the match winner
				p1.addMatchWin(1); //p1 recieves a match win,p2 recieves a match loss
				for (int i=0;i < allgames.size();i++) { //since p1's games will always be on the left of "-", and p2's will be on the right,we can aassume that 
					if (i%2 == 0) {			//if the indicie is even,it is p1's games, if it is odd,it is a loss for the player
						p1.addGameWin(allgames[i]); 
					}
					else {
						p1.addGameLost(allgames[i]);
					}
				}
			}
			else if(match[i].find(p1.getlname()) != string::npos) {
				p1.addMatchLost(1);  //same logic here except p1 is the loser of the match
				for (int i=0;i<allgames.size();i++) {
					if (i%2 == 0) {
						p1.addGameLost(allgames[i]);
					}
					else {
						p1.addGameWin(allgames[i]);
					}
				}
			}
		}
	}
};



