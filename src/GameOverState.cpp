#include "GameOverState.h"
#include "GameEngine.h"
#include "GameObject.h"
#include "Button.h"
#include "TextureManager.h"
#include "GUI.h"
#include <iostream>

GameOverState::GameOverState(TextureManager* textur_map, GLBL::signal signal) : GameState(textur_map)
{
	if (!loadTextures())
	{
		std::cerr << "Error loading texture!" << std::endl;
		throw 505;
	}
	std::cout << "Play textures loaded successfully !" << std::endl;

	GUI* background = new GUI(SDL_Rect{0,0, GLBL::BACKGROUND_SRC_WIDTH, GLBL::BACKGROUND_SRC_HEIGHT}, SDL_Rect{0,0, GLBL::SCREEN_WIDTH, GLBL::SCREEN_HEIGHT},"gameover_background");
	unused_state_objects.push_back(background);

	SDL_Rect src{ 0, 0, GLBL::SRC_PLAYER_ICON_W_H, GLBL::SRC_PLAYER_ICON_W_H };
	SDL_Rect dst{ GLBL::DST_GAMEOVER_ICON_X, GLBL::DST_GAMEOVER_ICON_Y, GLBL::DST_PLAYER_ICON_W_H, GLBL::DST_PLAYER_ICON_W_H };
	switch (signal)
	{
	case(GLBL::left_win):
		src.y = GLBL::SRC_LEFT_PLAYER_ICON_Y;
		break;
	case(GLBL::right_win):
		src.y = GLBL::SRC_RIGHT_PLAYER_ICON_Y;
		break;
	case(GLBL::comp_win):
		src.y = GLBL::SRC_COMP_ICON_Y;
		break;
        default:
                std::cerr << "Error signal for create state" << std::endl;
                throw 505;
	}
	GUI* icon = new GUI( src, dst, "winner_icon");
	unused_state_objects.push_back(icon);

	Button* button = new Button(SDL_Rect{ 0,  0, GLBL::SRC_OK_BUTTON_W, GLBL::SRC_OK_BUTTON_H },
		SDL_Rect{ GLBL::DST_OK_BUTTON_X, GLBL::DST_OK_BUTTON_Y, GLBL::DST_OK_BUTTON_W, GLBL::DST_OK_BUTTON_H },
		"gameover_button", 1, GLBL::menuState);
	buttons_state_objects.push_back(button);
}


void GameOverState::update(GameEngine* game)
{
	switch (current_signal)
	{
	case(GLBL::none):
		GameState::update(game);
		break;
	case(GLBL::menuState):
		game->PushState(current_signal);
		game->ChangeState(current_signal);
		break;
	case(GLBL::quit):
        default:
		game->exit();
		break;
	}

}

void GameOverState::handleEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event) != 0) {
		switch (event.type)
		{
		case SDL_QUIT:
			GameState::game_quit();
			break;
		case SDL_MOUSEBUTTONDOWN:
			GameState::button_click_check();
			break;
		case SDL_MOUSEMOTION:
			mouse_position.x_pos = event.motion.x;
			mouse_position.y_pos = event.motion.y;
			GameState::button_position_check();
		default:
			break;
		}
	}
}

void GameOverState::render()
{
	GameState::render();
}

bool GameOverState::loadTextures()
{

	if (!textur_map->loadTexture("src/gfx/gameover_background.png", "gameover_background"))
	{
		return false;
	}
	textures_id.push_back("gameover_background");

	if (!textur_map->loadTexture("src/gfx/gameover_button.png", "gameover_button"))
	{
		return false;
	}
	textures_id.push_back("gameover_button");

	if (!textur_map->loadTexture("src/gfx/player_icons.png", "winner_icon"))
	{
		return false;
	}
	textures_id.push_back("player_icons");

	return true;
}
