#pragma once

#include "../../Engine/System/Context/SysContextProvider.h"
#include "../../Engine/System/GameState/GameState.h"
#include "../../Engine/System/GameState/GameStateManager.h"
#include "../../Engine/Renderer/RenderManager.h"

//Game Objects
#include "Player.h"
#include "GameObjectWithSprite.h"
#include "GameObjectWithText.h"
#include "GameObjectWithCamera.h"


class HUD : public GameObject
{
public:
	HUD();
	~HUD() override;

	void Update() override;
	void Initialise() override;
	sf::Vector2f GetPosition() override;
	void GetPosition(float& x, float& y) override;
	void SetPosition(float px, float py) override;
	void SetPosition(sf::Vector2f ppos) override;

private:

	//Game State manager
	GameStateManager* pGameStateManager = C_SysContext::Get<GameStateManager>();
	WindowManager* pWindowManager = C_SysContext::Get<WindowManager>();

	//Window size
	int windowSizeX;
	int windowSizeY;

	//Player
	Player* player;

	//Player stats
	int currentMaxHealth;
	int currentHealth;
	int prevMaxHealth;
	int prevHealth;
	int score;
	int prevScore;

	//Objects to display
	GameObjectWithText* m_scoreDisplay;
	std::vector<GameObjectWithSprite*> m_FilledHearts;
	std::vector<GameObjectWithSprite*> m_HeartOutlines;
	GameObjectWithSprite* m_weaponDisplay;
	GameObjectWithText* m_ammoDisplay;
	GameObjectWithText* m_timerDisplay;
};

