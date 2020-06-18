#ifndef UI_TEXT_H
#define UI_TEXT_H

#include "GameObject.h"



class UI_text : public GameObject
{
public:
	UI_text(const SDL_Rect& dst, const char* texture_id, const char* font_id, const char* text, TextureManager* texture_manager);
	virtual void update();
	void updateText(const char* new_text);
private:
	TextureManager* textures;
	std::string font_id;
	std::string current_text;
};

#endif
