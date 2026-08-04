#include "ControlsViewGameState.h"

ControlsViewGameState::ControlsViewGameState()
{
	
}

ControlsViewGameState::~ControlsViewGameState()
{
	
}

void ControlsViewGameState::Initialise()
{
	//Create title
	m_controlsTitle = new GameObjectWithSpriteAndText("sprites/menus/keyboard.png", sf::Vector2f(0.2f, 0.2f), sf::Color::White,
		"fonts/8-BIT WONDER.ttf", "Controls Menu", 75, sf::Color::Blue, GameObjectWithSpriteAndText::RIGHT);
	//Initialise the title object
	m_controlsTitle->Initialise();
	//Add the title to the game object list
	m_GameObjects.push_back(m_controlsTitle);
	//Set the title position
	m_controlsTitle->SetPosition(1920 * 0.5f - m_controlsTitle->getBoundingRect().width * 0.5f, 50 + m_controlsTitle->getBoundingRect().height);

	//Create controls overview sprite
	m_controlsOverview = new GameObjectWithSprite("sprites/menus/controlsoverview.png", sf::Color::White, sf::Vector2f(1, 1), false);
	//Initialise
	m_controlsOverview->Initialise();
	//Add to game objects list
	m_GameObjects.push_back(m_controlsOverview);
	//Position
	m_controlsOverview->SetPosition(1920 * 0.5f, 1080 * 0.5f);

	//Create return to options button
	m_returnToOptions = new GameObjectWithText("fonts/8-BIT WONDER.ttf", "Press BACK to return to Options", sf::Color::White, 50);
	//Initialise
	m_returnToOptions->Initialise();
	//Add to game objects
	m_GameObjects.push_back(m_returnToOptions);
	//Position
	m_returnToOptions->SetPosition(1920 * 0.5f, 1080 - 50);
}

void ControlsViewGameState::Update()
{
	GameState::Update();


	if (pInputDevice->GetButtonInput(E_DigitalInput_Back).OnPressed())
	{
		pGameStateManager->QueuePop();
	}
}




