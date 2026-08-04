#include "LevelTwoGameState.h"

LevelTwoGameState::LevelTwoGameState()
{

}

LevelTwoGameState::~LevelTwoGameState()
{

}

void LevelTwoGameState::Initialise()
{
	GameObjectWithTileMap* pTileMap2 = new GameObjectWithTileMap();
	pTileMap2->Initialise();
	pTileMap2->LoadFromFile("levels/BackgroundMap.txt");
	pTileMap2->SetPosition(1920 * 0.5f, 1080 * 0.5f);
	m_GameObjects.push_back(pTileMap2);

	//Create text object
	m_text = new GameObjectWithText("fonts/8-BIT WONDER.ttf",
		"Level 2",
		sf::Color::White, 50);

	//Initialise the text object
	m_text->Initialise();
	//Add the text objects to the game object list
	m_GameObjects.push_back(m_text);
	//Set the text object positions
	m_text->SetPosition(1920 * 0.5f, 1080 * 0.5f);

	//Collectibles
	CollectibleFactory* collectible_factory = new CollectibleFactoryImplementation;
	std::array<CollectibleItem*, 20> titems{};
	std::array<int, 20> titemtype{};
	std::array<sf::Vector2f, 20> titempos{};
	//Randomly assign an item type and position for each item 0 = Ammo, 1 = Health, 2 = Speed
	srand(std::time(NULL));
	for (int i = 0; i < titems.size(); i++)
	{
		//Number from 0-2
		titemtype[i] = rand() % 3;
		//x and y between -2000 and +2000
		titempos[i] = sf::Vector2f(rand() % 2000 - 1000, rand() % 2000 - 1000);
	}
	//Create Collectibles
	for (int i = 0; i < titems.size(); i++)
	{
		CollectibleItem* titem = collectible_factory->MakeCollectible(titemtype[i]);
		titem->Initialise();
		titem->SetPosition(titempos[i]);
		//Add Collecible to Array
		titems[i] = titem;
	}
	//Add items to game objects list
	for (auto& titem : titems)
	{
		m_GameObjects.push_back(titem);
	}

	//Create Enemies
	std::array<Enemy*, 20> enemies{};
	for (int i = 0; i < enemies.size(); i++)
	{
		//Create GameObjectWithAnimatedSprite
		Enemy* enemy = new Enemy();
		//Initialise animated sprite object
		enemy->Initialise();
		//Set the position of the animated sprite randomly, x and y between +1000 and -1000
		enemy->SetPosition(rand() % 2000 - 1000, rand() % 2000 - 1000);
		//Add the object to the game object list
		m_GameObjects.push_back(enemy);
	}


	//DO LAST SO THEY ARE ON TOP OF THE WORLD LAYERS
	//Create player and get stats from previous level
	m_player = new Player();
	m_player->Initialise();
	m_player->setStats(dynamic_cast<Player*>(pGameStateManager->GetPreviousGameState()->GetPlayer())->getStats());
	m_GameObjects.push_back(m_player);

	//Create HUD
	m_HUD = new HUD();
	m_HUD->Initialise();
	m_GameObjects.push_back(m_HUD);

	//Camera
	this->m_Camera = new GameObjectWithCamera();
	this->m_Camera->Initialise();
	m_GameObjects.push_back(this->m_Camera);
}

void LevelTwoGameState::Update()
{
	GameState::Update();

	//Update the timer
	pGameStateManager->m_gameTimer += pFrameTimer->DeltaTime();

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

	//Go to end screen with WIN if debug f1 key is pressed or score reaches 2000
	if (pInputDevice->GetButtonInput(E_DigitalInput_DebugChangeGameState).OnPressed() || m_player->getScore() >= 2000)
	{
		//Create end screen game state
		EndScreenGameState* endScreen = new EndScreenGameState();
		//Let the end game state know the score and if the game was won or not
		//REPLACE WITH TAKING THIS INFO FROM PLAYER, PROBABLY IN ENDGAMESTATE ITSELF
		endScreen->setDidWin(true);
		endScreen->setScore(m_player->getScore());
		endScreen->setLevelReached(2);
		//Queue the end screen
		pGameStateManager->QueueGameState(endScreen);
	}

	//Go to end screen with LOSE if player goes to 0 health
	if (m_player->getCurrentHealth() <= 0)
	{
		//Create end screen game state
		EndScreenGameState* endScreen = new EndScreenGameState();
		//Let the end game state know the score
		endScreen->setDidWin(false);
		endScreen->setScore(m_player->getScore());
		endScreen->setLevelReached(2);
		//Queue the state
		pGameStateManager->QueueGameState(endScreen);
	}

	//HUD Testing - DEBUG BUTTONS TO INCREASE/DECREASE PLAYER STATS
	//Cast to player to access health, maxhealth, score
	int health = m_player->getCurrentHealth();
	int maxHealth = m_player->getMaxHealth();
	int score = m_player->getScore();

	//Health increase
	if (pInputDevice->GetButtonInput(E_DigitalInput_DebugIncreaseHealth).OnPressed())
	{
		m_player->increaseHealth();
	}
	//Health Decrease
	if (pInputDevice->GetButtonInput(E_DigitalInput_DebugDecreaseHealth).OnPressed())
	{
		m_player->reduceHealth();
	}
	//Score Increase
	if (pInputDevice->GetButtonInput(E_DigitalInput_DebugIncreaseScore).OnPressed())
	{
		m_player->increaseScore(100);
	}
	//Score Decrease
	if (pInputDevice->GetButtonInput(E_DigitalInput_DebugDecreaseScore).OnPressed())
	{
		m_player->decreaseScore(100);
	}
	//Max Health increase
	if (pInputDevice->GetButtonInput(E_DigitalInput_DebugIncreaseMaxHealth).OnPressed())
	{
		m_player->increaseMaxHealth();
	}
	//Max Health decrease
	if (pInputDevice->GetButtonInput(E_DigitalInput_DebugDecreaseMaxHealth).OnPressed())
	{
		m_player->reduceMaxHealth();
		//Reduce current health if it was the same as max health
		if (health == maxHealth)
			m_player->reduceHealth();
	}
}
