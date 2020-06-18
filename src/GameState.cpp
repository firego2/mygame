#include "GameState.h"
#include "GameEngine.h"
#include "GameObject.h"
#include "Button.h"
#include "TextureManager.h"
#include <iostream>


GameState::~GameState()
{
	for (auto it = unused_state_objects.begin(); it != unused_state_objects.end(); it++)
	{
		delete *it;
	}
	for (auto it = buttons_state_objects.begin(); it != buttons_state_objects.end(); it++)
	{
		delete *it;
	}
	textur_map->destroyTextures(textures_id);
}

void GameState::update(GameEngine* game)
{
	for (auto it = unused_state_objects.begin(); it != unused_state_objects.end(); it++)
	{
		(*it)->update();
	} 

	for (auto it = buttons_state_objects.begin(); it != buttons_state_objects.end(); it++)
	{
		(*it)->update();
	}
}

void GameState::render()
{
	for (auto it = unused_state_objects.begin(); it != unused_state_objects.end(); it++)
	{
		(*it)->draw(textur_map);
	}
	for (auto it = buttons_state_objects.begin(); it != buttons_state_objects.end(); it++)
	{
		(*it)->draw(textur_map);
	}
}

void GameState::set_signal(GLBL::signal signal)
{
	current_signal = signal;
}

void GameState::button_position_check()
{
	for (auto it = buttons_state_objects.begin(); it != buttons_state_objects.end(); it++)
	{
		(*it)->in_focus(mouse_position);
	}
}

void GameState::button_click_check()
{
	for (auto it = buttons_state_objects.begin(); it != buttons_state_objects.end(); it++)
	{
		if ((*it)->in_focus())
			(*it)->use(this);
	}
}

void GameState::game_quit()
{
	std::cout << "Command Alt + F4!" << std::endl;
	current_signal = GLBL::quit;
}
