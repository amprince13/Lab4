
// Hand.cpp : Defines playing hand class for use with Lab2DeckHands.cpp
// Author: Daniel Finn dmfinn@wustl.edu
// Creates a simple class that represents a poker hand of 5 cards. Adds associated functions.


#include "stdafx.h"
#include "Card.h"
#include "Hand.h"
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

Hand::Hand() {

}

Hand::Hand(const Hand &n) {
	h = n.h;
}

Hand & Hand::operator=(const Hand &n) {
	if (this == &n) {
		return *this;
	}
	h = n.h;
	return *this;
}

int Hand::size() const {
	return h.size();
}

Card Hand::operator[](size_t index) {
	if (index > h.size() - 1) {
		throw INVALID_HAND_INDEX;
	}
	else return h[index];
}

Card Hand::remove_card(size_t index) {
	if (index > h.size() - 1) {
		throw INVALID_HAND_INDEX;
	}
	else {
		Card target = h[index];
		h.erase(h.begin() + index);
		return target;
	}

}

bool Hand::operator==(const Hand &n) const {
	if (h.size() != n.size()) {
		return false;
	}
	for (unsigned int i = 0; i < h.size(); i++) {
		if (h[i] != n.h[i]) {
			return false;
		}
	}
	return true;
}

bool Hand::operator<(const Hand &n) const {
	for (int i = 0; i < 5; i++) {
		Card ours = h[i];
		Card theirs = n.getCardAtPosition(i);
		if (ours.rank_ == theirs.rank_) {

		}
		else if (ours.rank_ < theirs.rank_) {
			return true;
		}
		else return false;
	}
	return false;
}

string Hand::toString() {
	string output = "";
	for (unsigned int i = 0; i < h.size(); i++) {
		output += printCard(h[i]) + " ";
	}
	return output;

}

ostream &operator<<(ostream &out, Hand &h) {
	out << h.toString();
	return out;
}

Hand &operator<<(Hand &h, Deck &d) {
	Card newCard = d.getTop();
	h.h.push_back(newCard);
	std::sort(h.h.begin(), h.h.end());
	return h;
}

int operator<<(Hand &h, Card &c) {
	h.h.push_back(c);
	return 0;
}

Card Hand::getCardAtPosition(unsigned int n) const {
	if (n > h.size() - 1) {
		int i = 6;
		throw i;
	}
	Card target = h[n];
	return target;
}

int Hand::getRank() const {
	return analyzeHand(h);

}


bool poker_rank(Hand h1, Hand h2) {
	handRank h1r = (handRank)(h1.getRank());
	handRank h2r = (handRank)(h2.getRank());
	if (h1r == h2r) {
		switch (h1r) {
		case 0:
			// This is high Card
			// Compare Cards one by one
			for (int i = 4; i >= 0; i--) {
				if (h1.getCardAtPosition(i).rank_ == h2.getCardAtPosition(i).rank_) {

				}
				else return h2.getCardAtPosition(i).rank_ < h1.getCardAtPosition(i).rank_;
			}
			return false;
			break;
		case 1:
		{
			// This is one pair
			// Organize pair at front, compare pairs, then compare
			Card h1_best_pair = organizeOnePair(h1);
			Card h2_best_pair = organizeOnePair(h2);
			if (h1_best_pair.rank_ != h2_best_pair.rank_) {
				return h2_best_pair < h1_best_pair;
			}
			else {
				for (int i = 4; i >= 0; i--) {
					if (h2.getCardAtPosition(i).rank_ != h1.getCardAtPosition(i).rank_) {
						return h2.getCardAtPosition(i).rank_ < h1.getCardAtPosition(i).rank_;
					}
				}
			}
			return false;
			break;
		}

		case 2:
		{
			// Two Pair -> get locatins of high pair card, low pair card, outlier
			vector<int> h1_poss = twoPairLocation(h1);
			vector<int> h2_poss = twoPairLocation(h2);
			Card h1_high = h1.getCardAtPosition(h1_poss[0]);
			Card h2_high = h2.getCardAtPosition(h2_poss[0]);
			Card h1_low = h1.getCardAtPosition(h1_poss[1]);
			Card h2_low = h2.getCardAtPosition(h2_poss[1]);
			Card h1_out = h1.getCardAtPosition(h1_poss[2]);
			Card h2_out = h2.getCardAtPosition(h2_poss[2]);
			if (h1_high.rank_ != h2_high.rank_) {
				return h2_high < h1_high;
			}
			if (h1_low.rank_ != h2_low.rank_) {
				return h2_low < h1_low;
			}

			return h2_out < h1_out;
			break;
		}

		case 3:
		{
			// Three of a kind -> get rank of three of kind, compare
			Card h1_pair = getThreePairRank(h1);
			Card h2_pair = getThreePairRank(h2);
			return h2_pair < h1_pair;
			break;
		}
		case 4:
		{
			// Straight, simply compare highest card
			return h2.getCardAtPosition(4).rank_ < h1.getCardAtPosition(4).rank_;
			break;
		}
		case 5:
		{
			//Flush, compare down the line
			for (int i = 4; i >= 0; i--) {
				if (h1.getCardAtPosition(i).rank_ == h2.getCardAtPosition(i).rank_) {

				}
				else return h2.getCardAtPosition(i).rank_ < h1.getCardAtPosition(i).rank_;
			}
			return false;
			break;
		}
		case 6:
		{
			// Full house, compare three pair cards and then compare two pair cards
			// Get rank of 3 pair
			Card h1_three_pair;
			Card h1_two_pair;
			Card h2_three_pair;
			Card h2_two_pair;
			if (h1.getCardAtPosition(1).rank_ == h1.getCardAtPosition(2).rank_) {
				// [] [X] [X] [] [] three pair cards at location 0, 1, 2
				h1_three_pair = h1.getCardAtPosition(2);
				h1_two_pair = h1.getCardAtPosition(4);
			}
			else h1_three_pair = h1.getCardAtPosition(4); h1_two_pair = h1.getCardAtPosition(1); // otherwise the three pair are in 2,3,4
			if (h2.getCardAtPosition(1).rank_ == h2.getCardAtPosition(2).rank_) {
				// [] [X] [X] [] [] three pair cards at location 0, 1, 2
				h2_three_pair = h2.getCardAtPosition(2);
				h2_two_pair = h2.getCardAtPosition(4);
			}
			else h2_three_pair = h2.getCardAtPosition(4); h2_two_pair = h2.getCardAtPosition(1); // otherwise the three pair are in 2,3,4
			if (h1_three_pair != h2_three_pair) {
				return h2_three_pair < h1_three_pair;
			}
			return h2_two_pair < h1_two_pair;
			break;
		}
		case 7:
		{
			//Four of a kind, just figure out what the rank of the four cards are and compare
			Card h1_four_pair;
			Card h2_four_pair;
			if (h1.getCardAtPosition(0).rank_ != h1.getCardAtPosition(1).rank_) h1_four_pair = h1.getCardAtPosition(4); // [O][X][][][] pairs 1,2,3,4
			else h1_four_pair = h1.getCardAtPosition(3); // [x][x][][][] pairs 0, 1, 2, 3

			if (h2.getCardAtPosition(0).rank_ != h2.getCardAtPosition(1).rank_) h2_four_pair = h2.getCardAtPosition(4); // [O][X][][][] pairs 1,2,3,4
			else h2_four_pair = h2.getCardAtPosition(3); // [x][x][][][] pairs 0, 1, 2, 3

			return h2_four_pair < h1_four_pair;
			break;
		}
		case 8:
		{
			// straight flush, sort by highest card
			return h2.getCardAtPosition(4).rank_ < h1.getCardAtPosition(4).rank_;

		}

		}
	}
	return h1r > h2r;

}

Card organizeOnePair(const Hand &h1) {
	//Declare our new cards
	Card pair1;
	Card pair2;
	//Find pair cards in h1
	if (h1.getCardAtPosition(0).rank_ == h1.getCardAtPosition(1).rank_) {
		pair1 = h1.getCardAtPosition(0);
		pair2 = h1.getCardAtPosition(1);
	}
	if (h1.getCardAtPosition(1).rank_ == h1.getCardAtPosition(2).rank_) {
		pair1 = h1.getCardAtPosition(1);
		pair2 = h1.getCardAtPosition(2);
	}
	if (h1.getCardAtPosition(2).rank_ == h1.getCardAtPosition(3).rank_) {
		pair1 = h1.getCardAtPosition(2);
		pair2 = h1.getCardAtPosition(3);
	}
	if (h1.getCardAtPosition(3).rank_ == h1.getCardAtPosition(4).rank_) {
		pair1 = h1.getCardAtPosition(3);
		pair2 = h1.getCardAtPosition(4);
	}
	// Now push the remainder of the cards back
	if (pair2 < pair1) {
		return pair1;
	}
	return pair2;


}

vector<int> twoPairLocation(const Hand &h) { // Returns vector of cards where v[0] = high pair pos, v[1] = low pair, v[2] = outlier
	vector<int> positions;
	bool tp1 = (h.getCardAtPosition(0).rank_ == h.getCardAtPosition(1).rank_) && (h.getCardAtPosition(2).rank_ == h.getCardAtPosition(3).rank_);
	bool tp2 = (h.getCardAtPosition(0).rank_ == h.getCardAtPosition(1).rank_) && (h.getCardAtPosition(3).rank_ == h.getCardAtPosition(4).rank_);
	bool tp3 = (h.getCardAtPosition(1).rank_ == h.getCardAtPosition(2).rank_) && (h.getCardAtPosition(3).rank_ == h.getCardAtPosition(4).rank_);
	if (tp1) {
		positions.push_back(3);	// location of highest pair card
		positions.push_back(1); // location of lowest pair card
		positions.push_back(4); // location of outlier
	}
	if (tp2) {
		positions.push_back(4);	// location of highest pair card
		positions.push_back(1); // location of lowest pair card
		positions.push_back(2); // location of outlier
	}
	if (tp3) {
		positions.push_back(4);	// location of highest pair card
		positions.push_back(2); // location of lowest pair card
		positions.push_back(0); // location of outlier
	}

	return positions;

}

Card getThreePairRank(const Hand &h) {
	Card pairCard;
	if (h.getCardAtPosition(0).rank_ == h.getCardAtPosition(1).rank_) {
		pairCard = h.getCardAtPosition(2);
	}
	if (h.getCardAtPosition(3).rank_ == h.getCardAtPosition(4).rank_) {
		pairCard = h.getCardAtPosition(4);
	}
	else pairCard = h.getCardAtPosition(3);

	return pairCard;
}