#pragma once
#pragma once
#include "stdafx.h"
#include <string>
#include <vector>
using namespace std;
enum Suit { Clubs, Diamonds, Hearts, Spades };
enum Rank { Two, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack, Queen, King, Ace };

extern const char validRanks[];
extern const char validSuits[];

struct Card {
	Suit suit_;
	Rank rank_;
	Card(Suit s, Rank r) {
		suit_ = s;
		rank_ = r;
	}
	Card() {

	}
	bool operator< (const Card &) const;
	bool operator!= (const Card &) const;
	bool operator== (const Card &) const;

};


string printCard(Card c);
bool validateCardString(string s);
Card generateCardFromString(string s);
int printDeck(const vector<Card> &v, bool newLine);
int printHands(const vector<Card> &v);
int analyzeHand(const vector<Card> &h);