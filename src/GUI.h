#ifndef GUI_H
#define GUI_H

#include "GameObject.h"
class GUI : public GameObject
{
public:
	GUI(SDL_Rect _src, SDL_Rect _dst, const char* name_in_map, int total_frame = 0) : GameObject(_src, _dst, name_in_map, total_frame) {}
	virtual void update();
	void set_frame(int frame) { current_frame = frame; }
	void set_dst_rct(const SDL_Rect& rct) {
		dst_rect = rct;
	}
private:
};

#endif
