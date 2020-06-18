#ifndef HUMAN_H
#define HUMAN_H

#include "Player.h"
class Human : public Player
{
public:
	Human(std::vector<Card*>::iterator first_card, std::vector<Card*>::iterator last_card, TextureManager* textur_manager, GLBL::player_side side, int hp = GLBL::START_HP, int mp = GLBL::START_MP, int gold = GLBL::START_GOLD) : Player(true, first_card, last_card, textur_manager, side, hp, mp, gold) {}
	virtual void render();
private:

};

#endif
