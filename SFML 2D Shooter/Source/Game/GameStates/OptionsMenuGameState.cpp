#include "OptionsMenuGameState.h"

OptionsMenuGameState::OptionsMenuGameState()
{

}

OptionsMenuGameState::~OptionsMenuGameState()
{

}

void OptionsMenuGameState::Initialise()
{
	//Create title
	m_optionsTitle = new GameObjectWithSpriteAndText("sprites/menus/cogwheel.png", sf::Vector2f(0.2f, 0.2f),sf::Color::White, 
		"fonts/8-BIT WONDER.ttf", "Options Menu",75, sf::Color::Blue,GameObjectWithSpriteAndText::RIGHT);

	//Initialise the title object
	m_optionsTitle->Initialise();

	//Add the title to the game object list
	m_GameObjects.push_back(m_optionsTitle);

	//Set the title position
	m_optionsTitle->SetPosition(1920 * 0.5f - m_optionsTitle->getBoundingRect().width * 0.5f, 50 + m_optionsTitle->getBoundingRect().height);

	//Create menu Items
	m_controlsButton = new GameObjectWithSpriteAndText("sprites/menus/keyboard.png", sf::Vector2f(0.2f, 0.2f), sf::Color::White, "fonts/pf_arma_five.ttf",
		"Controls", 50, sf::Color::Green, GameObjectWithSpriteAndText::RIGHT);
	m_returnToMenuButton = new GameObjectWithSpriteAndText("sprites/menus/exit.png", sf::Vector2f(0.4f, 0.4f), sf::Color::White, "fonts/pf_arma_five.ttf",
		"Exit to Main Menu", 50, sf::Color::Blue, GameObjectWithSpriteAndText::LEFT);
	//Initialise
	m_controlsButton->Initialise();
	m_returnToMenuButton->Initialise();
	//Add the objects to list of game objects
	m_GameObjects.push_back(m_controlsButton);
	m_GameObjects.push_back(m_returnToMenuButton);
	//Add the objects to list of menu items
	m_menuItems.push_back(m_controlsButton);
	m_menuItems.push_back(m_returnToMenuButton);
	//Position the buttons
	m_controlsButton->SetPosition(700, 400);
	m_returnToMenuButton->SetPosition(1200, 550);

	if (wasGamePlaying)
	{
		//Create return to game button
		m_returnToGameButton = new GameObjectWithSpriteAndText("sprites/menus/playbutton.png", sf::Vector2f(0.2f, 0.2f), sf::Color::White, "fonts/pf_arma_five.ttf",
			"Back to Game", 50, sf::Color::Green, GameObjectWithSpriteAndText::RIGHT);
		//Initialise
		m_returnToGameButton->Initialise();
		//Add to list of game objects
		m_GameObjects.push_back(m_returnToGameButton);
		//Add to list of menu items
		m_menuItems.push_back(m_returnToGameButton);
		//Position
		m_returnToGameButton->SetPosition(700, 700);
	}	
	//Set highlight index to -1 by default
	m_highlightIndex = -1;
}

void OptionsMenuGameState::Update()
{
	GameState::Update();

	//Check for pInputDevice button presses
	bool startPressed = pInputDevice->GetButtonInput(E_DigitalInput_Start).OnPressed();
	bool backPressed = pInputDevice->GetButtonInput(E_DigitalInput_Back).OnPressed();
	bool leftTriggerPressed = pInputDevice->GetAnalogueInput(E_AnalogueInput_LeftTrigger).GetValue() != 0.f;

	//If Start (X on keyboard) pressed  or left trigger (mouse clicked) while controls is selected, go to controls state
	if ((startPressed || leftTriggerPressed) && m_highlightIndex == 0)
	{
		//Create controls view game state
		auto* controlsView = new ControlsViewGameState();
		//Queue the game state
		pGameStateManager->QueueGameState(controlsView);
	}

	//If Start pressed or left trigger (mouse clicked) while Return to main menu is selected,  return to the main menu game state
	if ((startPressed || leftTriggerPressed) && m_highlightIndex == 1)
	{
		//If was game playing, remove the last 2 game states from queue (i.e. the options menu and the gameplay state), which should therefore return to main menu
		if (wasGamePlaying)
			pGameStateManager->EmptyQueue(2);
		//Otherwise, options was accessed from main menu, so just pop the options menu
		else
			pGameStateManager->QueuePop();
	}

	//If Start pressed, or left trigger (mouse clicked), or if back button pressed, while back to game option is selected, just pop the options menu
	if (wasGamePlaying && (((startPressed || leftTriggerPressed) && m_highlightIndex == 2) || backPressed))
	{
		pGameStateManager->QueuePop();
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