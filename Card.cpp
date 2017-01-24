

// Card.cpp : Defines playing card struct for use with Lab2DeckHands.cpp
// Author: Daniel Finn dmfinn@wustl.edu
// Creates a simple struct that represents a playing card with a certain suit and rank. Adds associated functions.

#pragma once
#include "stdafx.h"
#include "Card.h"
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>


// arrays of valid characters for ranks and suits
extern const char validRanks[] = { '2', '3', '4', '5', '6', '7', '8', '9','j', 'J', 'q', 'Q', 'k', 'K', 'a', 'A' };
extern const char validSuits[] = { 'c', 'C', 'd', 'D', 'h', 'H', 's', 'S' };

using namespace std;

// compare cards to one another. If rank < c2 rank, return. Otherwise check if the same and return suit comaprison
bool
Card::operator< (const Card & c2) const
{
	return (rank_ < c2.rank_) || ((rank_ == c2.rank_) && (suit_ < c2.suit_));
}

bool Card::operator!= (const Card & c2) const {
	return (rank_ != c2.rank_) && (suit_ != c2.suit_);
}

bool Card::operator== (const Card & c2) const {
	return (rank_ == c2.rank_) && (suit_ == c2.suit_);
}

//simple method to print out a cards information as a string
string printCard(Card c) {
	string suit;
	string rank;
	string output;
	switch (c.suit_)
	{
	case Clubs: suit = "C"; break;
	case Diamonds: suit = "D"; break;
	case Hearts: suit = "H"; break;
	case Spades: suit = "S"; break;
	}
	switch (c.rank_)
	{
	case Two: rank = "2"; break;
	case Three: rank = "3"; break;
	case Four: rank = "4"; break;
	case Five: rank = "5"; break;
	case Six: rank = "6"; break;
	case Seven: rank = "7"; break;
	case Eight: rank = "8"; break;
	case Nine: rank = "9"; break;
	case Ten: rank = "10"; break;
	case Jack: rank = "J"; break;
	case Queen: rank = "Q"; break;
	case King: rank = "K"; break;
	case Ace: rank = "A"; break;

	}

	output = rank + suit;
	return output;
};

// Evaluates a string to see if it is a valid card definition. if it is , it returns true.
bool validateCardString(string s) {
	char rankChar;
	char suitChar;
	if (s.length() > 3 || s.length() < 2) // validate string by length
	{
		return false;
	}

	if (s.length() == 3) // special case for length of 3, when card should have rank 10
	{
		if (s[0] == '1' && s[1] == '0') // validate that card has rank 10
		{
			suitChar = s[2];
			for (int i = 0; i < 8; ++i) { // iterate through array of all 8 valid suits and make sure provided one matches one
				if (suitChar == validSuits[i]) {
					return true;
				}
			}
			return false;
		}
		else return false;

	}
	else //this is a two character card string
	{
		rankChar = s[0];
		suitChar = s[1];
	}

	bool validR = false;
	bool validS = false;;
	int r = rankChar;

	if (r > 58) { // if the integer value of the rank character is > 58 (i.e., not 1 - 10), validate it. 
		rankChar = toupper(rankChar);
		if (rankChar != 'A' && rankChar != 'K' && rankChar != 'Q' && rankChar != 'J') {
			return false;
		}
	}

	for (int i = 0; i < 17; ++i) { // iterate through array of all 17 valid ranks and make sure provided one matches one
		if (rankChar == validRanks[i])
		{
			validR = true;
		}
	}

	// convert all suit chars to upper case for simplicity, compare to known valid 
	suitChar = toupper(suitChar);
	if (suitChar != 'C' && suitChar != 'D' && suitChar != 'S' && suitChar != 'H') {
		return false;
	}

	validS = true; // if the above doesn't return false, 

	if (validR && validS) {
		return true;
	}
	return false;
}

// Generates a card struct from a string pre-validated by validateCardString()
Card generateCardFromString(string s) {
	//THIS METHOD MAY ONLY BE CALLED AFTER THE STRING HAS BEEN VALIDATED WITH validateCardString()!

	Suit suit_;
	Rank rank_;
	char suitChar;
	char rankChar;
	if (s.length() == 3) { // special case, if string length is 3 we know that it is of rank 10 as it's the only valid string of length 3


		suitChar = toupper(s[2]); // make all characters upper case for simplicity
		switch (suitChar)
		{
		case 'C': suit_ = Clubs; break;
		case 'D': suit_ = Diamonds; break;
		case 'S': suit_ = Spades; break;
		case 'H': suit_ = Hearts; break;


		}
		rank_ = Ten;
		return Card(suit_, rank_);

	} // otherwise we have a two character card

	rankChar = toupper(s[0]);
	suitChar = toupper(s[1]);

	switch (rankChar)
	{
	case '2': rank_ = Two; break;
	case '3': rank_ = Three; break;
	case '4': rank_ = Four; break;
	case '5': rank_ = Five; break;
	case '6': rank_ = Six; break;
	case '7': rank_ = Seven; break;
	case '8': rank_ = Eight; break;
	case '9': rank_ = Nine; break;
	case 'J': rank_ = Jack; break;
	case 'Q': rank_ = Queen; break;
	case 'K': rank_ = King; break;
	case 'A': rank_ = Ace; break;
	}
	switch (suitChar)
	{
	case 'C': suit_ = Clubs; break;
	case 'D': suit_ = Diamonds; break;
	case 'S': suit_ = Spades; break;
	case 'H': suit_ = Hearts; break;
	}
	return Card(suit_, rank_);



}

int printDeck(const vector<Card> &v, bool newLine) {
	for (size_t i = 0; i < v.size(); i++) { // call the printcard function on all the cards in c
		string obType = typeid(v[i]).name();
		if (obType != "struct Card") {
			return 5;
		}
		Card c = v[i];
		std::cout << printCard(c) << " ";
		if (newLine) { // checks if the cards should be printed on the same line or individual lines
			std::cout << "\n";
		}
	}
	return 0;

}

int printHands(const vector<Card> &v) {
	vector<Card> h;
	size_t j = 0;
	while (j < v.size()) {
		for (size_t i = j; i < j + 5; i++) {
			h.push_back(v[i]);
		}
		std::sort(h.begin(), h.end());
		printDeck(h, false);
		std::cout << "Rank: " << analyzeHand(h) << std::endl;
		std::cout << "\n" << std::endl;
		h.clear();
		j = j + 5;
	}
	return 0;

}
int analyzeHand(const vector<Card> &h) {

	if (h.size() == 0) {
		return -1;
	}

	if (h.size() != 5) {
		return 7;
	}
	if (!is_sorted(h.begin(), h.end())) {
		return 7;
	}

	//check for straight flush or flush
	if (h[0].suit_ == h[1].suit_ && h[1].suit_ == h[2].suit_ && h[2].suit_ == h[3].suit_ && h[3].suit_ == h[4].suit_) {
		if (h[0].rank_ == h[1].rank_ - 1 && h[1].rank_ == h[2].rank_ - 1 && h[2].rank_ == h[3].rank_ - 1 && h[3].rank_ == h[4].rank_ - 1) {
			return 8;
		}
		return 5;
	}
	//check for straight
	if (h[0].rank_ == h[1].rank_ - 1 && h[1].rank_ == h[2].rank_ - 1 && h[2].rank_ == h[3].rank_ - 1 && h[3].rank_ == h[4].rank_ - 1) {
		return 4;
	}
	// check for 4 of a kind
	if (h[0].rank_ == h[1].rank_ && h[1].rank_ == h[2].rank_&& h[2].rank_ == h[3].rank_) {
		return 7;
	}
	if (h[1].rank_ == h[2].rank_ && h[2].rank_ == h[3].rank_&& h[3].rank_ == h[4].rank_) {
		return 7;
	}

	// check for full house
	if (h[0].rank_ == h[1].rank_ && h[1].rank_ == h[2].rank_) {
		if (h[3].rank_ == h[4].rank_) {
			return 6;
		}
		return 3;
	}

	if (h[2].rank_ == h[3].rank_ && h[3].rank_ == h[4].rank_) {
		if (h[0].rank_ == h[1].rank_) {
			return 6;
		}
		return 3;
	}

	//check for 3 of a kind not covered by full house
	if (h[1].rank_ == h[2].rank_ && h[2].rank_ == h[3].rank_) {
		return 3;
	}

	//check for two pair
	bool tp1 = (h[0].rank_ == h[1].rank_) && (h[2].rank_ == h[3].rank_);
	bool tp2 = (h[0].rank_ == h[1].rank_) && (h[3].rank_ == h[4].rank_);
	bool tp3 = (h[1].rank_ == h[2].rank_) && (h[3].rank_ == h[4].rank_);
	if (tp1 || tp2 || tp3) {
		return 2;
	}
	// check for one pair
	bool p1 = h[0].rank_ == h[1].rank_;
	bool p2 = h[1].rank_ == h[2].rank_;
	bool p3 = h[2].rank_ == h[3].rank_;
	bool p4 = h[3].rank_ == h[4].rank_;
	if (p1 || p2 || p3 || p4) {
		return 1;
	}

	return 0;
}
