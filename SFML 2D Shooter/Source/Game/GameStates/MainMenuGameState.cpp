#include "MainMenuGameState.h"
#include "../Game.h"

MainMenuGameState::MainMenuGameState()
{

}

MainMenuGameState::~MainMenuGameState()
{

}

void MainMenuGameState::Initialise()
{
	//Game Title Text
	m_gameTitle = new GameObjectWithText("fonts/pf_arma_five.ttf",
		"RELIC SHOOTER!",
		sf::Color::Green, 150);
	//Initialise the text object
	m_gameTitle->Initialise();
	//Add the text objects to the game object list
	m_GameObjects.push_back(m_gameTitle);
	//Set the text object positions
	m_gameTitle->SetPosition(sf::Vector2f(1920.f * 0.5f, 150));

	//Create menu items
	m_startButton = new GameObjectWithSpriteAndText("sprites/menus/playbutton.png", sf::Vector2f(0.2f,0.2f), sf::Color::White, "fonts/pf_arma_five.ttf",
																					"Play Game!", 50, sf::Color::Green, GameObjectWithSpriteAndText::RIGHT);
	m_optionsButton = new GameObjectWithSpriteAndText("sprites/menus/cogwheel.png", sf::Vector2f(0.2f, 0.2f), sf::Color::White, "fonts/pf_arma_five.ttf",
																					"Settings", 50, sf::Color::Blue, GameObjectWithSpriteAndText::LEFT);
	m_exitButton = new GameObjectWithSpriteAndText("sprites/menus/exit.png", sf::Vector2f(0.4f, 0.4f), sf::Color::White, "fonts/pf_arma_five.ttf",
																					"Exit Game!", 50, sf::Color::Green, GameObjectWithSpriteAndText::RIGHT);
	//Initialise the menu items
	m_startButton->Initialise();
	m_optionsButton->Initialise();
	m_exitButton->Initialise();

	//Add the objects to list of game objects
	m_GameObjects.push_back(m_startButton);
	m_GameObjects.push_back(m_optionsButton);
	m_GameObjects.push_back(m_exitButton);

	//Add the objects to list of menu items
	m_menuItems.push_back(m_startButton);
	m_menuItems.push_back(m_optionsButton);
	m_menuItems.push_back(m_exitButton);

	//Position the buttons
	m_startButton->SetPosition(700, 400);
	m_optionsButton->SetPosition(1200, 550);
	m_exitButton->SetPosition(700, 700);

	//Set highlight index to -1 by default
	m_highlightIndex = -1;
}

void MainMenuGameState::Update()
{
	GameState::Update();
	//Change game state to game playing state if start key pressed (X on keyboard) while on the start game menu item
	bool startPressed = pInputDevice->GetButtonInput(E_DigitalInput_Start).OnPressed();
	bool leftTriggerPressed = pInputDevice->GetAnalogueInput(E_AnalogueInput_LeftTrigger).GetValue() != 0.f;

	if ((startPressed || leftTriggerPressed) && m_highlightIndex == 0)
	{
		m_highlightIndex = -1;
		//Create game playing game state if one doesn't already exist
		LevelOneGameState* level1 = new LevelOneGameState();
		//Queue the game playing game state
		pGameStateManager->QueueGameState(level1);
	}

	//Change game state to Options menu if start key pressed (X on keyboard) while on the options menu item
	if ((startPressed || leftTriggerPressed) && m_highlightIndex == 1)
	{
		m_highlightIndex = -1;
		//Create options menu game state if one doesn't already exist
		OptionsMenuGameState* optionsMenu = new OptionsMenuGameState();
		//Queue the options menu game state
		pGameStateManager->QueueGameState(optionsMenu);
	}

	//Pop out the main menu state if start key pressed (X on keyboard) while on the exit menu item
	if ((startPressed || leftTriggerPressed) && m_highlightIndex == 2)
	{
		m_highlightIndex = -1;
		pGameStateManager->exitGame();
	}
	
	//Menu Highlighting
	//Mouse
	//Set the highlight index to -1 if the mouse moves and is not hovering over an option
	//If it is hovering over an option, set the highlight index to that option
	if (pInputDevice->GetAnalogueInput(E_AnalogueInput_ThumbRX).GetValue() != 0.f || pInputDevice->GetAnalogueInput(E_AnalogueInput_ThumbRY).GetValue() != 0.f)
	{
		m_highlightIndex = -1;
		for (int i = 0; i < m_menuItems.size(); i++)
		{
			if (m_menuItems[i]->getBoundingRect().contains(pInputDevice->getPointerPos()))
				m_highlightIndex = i;
		}
	}

	//Keyboard
	if (pInputDevice->GetButtonInput(E_DigitalInput_DpadUp).OnPressed())
	{
		//If no menu item was previously highlighted, highlight the first one.
		if (m_highlightIndex == -1)
			m_highlightIndex = 0;
		//Otherwise, reduce the highlight index by 1 (move to the menu item above)
		//Set back to max if goes below 0
		else
		{
			m_highlightIndex--;
			if (m_highlightIndex < 0)
				m_highlightIndex = m_menuItems.size() - 1;
		}
	}

	if (pInputDevice->GetButtonInput(E_DigitalInput_DpadDown).OnPressed())
	{
		//If no menu item was previously highlighted, highlight the first one.
		if (m_highlightIndex == -1)
			m_highlightIndex = 0;
		//Otherwise, increase the highlight index by 1 (move to the menu item below)
		//Set back to 0 if goes above max
		else
		{
			m_highlightIndex++;
			m_highlightIndex = m_highlightIndex % m_menuItems.size();
		}
	}

	for (int i = 0; i < m_menuItems.size(); i++)
	{
		if (i == m_highlightIndex)
			m_menuItems[i]->setHighlighted(true);
		else
			m_menuItems[i]->setHighlighted(false);
	}
}