#ifndef AI_H
#define AI_H

#include "Player.h"

class PlayState; 
class GUI;

class AI : public Player
{
public:
	AI(std::vector<Card*>::iterator first_card, std::vector<Card*>::iterator last_card, TextureManager* textur_manager, GLBL::player_side side, int hp = GLBL::START_HP, int mp = GLBL::START_MP, int gold = GLBL::START_GOLD) : Player(false, first_card, last_card, textur_manager, side, hp, mp, gold) {}
	void make_move(PlayState * curr_state);
	virtual void render();
private:
	bool check_card(Card* curr_card, Card* check_card);
};

#endif
