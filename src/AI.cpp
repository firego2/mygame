#include "AI.h"
#include "GameState.h"
#include "PlayState.h"
#include "Card.h"
#include "AttackCard.h"
#include "DefenseCard.h"
#include "GUI.h"
#include <utility>


enum _available_card
{
	max_dmg,
	lock_dmg,
	max_hp,
	lock_hp_few_mp,
	lock_hp_few_gold,
	max_mana_up,
	max_gold_up,
	available_cards
};

const int MAX_CARD_DAMAGE = 15;
const GLBL::parameters_type MCD_COST_TYPE = GLBL::mana;
const int MCD_COST = 10;


void AI::make_move(PlayState* curr_state)
{

	int enemy_hp = curr_state->get_curr_enemy()->get_hp();
	//int enemy_mp = curr_state->get_curr_enemy()->get_mp(); ???
	//int enemy_gold = curr_state->get_curr_enemy()->get_gold(); ???

	Card* AI_cards[available_cards] {0};

	for (auto it = cards.begin(); it != cards.end(); it++)
	{

		if ((*it)->player_can_use_card(this))
		{
			if ((*it)->card_type == GLBL::attack && check_card(AI_cards[max_dmg], *it))
			{
				AI_cards[max_dmg] = *it;
			}
			else if ((*it)->card_type == GLBL::defense && (*it)->power_type == GLBL::hp && check_card(AI_cards[max_hp], *it))
			{
				AI_cards[max_hp] = *it;
			}
			else if ((*it)->card_type == GLBL::defense && (*it)->power_type == GLBL::mana && check_card(AI_cards[max_mana_up], *it))
			{
				AI_cards[max_mana_up] = *it;
			}
			else if ((*it)->card_type == GLBL::defense && (*it)->power_type == GLBL::gold && check_card(AI_cards[max_gold_up], *it))
			{
				AI_cards[max_gold_up] = *it;
			}
			else continue;
		}
		else
		{
			if ((*it)->card_type == GLBL::attack && check_card(AI_cards[lock_dmg], *it))
			{
				AI_cards[lock_dmg] = *it;
			}
			else if ((*it)->card_type == GLBL::defense && (*it)->power_type == GLBL::hp && (*it)->cost_type == GLBL::mana && check_card(AI_cards[lock_hp_few_mp], *it))
			{
				AI_cards[lock_hp_few_mp] = *it;
			}
			else if ((*it)->card_type == GLBL::defense && (*it)->power_type == GLBL::hp && (*it)->cost_type == GLBL::gold && check_card(AI_cards[lock_hp_few_gold], *it))
			{
				AI_cards[lock_hp_few_gold] = *it;
			}
			else continue;

		}

	}

	if (AI_cards[max_dmg] != nullptr && AI_cards[max_dmg]->power >= enemy_hp)
	{
		AI_cards[max_dmg]->use(curr_state);
		return;
	}


	bool heal_priority = false;
	if (health <= MAX_CARD_DAMAGE)
	{
		if (AI_cards[max_hp] != nullptr)
		{
			AI_cards[max_hp]->use(curr_state);
			return;
		}
		else if (AI_cards[lock_hp_few_mp] != nullptr || AI_cards[lock_hp_few_gold] != nullptr)
		{
			heal_priority = true;
		}
	}

	if (heal_priority)
	{
		if (AI_cards[lock_hp_few_mp] != nullptr && AI_cards[max_mana_up] != nullptr && (AI_cards[max_mana_up]->power + mana) >= AI_cards[lock_hp_few_mp]->cost)
		{
			AI_cards[max_mana_up]->use(curr_state);
			return;
		}
		else if (AI_cards[lock_hp_few_gold] != nullptr && AI_cards[max_gold_up] != nullptr && (AI_cards[max_gold_up]->power + gold) >= AI_cards[lock_hp_few_gold]->cost)
		{
			AI_cards[max_gold_up]->use(curr_state);
			return;
		}
	}

	if (AI_cards[lock_dmg] != nullptr && AI_cards[lock_dmg]->power >= enemy_hp)
	{
		if (AI_cards[lock_dmg]->cost_type == GLBL::mana && AI_cards[max_mana_up] != nullptr)
		{
			AI_cards[max_mana_up]->use(curr_state);
			return;
		}
		else if (AI_cards[lock_dmg]->cost_type == GLBL::gold && AI_cards[max_gold_up] != nullptr)
		{
			AI_cards[max_gold_up]->use(curr_state);
			return;
		}
	}

	if (AI_cards[max_dmg] != nullptr)
	{
		AI_cards[max_dmg]->use(curr_state);
		return;
	}

	if (AI_cards[max_gold_up] != nullptr)
		AI_cards[max_gold_up]->use(curr_state);
	else if (AI_cards[max_mana_up] != nullptr)
		AI_cards[max_mana_up]->use(curr_state);
	else if (AI_cards[max_hp] != nullptr)
		AI_cards[max_hp]->use(curr_state);

	return;
}

void AI::render()
{
	Player::render();

	auto card_it = cards.begin();
	auto overlay_it = cards_overlay.begin();
	while (card_it != cards.end())
	{
		if ((*card_it)->is_animated())
		{
			(*card_it)->draw(textur_manager);
		}
		else 
			(*overlay_it)->draw(textur_manager);

		card_it++;
		overlay_it++;
	}

}

bool AI::check_card(Card* curr_card, Card* check_card)
{
	return (curr_card == nullptr || check_card->power > curr_card->power || (check_card->power == curr_card->power && check_card->cost < curr_card->cost) );
}
