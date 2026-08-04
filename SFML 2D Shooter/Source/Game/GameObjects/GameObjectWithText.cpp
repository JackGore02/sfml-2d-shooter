#include "GameObjectWithText.h"

GameObjectWithText::GameObjectWithText(const char* fontFileName, std::string text, sf::Color textColor, int charSize)
{
	m_fontFileName = fontFileName;
	m_textContents = text;
	m_textColor = textColor;
	m_charSize = charSize;
}

void GameObjectWithText::Initialise()
{
	m_Text.Initialise(m_fontFileName, m_textContents, m_charSize, m_textColor);
	m_Text.setOrigin(m_Text.getLocalBounds().width / 2, m_Text.getLocalBounds().height / 2);
}

void GameObjectWithText::Update()
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

void GameObjectWithText::GetPosition(float& x, float& y)
{
	x = m_Text.getPosition().x;
	y = m_Text.getPosition().y;
}

sf::Vector2f GameObjectWithText::GetPosition()
{
	return m_Text.getPosition();
}

void GameObjectWithText::SetPosition(float px, float py)
{
	m_Text.setPosition(px, py - m_charSize / 2); //fixing y pos displacement bug
}

void GameObjectWithText::SetPosition(sf::Vector2f ppos)
{
	m_Text.setPosition(ppos.x, ppos.y - m_charSize / 2); //fixing y pos displacement bug
}
