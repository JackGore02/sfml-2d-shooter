#ifndef _SPRITE_H
#define _SPRITE_H

#include <SFML/Graphics.hpp>

class TextureManager;

class Sprite : public sf::Sprite
{
public: 
	Sprite();
	~Sprite() override;

	void Initialise(const char* filename, sf::Color spriteColor, sf::Vector2f spriteScale);

private:

	bool m_bInitialised;

	bool isHUDObject;
};

#endif
