#ifndef LIGHTNING_H
#define LIGHTNING_H

#include "GameObject.h"


class Lightning : public GameObject
{
public:
	Lightning(const char* name_in_map, int total_frame = 0) : GameObject(SDL_Rect{ 0, 0, GLBL::BACKGROUND_SRC_WIDTH, GLBL::BACKGROUND_SRC_HEIGHT },
		SDL_Rect{ 0, 0, GLBL::SCREEN_WIDTH, GLBL::SCREEN_HEIGHT }, name_in_map, total_frame), animation_direction(right) {}
	virtual void update();
private:
	bool animation_direction;
	enum {
		left,
		right
	};
};

#endif
