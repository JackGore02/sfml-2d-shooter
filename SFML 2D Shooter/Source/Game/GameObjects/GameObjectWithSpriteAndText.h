#pragma once
#include "../../Engine/Core/GameObject.h"
#include "../../Engine/Renderer/Sprite.h"
#include "../../Engine/UI/Text.h"

class GameObjectWithSpriteAndText : public GameObject
{
public:
	enum TextPosition
	{
		LEFT,
		RIGHT,
		TOP,
		BOTTOM
	};
	
	GameObjectWithSpriteAndText(const char* spriteFileName, sf::Vector2f spriteScale, sf::Color spriteColor, const char* fontFileName, std::string text, int charSize, sf::Color textColor, TextPosition textJustification);

	//Public member functions
	void Initialise() override;
	void Update() override;

	//Get/Set Position
	void GetPosition(float& x, float& y) override;
	sf::Vector2f GetPosition() override;
	void SetPosition(float px, float py) override;
	void SetPosition(sf::Vector2f ppos) override;
	void setHighlighted(bool isHighlighted) { m_Text.setHighlighted(isHighlighted); }
	sf::FloatRect getBoundingRect() { return m_Text.getGlobalBounds(); }

private:
	Text m_Text;
	Sprite m_Sprite;

	sf::Vector2f m_position;

	//Sprite Parameters
	const char* m_spriteFileName;
	sf::Vector2f m_spriteScale;
	sf::Color m_spriteColor;

	//Text Parameters
	const char* m_fontFileName;
	int m_textCharSize;
	std::string m_textContents;
	sf::Color m_textColor;

	//Text position relative to sprite
	TextPosition m_TextPos;
};

