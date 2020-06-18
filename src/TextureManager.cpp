#include <iostream>
#include "TextureManager.h"

TextureManager::~TextureManager()
{
	for (auto it = m_textureMap.begin(); it != m_textureMap.end(); it++)
	{
		SDL_DestroyTexture(it->second);
	}
	for (auto it = fonts.begin(); it != fonts.end(); it++)
	{
		TTF_CloseFont (it->second);
	}
}

bool TextureManager::loadTexture(const char* path, const char* texture_id)
{
	SDL_Surface* loadSurface = IMG_Load(path);
	if (loadSurface == NULL)
	{
		std::cout << "Texture " <<  path << "loading failed!" << std::endl;
		return false;
	}

	SDL_Texture* newTexture = NULL;
	newTexture = SDL_CreateTextureFromSurface(m_renderer, loadSurface);
	SDL_FreeSurface(loadSurface);

	if (newTexture != 0)
	{
		m_textureMap[texture_id] = newTexture;
		return true;
	}

	std::cerr << "newTexture = null" << std::endl;
	return false;
}

void TextureManager::draw(const char* texture_id, const SDL_Rect * src, const SDL_Rect * dst)
{
	SDL_RenderCopy(m_renderer, m_textureMap[texture_id], src, dst);
}


bool TextureManager::loadFont(const char* path, const char* font_id, int fontSize)
{
	TTF_Font* font = TTF_OpenFont(path, fontSize);
	if (font == NULL)
	{
		std::cerr << "Error load font" << std::endl;
		return false;
	}

	fonts.emplace(font_id, font);
	return true;
}

bool TextureManager::updateTextLine(const char* texture_id, const char* font_id, const char* text)
{

	SDL_Color color = { 0, 0, 0 };  // this is the color in rgb format, maxing out all would give you the color white, and it will be your text's color
	SDL_Surface* surfaceMessage = TTF_RenderText_Blended(fonts[font_id], text, color); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first
	if (surfaceMessage == nullptr)
	{
		std::cerr << TTF_GetError() << std::endl;
		std::cerr << "Surface for text line: " << texture_id << "update failed!" << std::endl;
		return false;
	}
	SDL_Texture* Message = SDL_CreateTextureFromSurface(m_renderer, surfaceMessage); //now you can convert it into a texture

	SDL_FreeSurface(surfaceMessage); // free your surface and texture

	if (Message == nullptr)
	{
		std::cerr << "Texture of text line: " << texture_id << "update failed!" << std::endl;
		return false;
	}

	m_textureMap[texture_id] = Message;
	return true;

}

void TextureManager::destroyTextures(std::vector<std::string>& texturesID)
{
	for (auto it = texturesID.begin(); it != texturesID.end(); it++)
	{
		if (m_textureMap.count(it->c_str()))
		{
			SDL_DestroyTexture(m_textureMap[it->c_str()]);
			m_textureMap.erase(it->c_str());
		}
		else if (fonts.count(it->c_str()))
		{
			TTF_CloseFont(fonts[it->c_str()]);
			fonts.erase(it->c_str());
		}
	}
}






