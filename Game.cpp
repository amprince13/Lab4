#include "stdafx.h"
#include "Game.h"
#include "FiveCardDraw.h"
#include "SevenCardStud.h"
string fiveCardDraw = "FIVECARDDRAW";
string sevenCardStud = "SEVENCARDSTUD";

std::shared_ptr<Game> Game::games;

shared_ptr<Game> Game::instance(){
	if (games == NULL) {
		throw instance_not_available;
	}
	else {
		shared_ptr<Game> gamesCopy = games;
		return gamesCopy;
	}
}

void Game::start_game(const string s)
{
	string temp = s;
	transform(temp.begin(), temp.end(), temp.begin(), toupper);

	if (games != NULL) {
		throw game_already_started;
	}
	else if (temp.find(fiveCardDraw) != string::npos) { //if the string does not include "FiveCardDraw"
		games = make_shared<FiveCardDraw>(FiveCardDraw());
	}
	else if (temp.find(sevenCardStud) != string::npos) { //if the string does not include "FiveCardDraw"
		games = make_shared<SevenCardStud>(SevenCardStud());
	}
	else {
		throw unknown_game;
	}

}

/*void Game::start_game(const string s)
{
	if (games != NULL) {
		throw game_already_started;
	}
	else if (s != "FiveCardDraw" && s!= "SevenCardStud") {
		throw unknown_game;
	}
	else {
		if (s == "FiveCardDraw") {
			games = make_shared<FiveCardDraw>(FiveCardDraw());
		}
		else {
			//games = make_shared<SevenCardStud>(SevenCardStud());
		}
	}
}*/

void Game::stop_game()
{
	if (games == NULL) {
		throw no_game_in_progress;
	}
	else {
		games = NULL;
	}
}

shared_ptr<Player> Game::add_player(const string padd)

{
	if (find_player(padd) == 0) {
		//player doesn't exist, sso we add.
		//make a regular pointer first and then the shared pointer off of the regular


		Player * newp2 = new Player(padd);
		shared_ptr<Player> sharedP = shared_ptr<Player>(newp2);
		//newplayer = new Player (padd);
		players.push_back(sharedP);
		return sharedP;
	}
	else {
		//they do exist, throw an exception
		//make enumeration
		throw already_playing;
		//already_playing;
	}
	return shared_ptr<Player>();
}

shared_ptr<Player> Game::find_player(const string pfind)
{
	for (unsigned int i = 0; i < players.size(); i++) {
		//might need string compare
		if ((*players[i]).playerName == pfind) {
			return players[i];
		}
	}
	//address for any singular pointer
	return 0;

}

bool Game::rank_player_hands(shared_ptr<Player> p1, shared_ptr<Player> p2) {
	if (p1 == NULL) {
		return false;
	}
	if (p2 == NULL){
		return true;
	}
	if (!(*p1).isAlive) {
		return false;
	}
	if (!(*p2).isAlive) {
		return true;
	}
	Player p1o = *p1;
	Player p2o = *p2;
	return poker_rank(p1o.playerHand, p2o.playerHand);
}

unsigned int Game::numPlayers(){
	return players.size();
}

Game::~Game() {
	//cout << "Game has been deleted " << endl;
}
