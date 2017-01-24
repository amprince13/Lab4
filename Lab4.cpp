// Authors: Austin Prince, Daniel Finn, Ramona Durham
// Contact: amprince@wustl.edu, dmfinn@wustl.edu, r.durham@wustl.edu

// Entry point for the Card games command prompt game

#include "stdafx.h"
#include "FiveCardDraw.h"
#include "SevenCardStud.h"
//#include "SevenCardStud.h"
enum Input_Errors{incorrect_num_params = 13};

int verifyParams(int argc, char* argv[]) {
	if (argc < 4) {
		std::cout << "Usage: " << argv[0] << " GAME_NAME PLAYERS " << std::endl;
		throw incorrect_num_params;
	}
	return 0;
}

int play(string Name, vector<string> players) {
	try {
		Game::start_game(Name);
		std::shared_ptr<Game> game = Game::instance();
		for (unsigned int i = 0; i < players.size(); i++) {
			game->add_player(players[i]);
		}
		int gameState = 0;
		while (game->numPlayers() >= 2 && gameState == 0) {	// while there are still people playing, run the game loop
			gameState = game->before_round();
			gameState = game->round();
			gameState = game->after_round();

		}
		Game::stop_game();
		std::cout << "GAME OVER" << std::endl;
		return gameState;
		
	}
	catch (game_errors &e) {
		return e;
	}

}

void playAgain() {
string response;
while (response != "quit") {
	std::cout << "Would you like to play again? (yes or quit)";
	std::cin >> response;
	if (response == "yes") {
		string name;
		string pnames;
		vector<string> playerNames;
		std::cout << "Enter game name:" << std::endl;
		std::cin >> name;
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		if (name == "FiveCardDraw" || name == "SevenCardStud") {
			std::cout << "Please enter player names space-seperated" << std::endl;
			std::cin >> noskipws;
			std::getline(std::cin, pnames);
			string player;
			istringstream iss(pnames);
			while (iss >> player) {
				playerNames.push_back(player);
			}
			play(name, playerNames);
		}
	}

}
}
int main(int argc, char* argv[])
{

	try {
		verifyParams(argc, argv);	// make sure the inputs to the game are correct
	}
	catch (Input_Errors &e) {

		return e;
	}
	string game_name = argv[1];
	int gameState = 0;
	try {
		// start the game and grap a copy of the pointer to it
		Game::start_game(game_name);
		std::shared_ptr<Game> game = Game::instance();

		for (int i = 2; i < argc; i++) {	// Player names start at pos 2, add all into game
			game->add_player(argv[i]);
		}

		while (game->numPlayers() >= 2 && gameState == 0) {	// while there are still people playing, run the game loop
			gameState = game->before_round();
			gameState = game->round();
			gameState = game->after_round();

		}
	}
	catch (game_errors &e) {	// Catch any exceptions thrown while creating the game, if so stop the game
		std::cout << "caught error game error: " << e << std::endl;
		Game::stop_game();
		return e;
	}
	catch (Error_Codes &e) {	// Catch any exceptions thrown while playing the game, if so stop the game
		std::cout << "Caught error_code mid game: " << e << std::endl;
		Game::stop_game();
		return e;
	}
	Game::stop_game();
	std::cout << "GAME OVER" << std::endl;
	playAgain();

	return 0;
}
	