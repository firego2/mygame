#ifndef DEFENSECARD_H
#define DEFENSECARD_H

#include "Card.h"
class DefenseCard : public Card
{
public:
	DefenseCard(const char* name_in_map, GLBL::parameters_type cost_type, int cost, GLBL::parameters_type power_type, int power, const SDL_Rect& src_rect, const SDL_Rect& dst_rect = SDL_Rect{0,0, GLBL::DST_CARD_W, GLBL::DST_CARD_H}) : Card(src_rect, dst_rect, name_in_map, GLBL::defense, cost_type, cost, power_type, power) {}
	virtual void use(PlayState*);
private:

};

#endif
