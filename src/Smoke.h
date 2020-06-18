#ifndef SMOKE_H
#define SMOKE_H

#include "GameObject.h"
class Smoke : public GameObject
{
public:
	Smoke(const char* name_in_map, int total_frame) : GameObject(SDL_Rect{ 0, 0, GLBL::BACKGROUND_SRC_WIDTH, GLBL::BACKGROUND_SRC_HEIGHT }, SDL_Rect{ 0, 0, GLBL::SCREEN_WIDTH, GLBL::SCREEN_HEIGHT }, name_in_map, total_frame), current_row(0), current_column(0) {}
        ~Smoke();
	virtual void update();
private:
	int current_row;
	int current_column;
        static int delay_counter;
	static int reset_counter;
};

#endif
