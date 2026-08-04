#ifndef _TEXT_H
#define _TEXT_H

#include "SFML/Graphics.hpp"

class Text : public sf::Text
{
public:

	Text();
	~Text() override;

	void Initialise(const char* fontfilename, std::string text, int charsize, sf::Color textcolor);

	void setHighlighted(bool isHighlighted) { m_isHighlighted = isHighlighted; }
	bool isHighlighted() { return m_isHighlighted; }

	void changeText(std::string newtext) { setString(newtext); }

	//Text highlighting
	sf::Color m_highlightFillColor = sf::Color(225, 0, 0);
	sf::Color m_highlightOutlineColor = sf::Color(255,255,0);

	sf::Color m_normalFillColor;
	sf::Color m_normalOutlineColor;

protected:
	bool m_isHighlighted = false;
	bool m_Initialised;

};

#endif
