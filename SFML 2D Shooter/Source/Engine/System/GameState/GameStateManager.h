#ifndef _GAME_STATE_MANAGER_H
#define _GAME_STATE_MANAGER_H

#include <vector>
#include "../../Core/GameObject.h"

class GameState;

class GameStateManager
{
public:
	GameStateManager();
	~GameStateManager();

	static void Initialise();
	void Update();

	void QueueGameState(GameState* pGameState);
	void QueuePop();
	void EmptyQueue(int amountToRemove);
	
	GameState* GetCurrentGameState() { return m_GameStates.back(); }
	GameState* GetPreviousGameState() { return m_GameStates[m_GameStates.size() - 2]; }

	bool isExiting() { return this->m_isExiting; }
	void setExiting(bool pvalue) { this->m_isExiting = pvalue; }
	void exitGame() { this->setExiting(true); }

	float m_gameTimer = 0;

private:
	
	void PushGameState(GameState* pGameState);
	void PopGameState();

	std::vector<GameState*> m_GameStates;

	std::vector<GameState*> m_GameStateQueue;

	bool m_bPopGameState;
	bool m_isExiting = false;
	bool m_clearQueue = false;
	int m_statesToRemove = 0;

};

#endif
