#ifndef CARD_H
#define CARD_H

#include "Used.h"

class PlayState;
class Player;

class Card : public Used
{
public:
	Card(const SDL_Rect& _src, const SDL_Rect& _dst, const char* name_in_map, GLBL::card_type card_type, GLBL::parameters_type cost_type, int cost, GLBL::parameters_type power_type, int power) : Used(_src, _dst, name_in_map), card_type(card_type),
		cost_type(cost_type), cost(cost), power_type(power_type), power(power), timer(0), _is_used(false), _animation(false), start_position{ 0,0 } {}
	~Card() { card_already_use = false; }
	virtual void use(PlayState*) = 0;
	virtual void update();


	void set_start_position(const GLBL::position & dst) {
		dst_rect.x = dst.x_pos;
		dst_rect.y = dst.y_pos;
		start_position.x_pos = dst.x_pos;
		start_position.y_pos = dst.y_pos;
	}

	GLBL::position get_start_position()
	{
		return start_position;
	}

	bool is_used() {
		return _is_used;
	}
	bool is_animated()
	{
		return _animation;
	}
	GLBL::position get_src_position() {
		return GLBL::position{ src_rect.x, src_rect.y };
	}

	bool player_can_use_card(Player* player);

	const GLBL::card_type card_type;
	const GLBL::parameters_type cost_type;
	const int cost;
	const GLBL::parameters_type power_type;
	const int power;

protected:
	
	int timer;
	static bool card_already_use;
	bool _is_used;
	bool _animation;
	GLBL::position start_position;
};

#endif

