#pragma once

#include "../Game.h"
#include "../../Engine/System/GameState/GameState.h"
#include "../../Engine/System/GameState/GameStateManager.h"
#include "../../Engine/System/Context/SysContextProvider.h"
#include "../../Engine/Input/InputManager.h"
#include "../../Engine/Input/InputDevice.h"
#include <array>

//Game Objects
#include "../GameObjects/GameObjectWithText.h"
#include "../GameObjects/GameObjectWithSprite.h"
#include "../GameObjects/GameObjectWithSpriteAndText.h"
#include "../GameObjects/GameObjectWithAnimatedSprite.h"
#include "../GameObjects/GameObjectWithCamera.h"
#include "../GameObjects/GameObjectWithTileMap.h"
#include "../GameObjects/HUD.h"
#include "../GameObjects/Collectibles/CollectibleFactoryImplementation.h"
#include "../GameObjects/Enemy.h"

//Game States
#include "../GameObjects/Player.h"
#include "../GameStates/MainMenuGameState.h"

class GameStateTest : public GameState
{
public:
	//Constructor and Destructor
	GameStateTest();
	~GameStateTest();

	//Public member functions
	void Initialise() override;
	void Update() override;
	GameObject* GetPlayer() override { return playerSprite; }

private:
	//Input device
	InputManager* pInputManager = C_SysContext::Get<InputManager>();
	InputDevice* pInputDevice = pInputManager->GetInputDevice();

	//Game State manager
	GameStateManager* pGameStateManager = C_SysContext::Get<GameStateManager>();

	//Window manager
	WindowManager* pWindowManager = C_SysContext::Get<WindowManager>();

	//Text Objects
	GameObjectWithText* helloText;
	GameObjectWithText* goodbyeText;

	//Sprite Objects
	GameObjectWithSprite* hudSprite;

	GameObjectWithTileMap* pcollMap;

	//Sprite and Text objects
	GameObjectWithSpriteAndText* hudAndText;

	//Animated Sprite objects
	GameObjectWithAnimatedSprite* animatedSprite;

	//Player Sprite Objects
	GameObject* playerSprite;

	//Game States
	MainMenuGameState* mainMenu;

	//Game Camera
	GameObjectWithCamera* m_Camera;

	//HUD
	HUD* m_HUD;

};

// Tile Map Layout for desertLevel0
const int desertLevel0[] =
{
0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1,
1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0,
0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1,
1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0,
0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1,
1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0,
0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1,
1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0,
0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1,
1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0,
0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1,
1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0,
0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1,
1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0,
0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1,
1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0,
};