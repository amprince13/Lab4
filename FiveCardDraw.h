#pragma once
#include <iostream>
#include <memory>
#include "Deck.h"
#include "Player.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include "Game.h"
using namespace std;

//how to derive public inheritance
class FiveCardDraw : public Game {
public:
	FiveCardDraw();
	virtual int before_turn(Player &p);
	virtual int turn(Player &p);
	virtual int after_turn(Player &p);
	virtual int before_round();
	virtual int round();
	virtual int after_round();
	unsigned int pot;
	unsigned int currentBet;
	int bettingRound();
	
protected:
	size_t dealer;
	Deck discardDeck;
	void discardAllCards(vector<shared_ptr<Player>> & players);
	int removePlayers(vector<shared_ptr<Player>> & players, string target);
	int addNewPlayers(string target);
	

};
void printPlayers(vector<shared_ptr<Player>> player_list);
unsigned int bet(Player &p, FiveCardDraw &g);