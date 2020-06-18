#include "Card.h"
#include "Player.h"
#include "TextureManager.h"


bool Card::card_already_use = false;

void Card::update()
{

	if (_animation)
	{
		if (dst_rect.y > GLBL::DST_Y_USED_CARD)
		{	
			dst_rect.y = dst_rect.y - 2;
		}

		if ( dst_rect.y == GLBL::DST_Y_USED_CARD)
		{
			timer++;
			if (timer >= 60)
			{
				_is_used = true;
				card_already_use = false;
			}
		}

	}


}

bool Card::player_can_use_card(Player* player)
{
	int points;
	if (cost_type == GLBL::mana)
		points = player->get_mp();
	else if (cost_type == GLBL::gold)
		points = player->get_gold();
	else points = player->get_hp();

	if (points < cost)
		return false;

	return true;
}

