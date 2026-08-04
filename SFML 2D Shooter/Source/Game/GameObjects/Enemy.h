#pragma once
#include "../../Engine/Core/GameObject.h"
#include "../../Engine/Renderer/AnimatedSprite.h"
#include "GameObjectWithSprite.h"
class Enemy :
    public GameObject, public BoxCollider2D
{
public:
    Enemy();
    ~Enemy();

public:
    virtual void Initialise() override;
    virtual void Update() override;
    virtual void GetPosition(float& x, float & y) override;
    virtual sf::Vector2f GetPosition() override;
    virtual void SetPosition(float px, float py) override;
    virtual void SetPosition(sf::Vector2f ppos) override;

    void OnCollision(Collider2D* pCollider2D) override;

public:
    AnimatedSprite m_AnimatedSprite;
private:
    enum E_AnimationState
    {
        E_Idle = 0,
        E_Walk = 1,
        E_Death = 2
    };

    float m_attackCooldownRamaining;
    const float m_attackCooldown = 1.5f;

    
};

