#include "GameObjectWithSpriteAndText.h"

GameObjectWithSpriteAndText::GameObjectWithSpriteAndText(const char* spriteFileName, sf::Vector2f spriteScale, sf::Color spriteColor, const char* fontFileName, std::string text, int charSize, sf::Color textColor, TextPosition textJustification)
{
	//Sprite parameters
	m_spriteFileName = spriteFileName;
	m_spriteColor = spriteColor;
	m_spriteScale = spriteScale;

	//Text parameters
	m_fontFileName = fontFileName;
	m_textContents = text;
	m_textCharSize = charSize;
	m_textColor = textColor;
	m_TextPos = textJustification;
}

void GameObjectWithSpriteAndText::Initialise()
{
	m_Sprite.Initialise(m_spriteFileName, m_spriteColor, m_spriteScale);
	m_Text.Initialise(m_fontFileName, m_textContents, m_textCharSize, m_textColor);

	//Set the origins of the sprite and text to the centres of each
	m_Sprite.setOrigin(m_Sprite.getLocalBounds().width / 2, m_Sprite.getLocalBounds().height / 2);
	m_Text.setOrigin(m_Text.getLocalBounds().width / 2, m_Text.getLocalBounds().height / 2);
}

//All positions for GameObjectWithSpriteAndText will relate to the Sprite's position. Text is then placed according to the m_TextPos enum
sf::Vector2f GameObjectWithSpriteAndText::GetPosition()
{
	return m_Sprite.getPosition();
}

void GameObjectWithSpriteAndText::GetPosition(float& x, float& y)
{
	x = m_Sprite.getPosition().x;
	y = m_Sprite.getPosition().y;
}

void GameObjectWithSpriteAndText::SetPosition(float px, float py)
{
	sf::Vector2f tpos = sf::Vector2f(px, py);
	m_Sprite.setPosition(tpos);

	//Adjust the text position relative to the sprite, depending on the justification
	switch (m_TextPos)
	{
		case RIGHT:
		{
			m_Text.setPosition(m_Sprite.getPosition().x + m_Sprite.getGlobalBounds().width / 2 + m_Text.getLocalBounds().width / 2 + 20, m_Sprite.getPosition().y);
			break;
		}
		case LEFT:
		{
			m_Text.setPosition(m_Sprite.getPosition().x - m_Sprite.getGlobalBounds().width / 2 - m_Text.getLocalBounds().width / 2 - 20, m_Sprite.getPosition().y);
			break;
		}
		case TOP:
		{
			m_Text.setPosition(m_Sprite.getPosition().x, m_Sprite.getPosition().y - m_Sprite.getGlobalBounds().height / 2 - m_Text.getLocalBounds().height / 2 - 20);
			break;
		}
		case BOTTOM:
		{
			m_Text.setPosition(m_Sprite.getPosition().x, m_Sprite.getPosition().y + m_Sprite.getGlobalBounds().height / 2 + m_Text.getLocalBounds().height / 2 + 20);
			break;
		}
	}

	//Fix y pos bug
	m_Text.setPosition(m_Text.getPosition().x, m_Text.getPosition().y - m_textCharSize * 0.5f);
}

void GameObjectWithSpriteAndText::SetPosition(sf::Vector2f ppos)
{
	m_Sprite.setPosition(ppos);

	//Adjust the text position relative to the sprite, depending on the justification
	switch (m_TextPos)
	{
		case RIGHT:
		{
			m_Text.setPosition(m_Sprite.getPosition().x + m_Sprite.getGlobalBounds().width / 2 + m_Text.getLocalBounds().width / 2 + 20, m_Sprite.getPosition().y);
			break;
		}
		case LEFT:
		{
			m_Text.setPosition(m_Sprite.getPosition().x - m_Sprite.getGlobalBounds().width / 2 - m_Text.getLocalBounds().width / 2 - 20, m_Sprite.getPosition().y);
			break;
		}
		case TOP:
		{
			m_Text.setPosition(m_Sprite.getPosition().x, m_Sprite.getPosition().y - m_Sprite.getGlobalBounds().height / 2 - m_Text.getLocalBounds().height / 2 - 20);
			break;
		}
		case BOTTOM:
		{
			m_Text.setPosition(m_Sprite.getPosition().x, m_Sprite.getPosition().y + m_Sprite.getGlobalBounds().height / 2 + m_Text.getLocalBounds().height / 2 + 20);
			break;
		}
	}

	//Fix y pos bug
	m_Text.setPosition(m_Text.getPosition().x, m_Text.getPosition().y - m_textCharSize * 0.5f);
}

void GameObjectWithSpriteAndText::Update()
{
	if (m_Text.isHighlighted())
	{
		m_Text.setFillColor(m_Text.m_highlightFillColor);
		m_Text.setOutlineColor(m_Text.m_highlightOutlineColor);
	}
	else
	{
		m_Text.setFillColor(m_Text.m_normalFillColor);
		m_Text.setOutlineColor(m_Text.m_normalOutlineColor);
	}
}





