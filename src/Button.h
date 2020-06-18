#ifndef BUTTON_H
#define BUTTON_H

#include "Used.h"


class Button : public Used
{
public:
	Button(SDL_Rect _src, SDL_Rect _dst, const char* name_in_map, int total_frame, GLBL::signal signal) : Used(_src, _dst, name_in_map, total_frame), change_frame(false), button_signal(signal) {}
	void use(GameState *);
	virtual void update();

private:
	bool change_frame; 
	GLBL::signal button_signal;
};

#endif
