#pragma once

#include "../../Engine/Core/GameObject.h"
#include "../../Engine/Physics/BoxCollider2D.h"
#include "../../Engine/Renderer/AnimatedSprite.h"

class Bullet : public GameObject, public BoxCollider2D
{
public:
	Bullet();
	~Bullet() override;

	void Initialise() override;
	void Update() override;
	void GetPosition(float& x, float& y) override;
	sf::Vector2f GetPosition() override;
	void SetPosition(float px, float py) override;
	void SetPosition(sf::Vector2f ppos) override;
	void SetRotation(float angle);
	void SetScale(float scaleX, float scaleY);
	void OnCollision(Collider2D* pCollider2D) override;

private:
	AnimatedSprite m_AnimatedSprite;
	float m_Velocity;
	float m_Lifetime;
};

