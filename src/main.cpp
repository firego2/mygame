#include "GameEngine.h"
#include "GLBL.h"
#undef main


Uint32 frameStart, frameTime;

int main(int argc, char* arhv[])
{
	GameEngine game ("Card Battle");

	while ( game.is_running() )
	{
		frameStart = SDL_GetTicks();

		game.handleEvents();
		game.update();
		game.render();

		frameTime = SDL_GetTicks() - frameStart;  
		if (frameTime < GLBL::DELAY_TIME) 
		{ 
			SDL_Delay((int)(GLBL::DELAY_TIME - frameTime)); 
		}
	}

	game.clean();

	return 0;

}
