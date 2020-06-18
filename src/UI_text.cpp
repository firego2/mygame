#include "UI_text.h"
#include "TextureManager.h"


UI_text::UI_text(const SDL_Rect& dst, const char* texture_id, const char* font_id, const char* text, TextureManager* texture_manager) : GameObject(SDL_Rect{ 0,0,0,0 }, dst, texture_id), textures(texture_manager), font_id(font_id), current_text(text)
{
	texture_manager->updateTextLine(texture_id, font_id, text);
}

void UI_text::update()
{
	textures->updateTextLine(texture_id.c_str(), font_id.c_str(), current_text.c_str());
}

void UI_text::updateText(const char* new_text)
{
	current_text = new_text;
	dst_rect.w = current_text.length() * GLBL::DST_W_ONE_CHARACHTER;
}
