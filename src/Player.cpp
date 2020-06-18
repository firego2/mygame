#include "Player.h"
#include "Card.h"
#include "GUI.h"
#include "UI_text.h"
#include "TextureManager.h"
#include <iostream>


Player::Player(bool is_human, std::vector<Card*>::iterator first_card, std::vector<Card*>::iterator last_card, TextureManager* textur_manager, GLBL::player_side side, int hp, int mp, int gold) : textur_manager(textur_manager), is_human(is_human), health(hp), mana(mp), gold(gold), side(side)
{
	std::string overlay_id;
	if (is_human)
		overlay_id = "overlay";
	else overlay_id = "deck";
	SDL_Rect src_overlay_rect{ 0, 0, GLBL::SRC_CARD_W, GLBL::SRC_CARD_H };
	SDL_Rect dst_overlay_rect{ 0, 0, GLBL::DST_CARD_W, GLBL::DST_CARD_H };

	int j = 0;
	for (std::vector<Card*>::iterator it = first_card; it != last_card; it++, j++)
	{
		GLBL::position dst;
		dst_overlay_rect.x = dst.x_pos = GLBL::SCREEN_SPACE + (j * (GLBL::SCREEN_SPACE + GLBL::DST_CARD_W));
		dst_overlay_rect.y = dst.y_pos = GLBL::DST_Y_PLAY_CARD;
		GUI* card_overlay = new GUI(src_overlay_rect, dst_overlay_rect, overlay_id.c_str());

		cards_overlay.push_back(card_overlay);
		cards.push_back(*it);
		
		if ((*it)->get_start_position().x_pos == 0)
			(*it)->set_start_position(dst);
	}

	makePlayersText();

}

void Player::makePlayersText()
{
	SDL_Rect dst_rect{ 0,GLBL::DST_Y_PLAYER_TEXT, 2 * GLBL::DST_W_ONE_CHARACHTER, GLBL::FONT_SIZE };
	if (side == GLBL::left)
	{

		text_id.push_back("left_hp");
		text_id.push_back("left_mana");
		text_id.push_back("left_gold");
		dst_rect.x = GLBL::DST_X_FIRST_PLAYER_TEXT;
	}
	else if (side == GLBL::right)
	{
		dst_rect.x = GLBL::DST_X_SECOND_PLAYER_TEXT;
		text_id.push_back("right_hp");
		text_id.push_back("right_mana");
		text_id.push_back("right_gold");
	}

	int points[3] = { health, mana, gold };
	const char* id_fonts = "arial";
	for (int i = 0; i < 3; i++)
	{
		dst_rect.y = GLBL::DST_Y_PLAYER_TEXT + i * (GLBL::DST_PLAYBUTTON_H + GLBL::SCREEN_SPACE);
		UI_text* new_text = new UI_text(dst_rect, text_id[i].c_str(), id_fonts, std::to_string(points[i]).c_str(), textur_manager);
		texts[text_id[i]] = new_text;
	}
}

Player::~Player()
{
	for (auto it = texts.begin(); it != texts.end(); it++)
	{
		delete it->second;
	}
	for (auto it = cards_overlay.begin(); it != cards_overlay.end(); it++)
	{
		delete (*it);
	}
	textur_manager->destroyTextures(text_id);
}


bool Player::isHuman()
{
	return is_human;
}

void Player::decrease_parameters(GLBL::parameters_type parameter, int power)
{
	switch (parameter)
	{
	case (GLBL::mana):
		mana = mana - power;
		break;
	case(GLBL::gold):
		gold = gold - power;
		break;
	case (GLBL::hp):
		health = health - power;
		break;
        case (GLBL::free):
        default:             //GLBL::non_param used or not?
                break;
	}


}

void Player::increase_parameters(GLBL::parameters_type parameter, int power)
{
	switch (parameter)
	{
	case (GLBL::mana):
		mana = mana + power;
		break;
	case(GLBL::gold):
		gold = gold + power;
		break;
	case (GLBL::hp):
		health = health + power;
		break;
        case (GLBL::free):
        default:
                break;
	}


}

void Player::updateTextsLine()
{
	int points[3] = { health, mana, gold };
	if (health < 0)
		points[0] = 0;

	for (int i = 0; i < 3; i++)
	{
		texts[text_id[i]]->updateText(std::to_string(points[i]).c_str());
		texts[text_id[i]]->update();
	}
}

void Player::render()
{
	for (auto it = texts.begin(); it != texts.end(); it++)
	{
		it->second->draw(textur_manager);
	}
}

bool Player::update(Card * next_card)
{
	for (auto it = cards.begin(); it != cards.end(); it++)  
	{
		(*it)->update();
		if ((*it)->is_used())
		{
			updateTextsLine();
			GLBL::position start_pos = (*it)->get_start_position();
			*it = next_card;
			if (next_card != nullptr)
				(*it)->set_start_position(start_pos);
			return true;
		}
	}

	return false;
}

bool Player::is_any_card_used_now()
{
	for (auto it = cards.begin(); it != cards.end(); it++)
	{
		if ((*it)->is_animated())
			return true;
	}

	return false;
}


