#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SDL2/SDL.h>
#include "GLBL.h"
#include <string>

class TextureManager;
class GameState;

class GameObject
{
public:
	GameObject(const SDL_Rect & _src, const SDL_Rect & _dst, const char* texture_id, int total_frame = 0) : src_rect(_src), dst_rect(_dst), texture_id(texture_id), current_frame(0), total_frame(total_frame) {};
	virtual ~GameObject() {}
	virtual void update() = 0;
	void draw(TextureManager* textures_map);


protected:
	SDL_Rect src_rect;
	SDL_Rect dst_rect;
	std::string texture_id;
	int current_frame;
	int total_frame;
};


#endif



