#include "GameStateTest.h"




GameStateTest::GameStateTest()
{
	
}

GameStateTest::~GameStateTest()
{
	
}

void GameStateTest::Initialise()
{

	//////////////////////////////////////////////////
	///TileMap Object
	/////////////////////////////////////////////////

	GameObjectWithTileMap* pTileMap1 = new GameObjectWithTileMap();
	pTileMap1->Initialise();
	pTileMap1->setPosition(1920.0f / 2.0f, 1080.0f / 2.0f);
	pTileMap1->LoadFromFile("levels/BackgroundMap.txt");
	m_GameObjects.push_back(pTileMap1);

	//////////////////////////////////////////
	///TEXT OBJECTS
	//////////////////////////////////////////

	//Create text objects
	helloText = new GameObjectWithText("fonts/8-BIT WONDER.ttf",
															"Hello",
															sf::Color::Green, 80);

	goodbyeText = new GameObjectWithText("fonts/wendy.ttf",
															"Goodbye",
															sf::Color::Blue, 100);

	//Initialise the text objects
	helloText->Initialise();
	goodbyeText->Initialise();

	//Add the text objects to the game object list
	m_GameObjects.push_back(helloText);
	m_GameObjects.push_back(goodbyeText);

	//Set the text object positions
	helloText->SetPosition(300.f, 200.f);
	goodbyeText->SetPosition(300.f, 100.f);

	/////////////////////////////////////////////
	///SPRITE OBJECTS
	/////////////////////////////////////////////
	
	//Create sprite objects
	hudSprite = new GameObjectWithSprite("sprites/HUD/spr_hud_face_raff_0.png",
																sf::Color::Green, sf::Vector2f(3.f,3.f), true);	

	//Initialise sprite objects
	hudSprite->Initialise();

	//Add the sprite objects to the game object list
	m_GameObjects.push_back(hudSprite);

	//Set the sprite object positions
	hudSprite->SetPosition(sf::Vector2f(1000,500));

	//Create CollectibleFactory
	CollectibleFactory* collectible_factory = new CollectibleFactoryImplementation;
	std::array<CollectibleItem*, 10> titems{};
	std::array<int,10> titemtype = { 0,1,2,0,1,2,0,1,2,0 };
	std::array<sf::Vector2f, 10> titempos{ sf::Vector2f(200.0f,200.0f),sf::Vector2f(300.0f,200.0f) ,
										 sf::Vector2f(400.0f,200.0f),sf::Vector2f(500.0f,200.0f) ,
										 sf::Vector2f(600.0f,200.0f) ,sf::Vector2f(700.0f,200.0f),
										 sf::Vector2f(800.0f,200.0f) ,sf::Vector2f(900.0f,200.0f) ,
										 sf::Vector2f(200.0f,400.0f),sf::Vector2f(200.0f,400.0f) };



	

	//////////////////////////////////////////////
	///SPRITE OBJECTS WITH TEXT
	//////////////////////////////////////////////
	
	//Create GameObjectWithSpriteAndText
	hudAndText = new GameObjectWithSpriteAndText("sprites/HUD/spr_hud_face_raff_0.png",
																				sf::Vector2f(1,1),sf::Color::White,
																				"fonts/wendy.ttf",
																				"Sprite Text",
																				50, sf::Color::Blue, GameObjectWithSpriteAndText::TOP);

	//Initialise sprite with text objects
	hudAndText->Initialise();

	//Add the sprite with text objects to the game object list
	m_GameObjects.push_back(hudAndText);

	//Set sprite with text objects positions
	hudAndText->SetPosition(sf::Vector2f(500, 500));

	//////////////////////////////////////////////////
	///Animated Sprite object
	/////////////////////////////////////////////////
	
	//Create GameObjectWithAnimatedSprite
	animatedSprite = new GameObjectWithAnimatedSprite("sprites/spritesheet_test.png", 
																					6, 256, 256, true, 10,
																						sf::Color::White, sf::Vector2f(1, 1), true);
	//Initialise animated sprite object
	animatedSprite->Initialise();
	//Set the position of the animated sprite
	animatedSprite->SetPosition(800, 400);
	//Add the object to the game object list
	m_GameObjects.push_back(animatedSprite);

	//////////////////////////////////////////////////
	///Enemies
	/////////////////////////////////////////////////

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

	//////////////////////////////////////////////////
	///Player Sprite object
	/////////////////////////////////////////////////

	//Create Player
	playerSprite = new Player();
	//Initialise player sprite object
	playerSprite->Initialise();
	//Add the object to the game object list
	m_GameObjects.push_back(playerSprite);

	//Create Collectible ---- 0 = Ammo, 1 = Health, 2 = Speed
	for (int i = 0; i < titems.size(); i++)
	{
		CollectibleItem* titem = collectible_factory->MakeCollectible(titemtype[i]);
		titem->Initialise();
		titem->SetPosition(titempos[i]);
		//Add Collecible to Array
		titems[i] = titem;
	}

	for (auto& titem : titems)
	{
		m_GameObjects.push_back(titem);
	}

	//Create HUD
	m_HUD = new HUD();
	m_HUD->Initialise();
	m_GameObjects.push_back(m_HUD);

	//////////////////////////////////////////////////
	///Camera object
	/////////////////////////////////////////////////

	this->m_Camera = new GameObjectWithCamera();
	this->m_Camera->Initialise();
	m_GameObjects.push_back(this-> m_Camera);
}

void GameStateTest::Update()
{
	//Animated Sprite movement (only use ONE of the options - digital or analogue)

	//DIGITAL DPAD MOVEMENT
	//NO LONGER REQUIRED HERE, MOVED CODE TO PLAYER CLASS
	//Move left
	//if (pInputDevice->GetButtonInput(E_DigitalInput_DpadLeft).IsDown())
		//playerSprite->SetPosition(playerSprite->GetPosition().x - movementSpeed, playerSprite->GetPosition().y);
	//Move right
	//if (pInputDevice->GetButtonInput(E_DigitalInput_DpadRight).IsDown())
		//playerSprite->SetPosition(playerSprite->GetPosition().x + movementSpeed, playerSprite->GetPosition().y);
	//Move up
	//if (pInputDevice->GetButtonInput(E_DigitalInput_DpadUp).IsDown())
		//playerSprite->SetPosition(playerSprite->GetPosition().x , playerSprite->GetPosition().y - movementSpeed);
	//Move down
	//if (pInputDevice->GetButtonInput(E_DigitalInput_DpadDown).IsDown())
		//playerSprite->SetPosition(playerSprite->GetPosition().x , playerSprite->GetPosition().y + movementSpeed);

	//NO LONGER FUNCTIONAL (COMMENTED OUT IN THE KEYBOARDANDMOUSEINPUTDEVICE.CPP)
	////ANALOGUE LSTICK MOVEMENT
	////Move left/right
	//if (pInputDevice->GetAnalogueInput(E_AnalogueInput_ThumbLX).GetValue() != 0.f)
	//	playerSprite->SetPosition(playerSprite->GetPosition().x + movementSpeed * pInputDevice->GetAnalogueInput(E_AnalogueInput_ThumbLX).GetValue(), playerSprite->GetPosition().y);
	//if (pInputDevice->GetAnalogueInput(E_AnalogueInput_ThumbLY).GetValue() != 0.f)
	//	playerSprite->SetPosition(playerSprite->GetPosition().x, playerSprite->GetPosition().y + movementSpeed * pInputDevice->GetAnalogueInput(E_AnalogueInput_ThumbLY).GetValue());

	//Mouse movement testing
	//if (pInputDevice->GetAnalogueInput(E_AnalogueInput_ThumbRX).GetValue() != 0.f)
	//	playerSprite->SetPosition(playerSprite->GetPosition().x + movementSpeed * pInputDevice->GetAnalogueInput(E_AnalogueInput_ThumbRX).GetValue(), playerSprite->GetPosition().y);
	//if (pInputDevice->GetAnalogueInput(E_AnalogueInput_ThumbRY).GetValue() != 0.f)
	//	playerSprite->SetPosition(playerSprite->GetPosition().x, playerSprite->GetPosition().y + movementSpeed * pInputDevice->GetAnalogueInput(E_AnalogueInput_ThumbRY).GetValue());


	// Get the player's position
	sf::Vector2f playerPos = playerSprite->GetPosition();

	// Call TileIndexAtPosition to determine the tile index
	for (auto gameObject : m_GameObjects)
	{
		GameObjectWithTileMap* tileMapObject = dynamic_cast<GameObjectWithTileMap*>(gameObject);
		if (tileMapObject)
		{
			tileMapObject->TileIndexAtPosition(playerPos);
		}
	}

	//Highlight testing
	//Mouse
	sf::Vector2f mouseScreenPos = pInputDevice->getPointerPos();
	//Convert to world space using player as a reference
	sf::Vector2f worldCentre = playerSprite->GetPosition();
	sf::Vector2f screenCentre = sf::Vector2f(pWindowManager->GetWindow()->getSize().x * 0.5f, pWindowManager->GetWindow()->getSize().y * 0.5f);
	int offsetX = worldCentre.x - screenCentre.x;
	int offsetY = worldCentre.y - screenCentre.y;
	sf::Vector2f mouseWorldPos = sf::Vector2f(mouseScreenPos.x + offsetX, mouseScreenPos.y + offsetY);

	if (hudAndText->getBoundingRect().contains(mouseWorldPos))
		hudAndText->setHighlighted(true);
	else
		hudAndText->setHighlighted(false);

	//hudAndText->setHighlighted(true);

	//Change game state to main menu if debug change game state is pressed
	if (pInputDevice->GetButtonInput(E_DigitalInput_DebugChangeGameState).OnPressed())
	{
		//Create main menu game state
		mainMenu = new MainMenuGameState();
		//Queue main menu state
		pGameStateManager->QueueGameState(mainMenu);
	}

	//HUD Testing - DEBUG BUTTONS TO INCREASE/DECREASE PLAYER STATS
	//Cast to player to access health, maxhealth, score
	int health = dynamic_cast<Player*>(playerSprite)->getCurrentHealth();
	int maxHealth = dynamic_cast<Player*>(playerSprite)->getMaxHealth();
	int score = dynamic_cast<Player*>(playerSprite)->getScore();

	//Health increase
	if (pInputDevice->GetButtonInput(E_DigitalInput_DebugIncreaseHealth).OnPressed())
	{
		dynamic_cast<Player*>(playerSprite)->increaseHealth();
	}
	//Health Decrease
	if (pInputDevice->GetButtonInput(E_DigitalInput_DebugDecreaseHealth).OnPressed())
	{
		dynamic_cast<Player*>(playerSprite)->reduceHealth();
	}
	//Score Increase
	if (pInputDevice->GetButtonInput(E_DigitalInput_DebugIncreaseScore).OnPressed())
	{
		dynamic_cast<Player*>(playerSprite)->increaseScore(100);
	}
	//Score Decrease
	if (pInputDevice->GetButtonInput(E_DigitalInput_DebugDecreaseScore).OnPressed())
	{
		dynamic_cast<Player*>(playerSprite)->decreaseScore(100);
	}
	//Max Health increase
	if (pInputDevice->GetButtonInput(E_DigitalInput_DebugIncreaseMaxHealth).OnPressed())
	{
		dynamic_cast<Player*>(playerSprite)->increaseMaxHealth();
	}
	//Max Health decrease
	if (pInputDevice->GetButtonInput(E_DigitalInput_DebugDecreaseMaxHealth).OnPressed())
	{
		dynamic_cast<Player*>(playerSprite)->reduceMaxHealth();
		//Reduce current health if it was the same as max health
		if (health == maxHealth)
			dynamic_cast<Player*>(playerSprite)->reduceHealth();
	}


	GameState::Update();
}
