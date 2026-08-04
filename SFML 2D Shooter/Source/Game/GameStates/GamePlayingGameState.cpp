#include "GamePlayingGameState.h"

GamePlayingGameState::GamePlayingGameState()
{

}

GamePlayingGameState::~GamePlayingGameState()
{

}

void GamePlayingGameState::Initialise()
{
	//Create text object
	m_text = new GameObjectWithText("fonts/8-BIT WONDER.ttf",
		"Game Playing Game State",
		sf::Color::White, 50);

	//Initialise the text object
	m_text->Initialise();

	//Add the text objects to the game object list
	m_GameObjects.push_back(m_text);

	//Set the text object positions
	m_text->SetPosition(1920 * 0.5f, 1080 * 0.5f);
}

void GamePlayingGameState::Update()
{
	GameState::Update();

	//Go to options menu if back key pressed (c on keyboard)
	if (pInputDevice->GetButtonInput(E_DigitalInput_Back).OnPressed())
	{
		//Create options menu game state
		OptionsMenuGameState* optionsMenu = new OptionsMenuGameState();
		//Let the options menu know it was from the game playing state
		optionsMenu->wasGamePlaying = true;
		//Queue the options menu
		pGameStateManager->QueueGameState(optionsMenu);
	}

	//Go to end screen if debug f1 key is pressed
	if (pInputDevice->GetButtonInput(E_DigitalInput_DebugChangeGameState).OnPressed())
	{
		//Create end screen game state
		EndScreenGameState* endScreen = new EndScreenGameState();
		//Let the end game state know the score and if the game was won or not
		//REPLACE WITH TAKING THIS INFO FROM PLAYER, PROBABLY IN ENDGAMESTATE ITSELF
		endScreen->setDidWin(true);
		endScreen->setScore(3000);
		//Queue the end screen
		pGameStateManager->QueueGameState(endScreen);
	}
}
