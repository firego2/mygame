#include "MenuState.h"
#include "PlayState.h"
#include "GameObject.h"
#include "GUI.h"
#include "Button.h"
#include "Smoke.h"
#include "TextureManager.h"
#include "GameEngine.h"
#include "ConfirmState.h"
#include <iostream>

MenuState::MenuState(TextureManager* game_textures) : GameState(game_textures)
{
	if (!loadTextures())
	{
		std::cerr << "Error loading texture!" << std::endl;
		throw 505;
	}
	std::cout << "Menu textures loaded successfully !" << std::endl;

	GUI* background = new GUI(SDL_Rect{0,0, GLBL::BACKGROUND_SRC_WIDTH, GLBL::BACKGROUND_SRC_HEIGHT}, SDL_Rect{0,0, GLBL::SCREEN_WIDTH, GLBL::SCREEN_HEIGHT}, "menu_background");
	unused_state_objects.push_back(background);
	Smoke* smoke = new Smoke("smoke", GLBL::TOTAL_SMOKE_FRAME);
	unused_state_objects.push_back(smoke);

	GLBL::signal button_enum[GLBL::TOTAL_MENU_BUTTONS]{ GLBL::newgamePC, GLBL::newgamePlayer, GLBL::loadgame, GLBL::quit };
	for (int j = 0; j < GLBL::TOTAL_MENU_BUTTONS; j++)
	{
		SDL_Rect src = {0, j * GLBL::H_SRC_MENU_BUTTON, GLBL::W_SRC_MENU_BUTTON, GLBL::H_SRC_MENU_BUTTON}; // x, y, w, h
		SDL_Rect dst = {GLBL::SCREEN_WIDTH/2, (j * (GLBL::H_SRC_MENU_BUTTON + GLBL::BUTTON_SPACE)) + GLBL::BUTTON_SPACE, GLBL::SCREEN_WIDTH/2 - GLBL::BUTTON_SPACE, GLBL::SCREEN_HEIGHT / 8 };
		Button* button = new Button(src, dst, "menu_buttons", GLBL::BUTTON_FRAME, button_enum[j]);
		buttons_state_objects.push_back(button);
	}
	std::cout << "MenuState make ok!" << std::endl;

}


void MenuState::handleEvents()
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

void MenuState::update(GameEngine* game)
{
	switch (current_signal)
	{
	case (GLBL::none):
		GameState::update(game);
		break;
	case (GLBL::newgamePC):
	case(GLBL::newgamePlayer):
	case (GLBL::loadgame):
		game->PushState(current_signal);
		game->ChangeState(GLBL::playState);
		break;
	case (GLBL::quit):
        default:
		game->exit();
		break;
	}
}

bool MenuState::loadTextures()
{
	if (!textur_map->loadTexture("src/gfx/menu_background.png", "menu_background"))
	{
		return false;
	}
	textures_id.push_back("menu_background");

	if (!textur_map->loadTexture("src/gfx/menu_buttons.png", "menu_buttons"))
	{
		return false;
	}
	textures_id.push_back("menu_buttons");

	if (!textur_map->loadTexture("src/gfx/smoke.png", "smoke"))
	{
		return false;
	}
	textures_id.push_back("smoke");

	return true;
}



