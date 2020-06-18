#include "ConfirmState.h"
#include "GameEngine.h"
#include "GameObject.h"
#include "Button.h"
#include "GUI.h"
#include "TextureManager.h"
#include <iostream>

ConfirmState::ConfirmState(TextureManager* textur_map) : GameState(textur_map)
{
	if (!loadTextures())
	{
		std::cerr << "Error loading texture!" << std::endl;
		throw 505;
	}
	std::cout << "Play textures loaded successfully !" << std::endl;

	GUI* background = new GUI(SDL_Rect{0,0, GLBL::BACKGROUND_SRC_WIDTH, GLBL::BACKGROUND_SRC_HEIGHT}, SDL_Rect{0,0, GLBL::SCREEN_WIDTH, GLBL::SCREEN_HEIGHT},"confirm_background");
	unused_state_objects.push_back(background);

	Button* button = new Button(SDL_Rect{ 0,  0, GLBL::SRC_OK_BUTTON_W, GLBL::SRC_OK_BUTTON_H },
		SDL_Rect{GLBL::DST_OK_BUTTON_X, GLBL::DST_OK_BUTTON_Y, GLBL::DST_OK_BUTTON_W, GLBL::DST_OK_BUTTON_H },
		"confirm_button", 1, GLBL::playState);
	buttons_state_objects.push_back(button);
}


void ConfirmState::update(GameEngine* game)
{
	switch (current_signal)
	{
	case(GLBL::none):
		GameState::update(game);
		break;
	case(GLBL::playState):
		game->ChangeState(current_signal);
		current_signal = GLBL::none;
		break;
	case(GLBL::quit):
        default:
		game->exit();
		break;
	}

}

void ConfirmState::handleEvents()
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

void ConfirmState::render()
{
	GameState::render();
}

bool ConfirmState::loadTextures()
{
	if (!textur_map->loadTexture("src/gfx/confirm_background.png", "confirm_background"))
	{
		return false;
	}
	textures_id.push_back("confirm_background");

	if (!textur_map->loadTexture("src/gfx/confirm_button.png", "confirm_button"))
	{
		return false;
	}
	textures_id.push_back("confirm_button");

	return true;
}
