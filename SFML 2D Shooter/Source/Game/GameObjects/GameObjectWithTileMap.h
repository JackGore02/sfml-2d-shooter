#pragma once

#include <SFML\Graphics.hpp>
#include "../../Engine/Core/GameObject.h"
#include "../../Game/GameData/GameDataManager.h"

#include "GameObjectWithAnimatedSprite.h"
#include "GameObjectWithSprite.h"


#include <iostream>
#include <fstream>

#include "../../Engine/Renderer/RenderManager.h"
#include "../../Engine/System/Assets/AssetManager.h"
#include "../../Engine/System/Context/SysContextProvider.h"
#include "../GameData/TilemapDef.h"


class GameObjectWithTileMap : public GameObject, public sf::Drawable, public sf::Transformable
{
public:
	GameObjectWithTileMap();
	~GameObjectWithTileMap() override;

public:
	void GetPosition(float& px, float& py) override;
	sf::Vector2f GetPosition() override;
	void SetPosition(float px, float py) override;
	void SetPosition(sf::Vector2f ppos) override;

	bool LoadFromTileMapDef(SpritesheetDef* pTilemapDef, const int* tiles, unsigned int width, unsigned int height);
	void LoadFromFile(std::string pmapname);

	void TileIndexAtPosition(sf::Vector2f playerPos);

	void Initialise() override;
	void Update() override;

	void setLevelData(TilemapLevelDef pdef);
	TilemapLevelDef getLevelData();

protected:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	sf::VertexArray m_Vertices;
	sf::Texture* m_pTileSet;
	int* m_pMap;

	int tileTypeIndex[256];

	TilemapLevelDef m_TileMapLevelDef;
};

