#include "HUD.h"

#include "../../Engine/Renderer/WindowManager.h"
#include "../Weapons/WeaponBase.h"

HUD::HUD()
{

}

HUD::~HUD()
{
	
}

void HUD::Initialise()
{
	//Get player character
	player = dynamic_cast<Player*>(pGameStateManager->GetCurrentGameState()->GetPlayer());

	//Get stats from player
	//Health and Max Health
	currentHealth = player->getCurrentHealth();
	currentMaxHealth = player->getMaxHealth();
	prevHealth = currentHealth;
	prevMaxHealth = currentMaxHealth;
	//Score
	score = player->getScore();
	prevScore = score;

	//Set up display objects
	windowSizeX = pWindowManager->GetWindow()->getSize().x;
	windowSizeY = pWindowManager->GetWindow()->getSize().y;

	//Health Display
	//Create heart outlines
	for (int i = 0; i < currentMaxHealth; i++)
	{
		GameObjectWithSprite* heartOutline = new GameObjectWithSprite("sprites/HUD/heartempty.png", sf::Color::White, sf::Vector2f(0.25f, 0.25f), false);
		heartOutline->Initialise();
		pGameStateManager->GetCurrentGameState()->AddGameObject(heartOutline);
		m_HeartOutlines.push_back(heartOutline);
	}
	//Create filled hearts
	for (int i = 0; i < currentHealth; i++)
	{
		GameObjectWithSprite* filledHeart = new GameObjectWithSprite("sprites/HUD/heartfilled.png",sf::Color::White,sf::Vector2f(0.25f,0.25f), false);
		filledHeart->Initialise();
		pGameStateManager->GetCurrentGameState()->AddGameObject(filledHeart);
		m_FilledHearts.push_back(filledHeart);
	}

	//Set positions of the health display
	for (int i = 0; i < m_HeartOutlines.size(); i++)
	{
		m_HeartOutlines[i]->SetPosition(50 + 100*i, 50);
	}
	for (int i = 0; i < m_FilledHearts.size(); i++)
	{
		m_FilledHearts[i]->SetPosition(50 + 100*i, 50);
	}

	//Score display
	//Set up score text to always show 5 digits (00000)
	std::string scoreText = "Score : ";
	if (score * 0.0001f >= 1.f)
		scoreText += std::to_string(score);
	else if (score * 0.001f >= 1.f)
		scoreText += "0" + std::to_string(score);
	else if (score * 0.01f >= 1.f)
		scoreText += "00" + std::to_string(score);
	else if (score * 0.1f >= 1.f)
		scoreText += "000" + std::to_string(score);
	else
		scoreText += "0000" + std::to_string(score);
	
	m_scoreDisplay = new GameObjectWithText("fonts/pf_arma_five.ttf", scoreText, sf::Color::White, 50);
	m_scoreDisplay->Initialise();
	pGameStateManager->GetCurrentGameState()->AddGameObject(m_scoreDisplay);
	//Position score display
	m_scoreDisplay->SetPosition(windowSizeX - 200, 50);

	//Weapon Display
	m_weaponDisplay = new GameObjectWithSprite(player->getWeapon()->getSpriteFile(), sf::Color::White,sf::Vector2f(3,3),false);
	m_weaponDisplay->Initialise();
	pGameStateManager->GetCurrentGameState()->AddGameObject(m_weaponDisplay);
	m_weaponDisplay->SetPosition(player->GetPosition().x - windowSizeX * 0.5f + 100, player->GetPosition().y + windowSizeY - 100);

	//Ammo display
	int clipAmmo = player->getWeapon()->GetClipAmmo();
	int totalAmmo = player->getWeapon()->GetTotalAmmo();
	std::string ammoText = "Ammo: [" + std::to_string(clipAmmo) + "/" + std::to_string(totalAmmo) + "]";

	m_ammoDisplay = new GameObjectWithText("fonts/pf_arma_five.ttf", ammoText, sf::Color::White, 40);
	m_ammoDisplay->Initialise();
	pGameStateManager->GetCurrentGameState()->AddGameObject(m_ammoDisplay);
	m_ammoDisplay->SetPosition(m_weaponDisplay->GetPosition() + sf::Vector2f(250, 10));

	//Timer display
	m_timerDisplay = new GameObjectWithText("fonts/pf_arma_five.ttf", std::to_string(pGameStateManager->m_gameTimer), sf::Color::White, 50);
	m_timerDisplay->Initialise();
	pGameStateManager->GetCurrentGameState()->AddGameObject(m_timerDisplay);
	m_timerDisplay->SetPosition(player->GetPosition().x, player->GetPosition().y - windowSizeY * 0.5f + 50);
}

void HUD::Update()
{
	//Update the health
	currentHealth = player->getCurrentHealth();
	//If the health has changed, update display
	//If health has increased, add another filled heart
	if (currentHealth > prevHealth)
	{
		//Create new heart
		GameObjectWithSprite* filledHeart = new GameObjectWithSprite("sprites/HUD/heartfilled.png", sf::Color::White, sf::Vector2f(0.25f, 0.25f), false);
		filledHeart->Initialise();
		pGameStateManager->GetCurrentGameState()->AddGameObject(filledHeart);
		//Add to vector
		m_FilledHearts.push_back(filledHeart);
	}
	//Health has decreased, remove the last heart
	else if (currentHealth < prevHealth)
	{
		//Delete the last heart in the vector of hearts
		pGameStateManager->GetCurrentGameState()->RemoveGameObject(m_FilledHearts[prevHealth - 1]);
		//Resize vector
		m_FilledHearts.pop_back();
	}

	//Update max health
	currentMaxHealth = player->getMaxHealth();
	//If the max health has changed, add a new heart outline
	if (currentMaxHealth > prevMaxHealth)
	{
		//Max health increased, add a new outline slot
		GameObjectWithSprite* heartOutline = new GameObjectWithSprite("sprites/HUD/heartempty.png", sf::Color::White, sf::Vector2f(0.25f, 0.25f), false);
		heartOutline->SetHUDObject(true);
		heartOutline->Initialise();
		pGameStateManager->GetCurrentGameState()->AddGameObject(heartOutline);
		m_HeartOutlines.push_back(heartOutline);
	}
	else if (currentMaxHealth < prevMaxHealth)
	{
		//Max health decreased, remove an outline slot
		pGameStateManager->GetCurrentGameState()->RemoveGameObject(m_HeartOutlines[prevMaxHealth - 1]);
		//Resize vector
		m_HeartOutlines.pop_back();
	}

	//Update score
	score = player->getScore();
	//If the score has changed, update the score
	if (score != prevScore)
	{
		std::string scoreText = "Score : ";
		if (score * 0.0001f >= 1.f)
			scoreText += std::to_string(score);
		else if (score * 0.001f >= 1.f)
			scoreText += "0" + std::to_string(score);
		else if (score * 0.01f >= 1.f)
			scoreText += "00" + std::to_string(score);
		else if (score * 0.1f >= 1.f)
			scoreText += "000" + std::to_string(score);
		else
			scoreText += "0000" + std::to_string(score);

		m_scoreDisplay->changeText(scoreText);
	}

	//Update previous values
	prevHealth = currentHealth;
	prevMaxHealth = currentMaxHealth;
	prevScore = score;

	//Update the weapon display
	m_weaponDisplay->ChangeSprite(player->getWeapon()->getSpriteFile());

	//Update ammo display
	int clipAmmo = player->getWeapon()->GetClipAmmo();
	int totalAmmo = player->getWeapon()->GetTotalAmmo();
	std::string ammoText = "Ammo: [" + std::to_string(clipAmmo) + "/" + std::to_string(totalAmmo) + "]";
	m_ammoDisplay->changeText(ammoText);

	//Update the timer
	m_timerDisplay->changeText(std::to_string(pGameStateManager->m_gameTimer));


	//Set position of each HUD element relative to the player
	//Set positions of the health display
	for (int i = 0; i < m_HeartOutlines.size(); i++)
	{
		m_HeartOutlines[i]->SetPosition(player->GetPosition().x - windowSizeX * 0.5f + 50 + 100 * i, player->GetPosition().y - windowSizeY * 0.5f + 50);
	}
	for (int i = 0; i < m_FilledHearts.size(); i++)
	{
		m_FilledHearts[i]->SetPosition(player->GetPosition().x - windowSizeX * 0.5f + 50 + 100 * i, player->GetPosition().y - windowSizeY * 0.5f + 50);
	}
	//Set position of the score display
	m_scoreDisplay->SetPosition(player->GetPosition().x + windowSizeX * 0.5f - 200, player->GetPosition().y - windowSizeY * 0.5f + 50);

	//Set position of the weapon display
	m_weaponDisplay->SetPosition(player->GetPosition().x - windowSizeX * 0.5f + 100, player->GetPosition().y + windowSizeY * 0.5f - 50);
	//Set the position of the ammo display
	m_ammoDisplay->SetPosition(m_weaponDisplay->GetPosition() + sf::Vector2f(250, 10));
	//Set the position of the timer display
	m_timerDisplay->SetPosition(player->GetPosition().x, player->GetPosition().y - windowSizeY * 0.5f + 50);
}

sf::Vector2f HUD::GetPosition()
{
	//Return the position of the player, since the HUD should be centered there
	return player->GetPosition();
}

void HUD::GetPosition(float& x, float& y)
{
	//Return the position of the player, since the HUD should be centered there
	x = player->GetPosition().x;
	y = player->GetPosition().y;
}

void HUD::SetPosition(float px, float py)
{
}

void HUD::SetPosition(sf::Vector2f ppos)
{

}



