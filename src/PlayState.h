#ifndef PLAYSTATE_H
#define PLAYSTATE_H

#include "GameState.h"
#include <vector>
#include <string>


class Player;
class Card;
class GUI;
class AI;

class PlayState : public GameState
{
public:
	PlayState(TextureManager* game_textures, GLBL::signal signal);
	~PlayState();
	virtual void update(GameEngine* game);
	virtual void handleEvents();
	virtual void render();

	Player* get_curr_player()
	{
		return curr_player;
	}
	Player* get_curr_enemy()
	{
		if (left_player == curr_player)
			return right_player;
		else return left_player;
	}
private:
	virtual bool loadTextures();
	bool loadDeck();
	bool loadSave();
	bool load_player(std::ifstream & fin, std::string & str);
	bool load_player_cards(std::ifstream& fin, std::string& str);
	bool load_remaining_cards(std::ifstream& fin, std::string& str);
	void makePlayerIcons();
	void makeGameButtons();
	void makeGUIinterface();
	void makeNewPlayers(GLBL::signal signal);
	void changeCurrPlayer();
	void saveGame();
	void savePlayer(std::ofstream & out, Player * player);

	std::vector<Card*> deck;
	std::vector<Card*>::iterator next_card;

	Player* left_player;
	Player* right_player;
	Player* curr_player;
	AI* comp_player;
	GUI* left_player_icon;
	GUI* right_player_icon;
};

#endif 

