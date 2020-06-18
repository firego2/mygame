#include "GameObject.h"
#include "TextureManager.h"


void GameObject::draw(TextureManager* textures_map)
{
	if (SDL_RectEmpty(&src_rect))
		textures_map->draw(texture_id.c_str(), nullptr, &dst_rect);
	else textures_map->draw(texture_id.c_str(), &src_rect, &dst_rect);
}

