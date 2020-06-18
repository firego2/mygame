#include "PlayState.h"
#include "GameEngine.h"
#include "GameObject.h"
#include "Button.h"
#include "TextureManager.h"
#include "Card.h"
#include "Player.h"
#include "Human.h"
#include "AI.h"
#include "AttackCard.h"
#include "DefenseCard.h"
#include "GUI.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include "UI_text.h"
#include "GameOverState.h"
#include <ctime> 

enum load_player_signal {
	comp,
	human
};


PlayState::PlayState(TextureManager* game_textures, GLBL::signal signal) : GameState (game_textures)
{
	if (!loadTextures())
	{
		std::cerr << "Error loading texture!" << std::endl;
		throw 505;
	}
	std::cout << "Play textures loaded successfully !" << std::endl;

	GUI* background = new GUI(SDL_Rect{0,0, GLBL::BACKGROUND_SRC_WIDTH, GLBL::BACKGROUND_SRC_HEIGHT}, SDL_Rect{0,0, GLBL::SCREEN_WIDTH, GLBL::SCREEN_HEIGHT}, "play_background");
	unused_state_objects.push_back(background);
	makeGUIinterface();
	makeGameButtons();

	if (signal == GLBL::loadgame)
	{
		if (!loadSave())
		{
			std::cerr << "Error loading save!" << std::endl;
			throw 500;
		}
	}
	else
	{
		if (!loadDeck())
		{
			std::cerr << "Error loading texture!" << std::endl;
			throw 505;
		}
		makeNewPlayers(signal);
	}
		
	makePlayerIcons();
}

PlayState::~PlayState()
{
	delete left_player;
	delete right_player;
	for (auto it = deck.begin(); it != deck.end(); it++)
	{
		delete (*it);
	}
}

void PlayState::makeGUIinterface()
{
	for (int i = 0; i < GLBL::TOTAL_PLAY_HUD_ICONS; i++) // mp hp gold
	{
		GUI* icon_left = new GUI(SDL_Rect{ i * GLBL::SRC_PLAYBUTTON_W, 0, GLBL::SRC_PLAYBUTTON_W, GLBL::SRC_PLAYBUTTON_H },
			SDL_Rect{ GLBL::SCREEN_SPACE, GLBL::DST_Y_PLAYER_TEXT - GLBL::SCREEN_SPACE + i * (GLBL::DST_PLAYBUTTON_H + GLBL::SCREEN_SPACE), GLBL::DST_PLAYBUTTON_W, GLBL::DST_PLAYBUTTON_H },
			"play_hud");
		GUI* icon_right = new GUI(SDL_Rect{ i * GLBL::SRC_PLAYBUTTON_W, 0, GLBL::SRC_PLAYBUTTON_W, GLBL::SRC_PLAYBUTTON_H },
			SDL_Rect{ GLBL::DST_X_SECOND_PLAYER_TEXT + 48, GLBL::DST_Y_PLAYER_TEXT - GLBL::SCREEN_SPACE + i * (GLBL::DST_PLAYBUTTON_H + GLBL::SCREEN_SPACE), GLBL::DST_PLAYBUTTON_W, GLBL::DST_PLAYBUTTON_H },
			"play_hud");
		unused_state_objects.push_back(icon_left);
		unused_state_objects.push_back(icon_right);
	}

	GUI* deck_back = new GUI(SDL_Rect{ 0,0, GLBL::SRC_CARD_W, GLBL::SRC_CARD_H }, SDL_Rect{ GLBL::DST_DECK_X, GLBL::DST_DECK_Y, GLBL::DST_CARD_W, GLBL::DST_CARD_H }, "deck");
	unused_state_objects.push_back(deck_back);
}


void PlayState::makeGameButtons()
{
	GLBL::signal signals[2] = { GLBL::savegame, GLBL::menuState }; // load buttons
	for (int i = 0; i < GLBL::TOTAL_PLAY_BUTTON; i++)
	{
		Button* button = new Button(SDL_Rect{ 0,  i * GLBL::SRC_PLAYBUTTON_H, GLBL::SRC_PLAYBUTTON_W, GLBL::SRC_PLAYBUTTON_H },
			SDL_Rect{ GLBL::DST_FIRST_PLAY_BUTTON_X + i * (GLBL::DST_PLAYBUTTON_W + GLBL::SCREEN_SPACE), GLBL::SCREEN_SPACE, GLBL::DST_PLAYBUTTON_W, GLBL::DST_PLAYBUTTON_H },
			"play_buttons", 1, signals[i]);
		buttons_state_objects.push_back(button);
	}
}

void PlayState::makePlayerIcons()
{
	SDL_Rect src_player_icon{ 0, GLBL::SRC_LEFT_PLAYER_ICON_Y, GLBL::SRC_PLAYER_ICON_W_H, GLBL::SRC_PLAYER_ICON_W_H };
	GUI* _left_player_icon = new GUI(src_player_icon, SDL_Rect{ GLBL::DST_LEFT_PLAYER_X, GLBL::DST_PLAYER_ICONS_Y, GLBL::DST_PLAYER_ICON_W_H, GLBL::DST_PLAYER_ICON_W_H }, "player_icons", 1);
	left_player_icon = _left_player_icon;
	unused_state_objects.push_back(_left_player_icon);

	if (right_player->isHuman())
		src_player_icon.y = GLBL::SRC_RIGHT_PLAYER_ICON_Y;
	else src_player_icon.y = GLBL::SRC_COMP_ICON_Y;

	GUI* _right_player_icon = new GUI(src_player_icon, SDL_Rect{ GLBL::DST_RIGHT_PLAYER_X, GLBL::DST_PLAYER_ICONS_Y, GLBL::DST_PLAYER_ICON_W_H, GLBL::DST_PLAYER_ICON_W_H }, "player_icons", 1);
	right_player_icon = _right_player_icon;
	unused_state_objects.push_back(_right_player_icon);

	if (curr_player == left_player)
		left_player_icon->set_frame(1);
	else right_player_icon->set_frame(1);
}

void PlayState::makeNewPlayers(GLBL::signal signal)
{
	srand((unsigned int)time(NULL));
	std::random_shuffle(deck.begin(), deck.end());
	auto first_card = deck.begin();
	auto last_card = next_card = deck.begin() + 6;
	left_player = new Human(first_card, last_card, textur_map, GLBL::left);

	first_card = last_card;
	last_card = next_card = next_card + 6;
	if (signal == GLBL::newgamePlayer)
	{
		right_player = new Human(first_card, last_card, textur_map, GLBL::right);
	}
	else if (signal == GLBL::newgamePC)
	{
		right_player = comp_player = new AI(first_card, last_card, textur_map, GLBL::right);
	}

	curr_player = left_player;
}



void PlayState::update(GameEngine* game)
{
	switch (current_signal)
	{
	case (GLBL::none):
	case (GLBL::AI_move):
	{
		GameState::update(game);

		Card* next_card_ptr = nullptr;
		if (next_card != deck.end())
			next_card_ptr = *next_card;

		if (curr_player->update(next_card_ptr))
		{
			get_curr_enemy()->updateTextsLine();
			if (next_card != deck.end())
				next_card++;

			changeCurrPlayer();
		}
		break;
	}
	case (GLBL::confirmState):
	{
		game->ChangeState(current_signal);
		current_signal = GLBL::none;
		break;
	}
	case (GLBL::left_win):
	case (GLBL::right_win):
	case (GLBL::comp_win):
	{
		game->PushState(current_signal);
		game->ChangeState(GLBL::gameoverState);
		break;
	}
	case (GLBL::menuState):
	{
		game->PushState(current_signal);
		game->ChangeState(current_signal);
		break;
	}
	case (GLBL::savegame):
	{
		if (!curr_player->is_any_card_used_now())
		{
			saveGame();
			std::cout << "Game saved" << std::endl;
		}
		else std::cout << "The game cannot be saved, wait until the turn is over" << std::endl;
		if (curr_player->isHuman())
			current_signal = GLBL::none;
		else current_signal = GLBL::AI_move;
		break;
	}
	case (GLBL::quit):
        default:
	{
		game->exit();
		break;
	}
	}
}

void PlayState::handleEvents()
{

	if (current_signal == GLBL::AI_move)
	{
		static int delay = 0;
		delay++;
		if (delay >= GLBL::FPS * 2)
		{
			comp_player->make_move(this);
			current_signal = GLBL::none;
			delay = 0;
		}
	}

	SDL_Event event;
	while (SDL_PollEvent(&event) != 0) {
		switch (event.type)
		{
		case SDL_QUIT:
			GameState::game_quit();
			break;
		case SDL_MOUSEBUTTONDOWN:
			GameState::button_click_check();
			if (current_signal != GLBL::AI_move)
			{
				for (auto it = curr_player->player_card().begin(); it != curr_player->player_card().end(); it++)
				{
					if ((*it)->in_focus())
						(*it)->use(this);
				}
			}
			break;
		case SDL_MOUSEMOTION:
			mouse_position.x_pos = event.motion.x;
			mouse_position.y_pos = event.motion.y;
			GameState::button_position_check();
			if (current_signal != GLBL::AI_move)
			{
				for (auto it = curr_player->player_card().begin(); it != curr_player->player_card().end(); it++)
					(*it)->in_focus(mouse_position);
			}
		default:
			break;
		}
	}

}

void PlayState::render()
{
	GameState::render();
	get_curr_enemy()->Player::render();
	curr_player->render();
}

bool PlayState::loadTextures()
{
	if (!textur_map->loadTexture("src/gfx/play_background.png", "play_background"))
	{
		return false;
	}
	textures_id.push_back("play_background");

	if (!textur_map->loadTexture("src/gfx/play_buttons.png", "play_buttons"))
	{
		return false;
	}
	textures_id.push_back("play_buttons");

	if (!textur_map->loadTexture("src/gfx/deck.png", "deck"))
	{
		return false;
	}
	textures_id.push_back("deck");

	if (!textur_map->loadTexture("src/gfx/play_hud.png", "play_hud"))
	{
		return false;
	}
	textures_id.push_back("play_hud");

	if (!textur_map->loadTexture("src/gfx/player_icons.png", "player_icons"))
	{
		return false;
	}
	textures_id.push_back("player_icons");

	if (!textur_map->loadTexture("src/gfx/overlay.png", "overlay"))
	{
		return false;
	}
	textures_id.push_back("overlay");

	if (!textur_map->loadFont("src/fonts/arial.ttf", "arial", 48))
	{
		return false;
	}
	textures_id.push_back("arial");


	return true;
}

bool PlayState::loadDeck()
{
	std::string str;

	std::ifstream fin("src/cnfg/deck_cnfg.txt"); 
	if (!fin.is_open())
	{
		std::cerr << "Error open card definitions" << std::endl;
		return false;
	}

	std::getline(fin, str);
	if (str != "CARD_TYPE COST_TYPE COST POWER_TYPE POWER")
	{
		std::cerr << "Error reading card definitions" << std::endl;
		fin.close();
		return false;
	}


	for (int row = 1, line = 0, cur_card = 1; cur_card <= GLBL::TOTAL_CARDS; cur_card++)
	{
		if (std::getline(fin, str))
		{
			int card_type, cost, power, int_cost_type, int_power_type;
			GLBL::parameters_type cost_type, power_type;
			if (sscanf(str.c_str(), "%d %d %d %d %d", &card_type, &int_cost_type, &cost, &int_power_type, &power) != 5)
			{
				break;
			}
                        cost_type = (GLBL::parameters_type)int_cost_type;
                        power_type = (GLBL::parameters_type)int_power_type;

			Card* card;
			SDL_Rect src;
			src.x = row * GLBL::SRC_CARD_W;
			src.y = line * GLBL::SRC_CARD_H;
			src.w = GLBL::SRC_CARD_W;
			src.h = GLBL::SRC_CARD_H;

			if (card_type == GLBL::attack)
				card = new AttackCard("deck", cost_type, cost, power_type, power, src);
			else if (card_type == GLBL::defense)
				card = new DefenseCard("deck", cost_type, cost, power_type, power, src);
			else
				break;
			
			deck.push_back(card);

			row++;
			if (row == 9)
			{
				row = 0;
				line++;
				if (line == 5)
				{
					fin.close();
					return true;
				}
			}
		}
		else break;

	}

	std::cerr << "Error reading card definitions" << std::endl;
	fin.close();
	return false;

}

bool PlayState::loadSave()
{
	std::string str;

	std::ifstream fin("src/save/save_game.txt");
	if (!fin.is_open())
	{
		std::cerr << "Error open save file" << std::endl;
		return false;
	}

	std::getline(fin, str);
	for (int _player = 0; _player < 2; _player++)
	{
		if (!load_player(fin, str))
			break;

		if (_player == 1 && load_remaining_cards(fin, str))
		{
			std::cout << "Game loaded succesfully!" << std::endl;
			fin.close();
			return true;
		}
	}

	std::cerr << "Error reading player definitions" << std::endl;
	fin.close();
	return false;
}

bool PlayState::load_player(std::ifstream& fin, std::string& str)
{
	if (str != "Player_type Player_number Hp Mp Gold")
		return false;

	static bool is_curr_player = true;
	if (std::getline(fin, str))
	{
		int player_type, int_player_side, hp, mp, gold;
		GLBL::player_side player_side;
		if (sscanf(str.c_str(), "%d %d %d %d %d", &player_type, &int_player_side, &hp, &mp, &gold) != 5)
			return false;
		player_side = (GLBL::player_side)int_player_side;

		Player* player;
		if (player_type == human)
		{
			if (load_player_cards(fin, str))
			{
				auto first_card_it = next_card;
				auto last_card_it = next_card = deck.end();
				player = new Human(first_card_it, last_card_it, textur_map, player_side, hp, mp, gold);
			}
			else return false;
		}
		else if (player_type == comp)
		{
			if (load_player_cards(fin, str))
			{
				auto first_card_it = next_card;
				auto last_card_it = next_card = deck.end();
				AI* ai_player;
				player = ai_player = new AI(first_card_it, last_card_it, textur_map, player_side, hp, mp, gold);
				comp_player = ai_player;
				current_signal = GLBL::AI_move;
			}
			else return false;
		}
		else return false;

		if (player_side == GLBL::left)
			left_player = player;
		else if (player_side == GLBL::right)
			right_player = player;
		else return false;

		if (is_curr_player)
			curr_player = player;
		is_curr_player = !is_curr_player;
	}

	return true;


}

bool PlayState::load_player_cards(std::ifstream& fin, std::string & str)
{

	std::getline(fin, str);
	if (str != "card_type, cost_type, cost, power_type, power, src_x, src_y, dst_x, dst_y")
		return false;

	SDL_Rect src_rect = {0, 0, GLBL::SRC_CARD_W, GLBL::SRC_CARD_H};
	SDL_Rect dst_rect = { 0, 0, GLBL::DST_CARD_W, GLBL::DST_CARD_H };
	for (int i = 0; i < 7; i++)
	{
		if (std::getline(fin, str))
		{
			if ((str == "Player_type Player_number Hp Mp Gold" || str == "card_type, cost_type, cost, power_type, power, src_x, src_y") && i > 0)
			{
				next_card = deck.end() - i;
				return true;
			}


			int card_type, int_cost_type, cost, int_power_type, power, src_x, src_y, dst_x, dst_y;
			GLBL::parameters_type cost_type, power_type;
			if (sscanf(str.c_str(), "%d %d %d %d %d %d %d %d %d", &card_type, &int_cost_type, &cost, &int_power_type, &power, &src_x, &src_y, &dst_x, &dst_y) != 9)
				return false;
                        cost_type = (GLBL::parameters_type)int_cost_type;
                        power_type = (GLBL::parameters_type)int_power_type;

			Card* card; 
			src_rect.x = src_x;
			src_rect.y = src_y;
			dst_rect.x = dst_x;
			dst_rect.y = dst_y;
			if (card_type == GLBL::attack)
				card = new AttackCard("deck", cost_type, cost, power_type, power, src_rect, dst_rect);
			else if (card_type == GLBL::defense)
				card = new DefenseCard("deck", cost_type, cost, power_type, power, src_rect, dst_rect);
			else
				break;
			deck.push_back(card);

		}
	}

	return false;
}

bool PlayState::load_remaining_cards(std::ifstream& fin, std::string& str)
{
	
	if (str != "card_type, cost_type, cost, power_type, power, src_x, src_y")
		return false;

	SDL_Rect src_rect = { 0, 0, GLBL::SRC_CARD_W, GLBL::SRC_CARD_H};

	int i = 0;
	while (std::getline(fin, str))
	{
		int card_type, int_cost_type, cost, int_power_type, power, src_x, src_y;
		GLBL::parameters_type cost_type, power_type;
		if (sscanf(str.c_str(), "%d %d %d %d %d %d %d", &card_type, &int_cost_type, &cost, &int_power_type, &power, &src_x, &src_y) != 7)
			return false;
                cost_type = (GLBL::parameters_type)int_cost_type;
                power_type = (GLBL::parameters_type)int_power_type;

		Card* card;
		src_rect.x = src_x;
		src_rect.y = src_y;

		if (card_type == GLBL::attack)
			card = new AttackCard("deck", cost_type, cost, power_type, power, src_rect);
		else if (card_type == GLBL::defense)
			card = new DefenseCard("deck", cost_type, cost, power_type, power, src_rect);
		else return false;


		deck.push_back(card);
		i++;
	}

	next_card = deck.end() - i;

	return true;
}




void PlayState::changeCurrPlayer()
{
	GLBL::signal sgnl; 

	if (curr_player == left_player)
	{
		sgnl = GLBL::left_win;
		curr_player = right_player;
		left_player_icon->set_frame(0);
		right_player_icon->set_frame(1);
	}
	else
	{
		if (curr_player->isHuman())
			sgnl = GLBL::right_win;
		else sgnl = GLBL::comp_win;

		curr_player = left_player;
		left_player_icon->set_frame(1);
		right_player_icon->set_frame(0);
	}

	if (curr_player->get_hp() <= 0)
		current_signal = sgnl;
	else if (right_player->isHuman())
		current_signal = GLBL::confirmState;
	else if (!curr_player->isHuman())
		current_signal = GLBL::AI_move;

}

void PlayState::saveGame()
{
	std::string str;

	std::ofstream out;          
	out.open("src/save/save_game.txt"); 
	if (out.is_open())
	{
		savePlayer(out, curr_player);
		savePlayer(out, get_curr_enemy());

		out << "card_type, cost_type, cost, power_type, power, src_x, src_y";
		for (auto it = next_card; it != deck.end(); it++)
		{
			GLBL::position src_pos = (*it)->get_src_position();
			out << std::endl << (*it)->card_type << " " << (*it)->cost_type << " " << (*it)->cost << " " << (*it)->power_type << " " << (*it)->power << " ";
			out << src_pos.x_pos << " " << src_pos.y_pos;
		}
	}


}

void PlayState::savePlayer(std::ofstream & out, Player* player)
{
	GLBL::player_side sgnl = GLBL::left;
	if (right_player == player)
		sgnl = GLBL::right;

	out << "Player_type Player_number Hp Mp Gold" << std::endl;
	out << player->isHuman() << " " << sgnl << " " << player->get_hp() << " " << player->get_mp() << " " << player->get_gold() << std::endl;
	out << "card_type, cost_type, cost, power_type, power, src_x, src_y, dst_x, dst_y" << std::endl;

	for (auto it = player->player_card().begin(); it != player->player_card().end(); it++)
	{
		GLBL::position src_pos = (*it)->get_src_position();
		GLBL::position dst_pos = (*it)->get_start_position();
		out << (*it)->card_type << " " << (*it)->cost_type << " " << (*it)->cost << " " << (*it)->power_type << " " << (*it)->power << " ";
		out << src_pos.x_pos << " " << src_pos.y_pos << " " << dst_pos.x_pos << " " << dst_pos.y_pos << std::endl;
	}

}

