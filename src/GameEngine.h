#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <SDL2/SDL.h>  
#include <SDL2/SDL_image.h>
#include "GLBL.h"
#include <map>

class TextureManager;
class GameState;

class GameEngine
{
public:
	GameEngine(const char* title);
	~GameEngine() {}

	void handleEvents();
	void update();
	void render();
	void clean();

	void ChangeState(GLBL::signal signal);
	void PushState(GLBL::signal state_signal);
	void PopState(GLBL::signal state_signal);

	bool is_running() const { return game_running; }
	void exit() { game_running = false; }
	TextureManager* getTextures() { return m_textures; }
private:
	
	SDL_Window* m_window;
	SDL_Renderer* m_renderer;
	TextureManager* m_textures;
	std::map<GLBL::signal, GameState *> game_states;
	GLBL::signal current_state;
	bool game_running;


};

#endif

