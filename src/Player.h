#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <map>
#include <string>
#include "GLBL.h"

class Card;
class UI_text;
class TextureManager;
class GUI;

class Player
{
public:
	Player(bool is_human, std::vector<Card*>::iterator first_card, std::vector<Card*>::iterator last_card, TextureManager * textur_manager, GLBL::player_side side, int hp, int mp, int gold);
	virtual ~Player();
	bool isHuman();

	void decrease_parameters(GLBL::parameters_type parameter, int power);
	void increase_parameters(GLBL::parameters_type parameter, int power);
	void updateTextsLine();
	int get_hp() { return health; }
	int get_mp() { return mana; }
	int get_gold() { return gold; }
	virtual void render();
	bool update(Card * next_card);



	std::vector<Card*>& player_card()
	{
		return cards;
	}

	bool is_any_card_used_now();

	//std::map<std::string, UI_text*>& texts_map()
	//{
	//	return texts;
	//}

protected:
	std::vector<Card*> cards;
	std::map<std::string, UI_text*> texts;
	std::vector<GUI*> cards_overlay;
	TextureManager* textur_manager;
	bool is_human;
	int health;
	int mana;
	int gold;
	std::vector<std::string> text_id;
	const GLBL::player_side side;
	void makePlayersText();
};

#endif

