#include "stdafx.h"
#include "Player.h"
#include <fstream>
#include <sstream>
 

Player::Player(string input)
	:handsWon(0), handsLost(0), chips(20), lastBet(0), playerHand()
{
	isAlive = true;
	playerName = input;
	ifstream ifs;
	ifs.open(input + ".txt");
	int counter = 0;
	if (ifs.is_open()) {
		string line, word;
		
		while (getline(ifs, line)) {
			istringstream iss(line);
			if (iss >> word) {	// player information is stored line by line
				if (counter == 0) {// first line is name
					playerName = word;
				}
				if (counter == 1) {// second line is wins
					handsWon = std::stoi(word);
				}
				if (counter == 2) { // third line is loses
					handsLost = std::stoi(word);
				}
				if (counter == 3) {
					chips = std::stoi(word);
				}
				counter++;
			}

		}
		if (counter < 4) { // if there wasn't full data, reset both to zero
			handsWon = 0;
			handsLost = 0;
			chips = 20;
		}
	}

}
	


ostream &operator <<(ostream &out, const Player &p) {	// print name, wins, and loses all on seperate lines
	out << p.playerName << "\n" << p.handsWon << "\n" << p.handsLost << "\n" << p.chips << std::endl;
	return out;
}

