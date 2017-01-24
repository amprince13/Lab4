// Author: Daniel Finn
// Email: dmfinn@wustl.edu
// Contains defintion for Deck playing class, which represents a standard playing deck. Adds associated functions.


#pragma once
#include "stdafx.h"
#include "Card.h"
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include "Deck.h"
#include <fstream>
#include <sstream>
#include <ctime>


Deck::Deck()
{}
Deck::Deck(string fileName)
{
	try {
		load(fileName);
	}
	catch (Error_Codes &e) {
		throw e;
	}

}
void Deck::add_card(Card &c) {
	d.push_back(c);
}

void Deck::load(string filename)
{
	ifstream ifs;
	ifs.open(filename);
	if (!ifs.is_open()) { // check if file could be opened,
		std::cout << "Error Loading input file" << std::endl;
		throw ERROR_OPENING_FILE;
		return;
	}
	string line, word;
	while (getline(ifs, line)) { // while there are available lines, read them
		istringstream iss(line); // get the fisrt line
		while (iss >> word) { // get each 'word', aka card string, from the line
			bool valid = validateCardString(word); // check if the string is valid
			if (valid)
			{
				Card c = generateCardFromString(word); // if it's valid, generate a card from it and add it to the vector
				d.push_back(c);
			}
			// otherwise do nothing
		}
	}

	ifs.close();

}

void Deck::shuffle() {
	srand(unsigned(time(NULL)));
	std::random_shuffle(d.begin(), d.end());
}

int Deck::size() const {
	return d.size();
}

ostream &operator<<(ostream &out, Deck &g) {
	int j = 0;
	int m = g.size();
	while (j < m) {
		out << printCard(g.d[j]) << std::endl;
		j++;
	}
	return out;

}

Card Deck::getTop() {
	Card newCard = d.back();
	d.pop_back();
	return newCard;
}

void Deck::print() {
	std::cout << "\n";
	std::cout << "Printing entire deck: " << std::endl;
	std::cout << "---" << std::endl;
	printDeck(d, false);
	std::cout << "\n";
	std::cout << "---" << std::endl;
}