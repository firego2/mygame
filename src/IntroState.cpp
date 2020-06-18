#include "IntroState.h"
#include "GameObject.h"
#include "GLBL.h"
#include "GUI.h"
#include "TextureManager.h"
#include "GameEngine.h"
#include "MenuState.h"
#include "Lightning.h"
#include <iostream>

IntroState::IntroState(TextureManager* game_textures) : GameState(game_textures)
{

	if (!loadTextures())
	{
		std::cerr << "Error loading texture!" << std::endl;
		throw 505;
	}
	std::cout << "Intro textures loaded successfully !" << std::endl;

	GUI* background = new GUI(SDL_Rect{0,0, GLBL::BACKGROUND_SRC_WIDTH, GLBL::BACKGROUND_SRC_HEIGHT}, SDL_Rect{0,0, GLBL::SCREEN_WIDTH, GLBL::SCREEN_HEIGHT}, "intro");
	unused_state_objects.push_back(background);
	Lightning* lightning = new Lightning("lightning", GLBL::TOTAL_LIGHTNING_FRAME);
	unused_state_objects.push_back(lightning);
	std::cout << "IntroState make ok!" << std::endl;

}



void IntroState::handleEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event) != 0) {
		switch (event.type)
		{
		case SDL_QUIT:
			GameState::game_quit();
			break;
		case SDL_MOUSEBUTTONUP:
		case SDL_KEYUP:
			std::cout << "start menu!" << std::endl;
			current_signal = GLBL::menuState;
			break;
		default:
			break;
		}
	}
}

void IntroState::update(GameEngine* game)
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



bool IntroState::loadTextures()
{
	if (!textur_map->loadTexture("src/gfx/intro.png", "intro"))
	{
		return false;
	}
	textures_id.push_back("intro");

	if (!textur_map->loadTexture("src/gfx/lightning.png", "lightning"))
	{
		return false;
	}
	textures_id.push_back("lightning");

	return true;
}
