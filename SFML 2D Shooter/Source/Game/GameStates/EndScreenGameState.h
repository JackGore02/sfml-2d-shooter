#pragma once
#include "../../Engine/System/GameState/GameState.h"
#include "../GameObjects/GameObjectWithText.h"
#include "../../Engine/System/Context/SysContextProvider.h"
#include "../../Engine/Input/InputManager.h"
#include "../../Engine/Input/InputDevice.h"
#include "../../Engine/System/GameState/GameStateManager.h"

//Objects
#include "../GameObjects/GameObjectWithSpriteAndText.h"
#include "../GameObjects/GameObjectWithSprite.h"
#include "../GameObjects/GameObjectWithText.h"

class EndScreenGameState : public GameState
{
public:
	//Constructor and Destructor
	EndScreenGameState();
	~EndScreenGameState();

	//Public member functions
	void Initialise() override;
	void Update() override;
	GameObject* GetPlayer() override { return nullptr; }
	void setDidWin(bool didWin) { m_wonGame = didWin; }
	void setScore(int score) { m_score = score; }
	void setLevelReached(int level) { m_level = level; }

private:
	//Input device
	InputManager* pInputManager = C_SysContext::Get<InputManager>();
	InputDevice* pInputDevice = pInputManager->GetInputDevice();

	//Game State manager
	GameStateManager* pGameStateManager = C_SysContext::Get<GameStateManager>();

	GameObjectWithText* m_endGameTitle;
	GameObjectWithSpriteAndText* m_returnToMenuButton;
	GameObjectWithText* m_scoreDisplay;
	GameObjectWithText* m_timeDisplay;

	bool m_wonGame;
	int m_score;
	int m_level;

};

