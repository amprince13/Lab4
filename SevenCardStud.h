#pragma once
#ifndef SEVENCARDSTUD_H
#define SEVENCARDSTUD_H
#include "stdafx.h"
//#include "IntermediateGame.h"

#include "Game.h"
#include "Player.h"
#include <string>

class SevenCardStud : public Game {

public:
	SevenCardStud();
	//virtual int first_turn();
	//virtual int other_turns();
	virtual int before_turn(Player &p);
	virtual int turn(Player &p);
	virtual int after_turn(Player &p);
	//void dealeachturn(int numcards);

	virtual int before_round();
	virtual int round();
	virtual int after_round();

	//void print(unsigned int yourpos);
	//void checkPlayerChips();
	unsigned int pot;
	unsigned int currentBet;
	int bettingRound();

protected:
	size_t dealer;
	Deck discardDeck;
	unsigned int currentRound;
	int removePlayers(vector<shared_ptr<Player>> & players, string target);
	int addNewPlayers(string target);
	void discardAllCards(vector<shared_ptr<Player >> &players);
	Hand returnBestCombination(Player &p);
};
unsigned int bet(Player &p, SevenCardStud &g);
void printNoHiddenCards(Player &p);
void printWithHiddenCards(Player &p);
void printAllPlayers(vector<shared_ptr<Player>> copy);



#endif

//pot with unsigned int
//add ante to run through everythig
//betting phase after each turn