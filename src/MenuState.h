#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "GameState.h"


class MenuState : public GameState
{
public:
	MenuState(TextureManager* game_textures);
	virtual void handleEvents();
	virtual void update(GameEngine* game);

private:
	virtual bool loadTextures();
};

#endif
