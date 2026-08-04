#include "EndScreenGameState.h"

EndScreenGameState::EndScreenGameState()
{

}

EndScreenGameState::~EndScreenGameState()
{

}

void EndScreenGameState::Initialise()
{
	//Title
	//Create text object depending on win state
	std::string titletext;
	if (m_wonGame)
		titletext = "Congratulations! You have won the game!";
	else
		titletext = "YOU DIED!";
	m_endGameTitle = new GameObjectWithText("fonts/pf_arma_five.ttf",
											titletext,
											sf::Color::White, 75);
	//Initialise the text object
	m_endGameTitle->Initialise();
	//Add the title to the game object list
	m_GameObjects.push_back(m_endGameTitle);
	//Set the title position
	m_endGameTitle->SetPosition(1920 * 0.5f, 200);


	//Score display
	m_scoreDisplay = new GameObjectWithText("fonts/pf_arma_five.ttf",
	                                        "Your Score: " + std::to_string(m_score),
	                                        sf::Color::White, 50);
	m_scoreDisplay->Initialise();
	m_GameObjects.push_back(m_scoreDisplay);
	m_scoreDisplay->SetPosition(1920 * 0.5f, 500);

	//Time display
	m_scoreDisplay = new GameObjectWithText("fonts/pf_arma_five.ttf",
		"Time: " + std::to_string(pGameStateManager->m_gameTimer),
		sf::Color::White, 50);
	m_scoreDisplay->Initialise();
	m_GameObjects.push_back(m_scoreDisplay);
	m_scoreDisplay->SetPosition(1920 * 0.5f, 575);


	//Return to main menu button
	m_returnToMenuButton = new GameObjectWithSpriteAndText("sprites/menus/exit.png", sf::Vector2f(0.4f, 0.4f), sf::Color::White, "fonts/pf_arma_five.ttf",
		"Exit to Main Menu", 50, sf::Color::Blue, GameObjectWithSpriteAndText::LEFT);
	m_returnToMenuButton->Initialise();
	m_GameObjects.push_back(m_returnToMenuButton);
	m_returnToMenuButton->SetPosition(1920 * 0.5f + 200, 800);
}

void EndScreenGameState::Update()
{
	GameState::Update();
	bool startPressed = pInputDevice->GetButtonInput(E_DigitalInput_Start).OnPressed();
	bool backPressed = pInputDevice->GetButtonInput(E_DigitalInput_Back).OnPressed();
	bool leftTriggerPressed = pInputDevice->GetAnalogueInput(E_AnalogueInput_LeftTrigger).GetValue() > 0.f;

	if (m_returnToMenuButton->getBoundingRect().contains(pInputDevice->getPointerPos()))
		m_returnToMenuButton->setHighlighted(true);
	else
		m_returnToMenuButton->setHighlighted(false);


	if (startPressed || backPressed || (m_returnToMenuButton->getBoundingRect().contains(pInputDevice->getPointerPos()) && leftTriggerPressed))
	{
		if (m_level == 1)
			pGameStateManager->EmptyQueue(2);
		else if (m_level == 2)
			pGameStateManager->EmptyQueue(3);
	}
}
