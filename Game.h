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
using namespace std;
enum game_errors {instance_not_available = 8, game_already_started, unknown_game, no_game_in_progress, already_playing};

class SevenCardStud;
class Game {
	friend unsigned int bet(Player &p, SevenCardStud &g);
public:
	Game() = default;
	~Game();
	//how to define instance not available
	static shared_ptr<Game> instance();
	static void start_game(const string);
	static void stop_game();
	shared_ptr<Player> add_player(const string);
	shared_ptr<Player> find_player(const string);
	static bool rank_player_hands(shared_ptr<Player> p1, shared_ptr<Player> p2);
	virtual int before_turn(Player &p) = 0;
	virtual int turn(Player &p) = 0;
	virtual int after_turn(Player &p) = 0;
	virtual int before_round() = 0;
	virtual int round() = 0;
	virtual int after_round() = 0;
	unsigned int numPlayers();

protected:
	static std::shared_ptr<Game> games;
	Deck mainDeck;
	std::vector<shared_ptr<Player>> players;



};