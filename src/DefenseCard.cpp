#include "DefenseCard.h"
#include "PlayState.h"
#include "Player.h"

void DefenseCard::use(PlayState* state)
{
	if (!card_already_use)
	{
		
		Player* curr_player = state->get_curr_player();
		if (!Card::player_can_use_card(curr_player))
			return;

		curr_player->decrease_parameters(cost_type, cost);
		curr_player->increase_parameters(power_type, power);

		card_already_use = true;
		_animation = true;
	}

}
