#pragma once
#include <iostream>
#include <string>
#include "Hand.h"


struct Player {
	Player(string name);
	string playerName;
	Hand playerHand;
	vector<Card> sevenCardHand;
	unsigned int handsLost;
	unsigned int handsWon;
	unsigned int chips;
	unsigned int lastBet;
	bool isAlive;
	

};

ostream &operator <<(ostream &out, const Player &p);