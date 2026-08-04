#pragma once
#include "../../Engine/Core/GameObject.h"
#include "../../Engine/UI/Text.h"

class GameObjectWithText : public GameObject
{
public:
	//Constructor
	GameObjectWithText(const char* fontFileName, std::string text, sf::Color textColor, int charSize);

	//Public member functions
	void Initialise() override;
	void Update() override;

	//Get/Set functions
	void GetPosition(float& x, float& y) override;
	sf::Vector2f GetPosition() override;
	void SetPosition(float px, float py) override;
	void SetPosition(sf::Vector2f ppos) override;
	void setHighlighted(bool isHighlighted) { m_Text.setHighlighted(isHighlighted); }
	bool isHighlighted() { return m_isHighlighted; }

	void changeText(std::string newtext) { m_Text.changeText(newtext); }

private:
	Text m_Text;

	int m_charSize;
	const char* m_fontFileName;
	std::string m_textContents;
	sf::Color m_textColor;
	bool m_isHighlighted = false;


};

