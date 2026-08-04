#pragma once
#include "../../Engine/Core/GameObject.h"
#include "../../Engine/Physics/BoxCollider2D.h"
#include "../../Engine/Renderer/RenderManager.h"
#include "../../Engine/Renderer/Sprite.h"

class GameObjectWithSprite : public GameObject, public BoxCollider2D
{
public:
	//Constructor
	GameObjectWithSprite(const char* spriteFileName, sf::Color spriteColor, sf::Vector2f spriteScale, bool isDestructible);

	//Public member functions
	void Initialise() override;
	void Update() override;

	//Get/Set Position
	void GetPosition(float& x, float& y) override;
	sf::Vector2f GetPosition() override;
	void SetPosition(float px, float py) override;
	void SetPosition(sf::Vector2f ppos) override;

	void OnCollision(Collider2D* pCollider2D) override;
	bool m_isDestructible;

	void SetHUDObject(bool value);
	bool IsHUDObject() const;

	void ChangeSprite(const char* newSpriteFileName);

private:
	Sprite m_Sprite;

	sf::Color m_spriteColor;
	const char* m_spriteFileName;
	sf::Vector2f m_spriteScale;
	

	//Setting as HUD objects
	bool m_isHUD;
};

