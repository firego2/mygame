#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <map>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h> 
#include <SDL2/SDL_ttf.h>

class TextureManager
{
public:
	TextureManager(SDL_Renderer * renderer) : m_renderer(renderer) {};
	~TextureManager();
	bool loadTexture(const char * path, const char * texture_id);
	void draw(const char * texture_id, const SDL_Rect * src, const SDL_Rect * dst);
	bool loadFont(const char* path, const char* font_id, int fontSize);
	bool updateTextLine(const char* texture_id, const char* font_id, const char* text);
	void destroyTextures(std::vector<std::string> & texturesID);

private:
	std::map<std::string, SDL_Texture*> m_textureMap;
	std::map<std::string, TTF_Font*> fonts;
	SDL_Renderer* m_renderer;
};

#endif
