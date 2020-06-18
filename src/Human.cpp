#include "Human.h"
#include "Card.h"
#include "GUI.h"


void Human::render()
{
	Player::render();

	auto card_it = cards.begin();
	auto overlay_it = cards_overlay.begin();
	while (card_it != cards.end())
	{
		(*card_it)->draw(textur_manager);

		if (!(*card_it)->player_can_use_card(this) && !(*card_it)->is_animated())
		{
			(*overlay_it)->draw(textur_manager);
		}

		card_it++;
		overlay_it++;
	}


}
