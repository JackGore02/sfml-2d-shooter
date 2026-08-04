#pragma once
#include <iostream>
#include "GameObjectWithSprite.h"

class CollectibleItem : public GameObject, public BoxCollider2D 
{
public:
	CollectibleItem() {};
	virtual ~CollectibleItem() {}

	/*
	void awardItem(Player* pplayer)
	{
		//player->addA(this->a)
	}
	*/
	std::string get_Type();
	void Update() override;
	sf::Vector2f GetPosition() override;
	void SetPosition(float px, float py) override;
	void SetPosition(sf::Vector2f ppos) override;
	void GetPosition(float& x, float& y) override;
	void Initialise() override;


protected:
	std::string _type;
	std::string _texturepath;
	float a;
	float b;
	float c;

	Sprite m_sprite;
};


