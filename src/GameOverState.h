#ifndef GAMEOVERSTATE_H
#define GAMEOVERSTATE_H

#include "GameState.h"

class GameEngine;
class GUI;

class GameOverState : public GameState
{
public:
	GameOverState(TextureManager* game_textures, GLBL::signal signal); //: GameState(game->getTextures()) {}
	virtual void update(GameEngine* game);
	virtual void handleEvents();
	virtual void render();

private:
	virtual bool loadTextures();
};

#endif
