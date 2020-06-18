#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <vector>
#include <string>
#include "GLBL.h"

class GameEngine;
class GameObject;
class TextureManager;
class Button;

class GameState
{
public:
	GameState(TextureManager* game_textures) : textur_map(game_textures), mouse_position{ 0,0 }, current_signal(GLBL::none) {};
	virtual ~GameState();
	virtual void handleEvents() = 0;
	virtual void update(GameEngine *);
	virtual void render();
	void set_signal(GLBL::signal);
protected:
	std::vector<GameObject *> unused_state_objects;
	std::vector<Button*> buttons_state_objects;
	std::vector<std::string> textures_id;
	TextureManager* textur_map;
	GLBL::position mouse_position;
	GLBL::signal current_signal;

	virtual bool loadTextures() = 0;
	void button_position_check();
	void button_click_check();
	void game_quit();
};

#endif
