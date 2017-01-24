#pragma once
#pragma once
#pragma once
#include "stdafx.h"
#include "Card.h"
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
enum Error_Codes { ERROR_OPENING_FILE = 1, TOO_MANY_COMMANDS, NO_SHUFFLE_FLAG, NO_COMMANDS_GIVEN, NO_FILE_NAME, DECK_TOO_SMALL, INVALID_HAND_INDEX };

class Deck {
	friend ostream &operator<<(ostream &out, Deck &g);

public:
	Deck();
	Deck(string fileName);
	void load(string fileName);
	void shuffle();
	int size() const;
	Card getTop();
	void print();
	void add_card(Card &c);
private:
	vector<Card> d;
};
