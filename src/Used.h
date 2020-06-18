#ifndef USED_H
#define USED_H

#include "GameObject.h"
class Used : public GameObject
{
public:
	Used(const SDL_Rect & _src, const SDL_Rect & _dst, const char* name_in_map, int total_frame = 0) : GameObject(_src, _dst, name_in_map, total_frame), focus(false) {}
	virtual void update() = 0;

	bool in_focus(const GLBL::position &);
    bool in_focus() { return focus; }
protected:
	bool focus;
};

#endif
