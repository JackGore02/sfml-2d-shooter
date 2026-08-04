#pragma once
#include "../../Engine/Core/GameObject.h"
#include "../../Engine/Physics/BoxCollider2D.h"
#include "../../Engine/Renderer/AnimatedSprite.h"

class GameObjectWithAnimatedSprite : public GameObject, public BoxCollider2D
{
public:
	GameObjectWithAnimatedSprite(const char* filename, int numberOfFrames, int frameWidth, int frameHeight, bool isLooped, int fps, sf::Color color, sf::Vector2f m_scale, bool destructible);

	void Initialise() override;
	void Update() override;
	sf::Vector2f GetPosition() override;
	void SetPosition(float px, float py) override;
	void SetPosition(sf::Vector2f ppos) override;
	void GetPosition(float& x, float& y) override;

	void OnCollision(Collider2D* pCollider2D) override;
	bool m_isDestructible = false;

protected:
	AnimatedSprite m_AnimatedSprite;
	std::vector<sf::IntRect> m_frames;
	std::vector<sf::Vector2f> m_origins;

	const char* m_filename;
	int m_numberOfFrames;
	int m_frameWidth;
	int m_frameHeight;
	bool m_isLooped;
	int m_fps;
	sf::Color m_color;
	sf::Vector2f m_scale;

};

