#include "GameObjectWithAnimatedSprite.h"

#include "Player.h"
#include "../Weapons/Bullet.h"
#include "../../Engine/System/GameState/GameState.h"
#include "../../Engine/System/GameState/GameStateManager.h"
#include "../../Engine/System/Context/SysContextProvider.h"

GameObjectWithAnimatedSprite::GameObjectWithAnimatedSprite(const char* filename, int numberOfFrames, int frameWidth, int frameHeight, bool isLooped, int fps, sf::Color color, sf::Vector2f scale, bool destructible)
{
	m_filename = filename;
	m_numberOfFrames = numberOfFrames;
	m_frameWidth = frameWidth;
	m_frameHeight = frameHeight;
	m_isLooped = isLooped;
	m_fps = fps;
	m_color = color;
	m_scale = scale;
	m_isDestructible = destructible;
}

sf::Vector2f GameObjectWithAnimatedSprite::GetPosition()
{
	return m_AnimatedSprite.getPosition();
}

void GameObjectWithAnimatedSprite::GetPosition(float& x, float& y)
{
	x = m_AnimatedSprite.getPosition().x;
	y = m_AnimatedSprite.getPosition().y;
}

void GameObjectWithAnimatedSprite::SetPosition(float px, float py)
{
	sf::Vector2f tpos = sf::Vector2f(px, py);
	m_AnimatedSprite.setPosition(tpos);
}

void GameObjectWithAnimatedSprite::SetPosition(sf::Vector2f ppos)
{
	m_AnimatedSprite.setPosition(ppos);
}

void GameObjectWithAnimatedSprite::Initialise()
{
	//Calculate the frame rectangle and origin for each frame
	for (int i = 0; i < m_numberOfFrames; i++)
	{
		sf::IntRect tspriteRect;
		sf::Vector2f tspriteOrigin;

		//Calculate sprite frame rectangle. Each frame always has top = 0, height and width = m_frameHeight and m_frameWidth. Left changes by 1+m_frameWidth each frame
		tspriteRect.left = 0 + (1 + m_frameWidth) * i;
		tspriteRect.top = 0;
		tspriteRect.height = m_frameHeight;
		tspriteRect.width = m_frameWidth;
		//Add the frame to the frames list
		m_frames.push_back(tspriteRect);

		//Calculate sprite frame origin. Each frame has y = 1/2 height, x = 1/2 width
		tspriteOrigin = sf::Vector2f(tspriteRect.width / 2.f, tspriteRect.height / 2.f);
		//Add the origin to the origin list
		m_origins.push_back(tspriteOrigin);
	}
	//Add the animation using the frame list and origin list
	m_AnimatedSprite.AddAnimation(1, m_filename, m_frames, m_origins, m_fps, m_isLooped);

	//Set as the current animation
	m_AnimatedSprite.SetCurrentAnimation(1);

	//Set the color of the sprite
	m_AnimatedSprite.setColor(m_color);

	//Set the scale of the sprite
	m_AnimatedSprite.setScale(m_scale);

	m_CollisionRect = m_AnimatedSprite.getGlobalBounds();
}

void GameObjectWithAnimatedSprite::Update()
{
	m_AnimatedSprite.Animate();

	m_CollisionRect = m_AnimatedSprite.getGlobalBounds();
}

void GameObjectWithAnimatedSprite::OnCollision(Collider2D* pCollider2D)
{

}
