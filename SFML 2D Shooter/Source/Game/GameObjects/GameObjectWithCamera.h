#pragma once

#include <SFML/Graphics.hpp>
#include "../../Engine/Core/GameObject.h"

class GameObjectWithCamera : public GameObject
{
public:
	GameObjectWithCamera();
	~GameObjectWithCamera();

public:
	sf::Vector2f GetPosition() override;
	void GetPosition(float& px, float& py) override;
	void SetPosition(float px, float py) override;
	void SetPosition(sf::Vector2f ppos) override;

	void SetAsCurrentCamera();
	void RemoveCamera();

	void Initialise() override;
	void Update() override;

protected:
	sf::View m_View;
	bool m_Active;
};

