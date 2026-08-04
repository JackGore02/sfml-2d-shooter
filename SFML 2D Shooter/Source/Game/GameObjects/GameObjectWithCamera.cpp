#include "GameObjectWithCamera.h"

#include "../../Engine/Renderer/WindowManager.h"
#include "../../Engine/System/Context/SysContextProvider.h"
#include "../../Engine/System/GameState/GameState.h"
#include "../../Engine/System/GameState/GameStateManager.h"

class WindowManager;

GameObjectWithCamera::GameObjectWithCamera()
{
}


GameObjectWithCamera::~GameObjectWithCamera()
{
	RemoveCamera();
}

void GameObjectWithCamera::Initialise()
{
	WindowManager* pWindowManager = C_SysContext::Get<WindowManager>();
	m_View = pWindowManager->GetWindow()->getDefaultView();
}

void GameObjectWithCamera::Update()
{
	if (m_Active)
	{
		WindowManager* pWindowManager = C_SysContext::Get<WindowManager>();
		pWindowManager->GetWindow()->setView(m_View);
	}

	auto* pGameStateManager = C_SysContext::Get<GameStateManager>();
	GameState* pCurrentGameState = pGameStateManager->GetCurrentGameState();
	GameObject* pPlayer = pCurrentGameState->GetPlayer();

	if (pPlayer)
	{
		this->SetPosition(pPlayer->GetPosition());
	}
	if (this->m_Active)
	{
		this->SetAsCurrentCamera();
	}
}

void GameObjectWithCamera::SetAsCurrentCamera()
{
	m_Active = true;
	WindowManager* pWindowManager = C_SysContext::Get<WindowManager>();
	pWindowManager->GetWindow()->setView(m_View);
}

void GameObjectWithCamera::RemoveCamera()
{
	WindowManager* pWindowManager = C_SysContext::Get<WindowManager>();
	pWindowManager->GetWindow()->setView(m_View);

	m_Active = false;
}

sf::Vector2f GameObjectWithCamera::GetPosition()
{
	return m_View.getCenter();
}

void GameObjectWithCamera::GetPosition(float& px, float& py)
{
	m_View.setCenter(px, py);
}

void GameObjectWithCamera::SetPosition(sf::Vector2f ppos)
{
	m_View.setCenter(ppos);
}


void GameObjectWithCamera::SetPosition(float px, float py)
{
	m_View.setCenter(px, py);
}
