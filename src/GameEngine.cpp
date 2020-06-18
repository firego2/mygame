#include "GameEngine.h"
#include "TextureManager.h"
#include "GameState.h"
#include "MenuState.h"
#include "IntroState.h"
#include "PlayState.h"
#include "ConfirmState.h"
#include "GameOverState.h"
#include "GameObject.h"
#include "GLBL.h"
#include <iostream>



GameEngine::GameEngine(const char* title) : m_window(NULL), m_renderer(NULL), m_textures(NULL), current_state(GLBL::introState), game_running(false)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "SDL_INIT_EVERYTHING initialized successfuly! " << std::endl;

		if (IMG_Init(IMG_INIT_PNG) && TTF_Init() == 0)
		{
			std::cout << "SDL IMG_INIT_PNG initialized successfuly! " << std::endl;
			m_window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, GLBL::SCREEN_WIDTH, GLBL::SCREEN_HEIGHT, SDL_WINDOW_SHOWN); 
			if (m_window != NULL)
			{
				std::cout << "Window created!" << std::endl;
				m_renderer = SDL_CreateRenderer(m_window, -1, 0);

				if (m_renderer != NULL)
				{
					std::cout << "Renderer created!" << std::endl;
					SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
					game_running = true;
				}
			}
		}
	}

	if (!game_running)
		std::cerr << "SDL_Init fail! SDL error: " << SDL_GetError() << std::endl;
	else {
		m_textures = new TextureManager(m_renderer);
		try {
			GameState* state = new IntroState(m_textures);
			current_state = GLBL::introState;
			game_states[current_state] = state;
		}
		catch (int i)
		{
			std::cerr << "Error: " << i << std::endl;
			game_running = false;
		}
	}
}

void GameEngine::handleEvents()
{
	game_states[current_state]->handleEvents();
}

void GameEngine::update()
{
	game_states[current_state]->update(this);
}

void GameEngine::render()
{
	SDL_RenderClear(m_renderer);
	game_states[current_state]->render();
	SDL_RenderPresent(m_renderer);
}

void GameEngine::clean()
{

	std::cout << "Cleaning game..." << std::endl;  
	for (auto it = game_states.begin(); it != game_states.end(); it++)
		delete it->second;
	delete m_textures;
	SDL_DestroyWindow(m_window); 
	SDL_DestroyRenderer(m_renderer);  
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

void GameEngine::ChangeState(GLBL::signal signal)
{

	switch (signal)
	{
	case(GLBL::menuState):
		PopState(GLBL::introState);
		PopState(GLBL::playState);
		PopState(GLBL::gameoverState);
		break;
	case(GLBL::playState):
		PopState(GLBL::menuState);
		break;
	case(GLBL::confirmState):
		if (game_states.count(signal) == 0)
			PushState(signal);
		break;
	case(GLBL::gameoverState):
		PopState(GLBL::playState);
		PopState(GLBL::confirmState);
		break;
	default:
		std::cerr << "Unavailable game state" << std::endl;
		game_running = false;
	}
	current_state = signal;


}

void GameEngine::PushState(GLBL::signal state_signal)
{
	if (game_states.count(state_signal))
		delete game_states[state_signal];

	try 
	{
		GameState* state;
		switch (state_signal)
		{
		case(GLBL::menuState):
			state = new MenuState(m_textures);
			game_states[GLBL::menuState] = state;
			break;
		case(GLBL::confirmState):
			state = new ConfirmState(m_textures);
			game_states[GLBL::confirmState] = state;
			break;
		case(GLBL::newgamePC):
		case(GLBL::newgamePlayer):
		case(GLBL::loadgame):
			state = new PlayState(m_textures, state_signal);
			game_states[GLBL::playState] = state;
			break;
		case(GLBL::left_win):
		case(GLBL::right_win):
		case(GLBL::comp_win):
			state = new GameOverState(m_textures, state_signal);
			game_states[GLBL::gameoverState] = state;
			break;
		default:
			throw 501;
			break;
		}
	}
	catch (int i)
	{
		std::cerr << "Game state don`t create! ERROR: " << i << std::endl;
		game_running = false;
	}
}

void GameEngine::PopState(GLBL::signal state_signal)
{
	if (game_states.count(state_signal))
	{
		std::cout << "delete state" << std::endl;
		delete game_states[state_signal];
		game_states.erase(state_signal);
	}


}




