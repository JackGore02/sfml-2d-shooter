#include "GameObjectWithTileMap.h"

#include "Player.h"
#include "../GameData/SpritesheetDef.h"

class GameDataManager;

GameObjectWithTileMap::GameObjectWithTileMap()
{
}
GameObjectWithTileMap::~GameObjectWithTileMap()
{
	C_SysContext::Get<RenderManager>()->RemoveRenderObject(this);
}

bool GameObjectWithTileMap::LoadFromTileMapDef(SpritesheetDef* pTilemapDef, const int* tiles, unsigned width, unsigned height)
{
	this->setOrigin(1024.0f * 0.5f, 1024.0f * 0.5f);
	if (!pTilemapDef)
		return false;

	auto* pAssetManager = C_SysContext::Get<AssetManager>();
	m_pTileSet = &pAssetManager->GetTexture(pTilemapDef->m_Filename.c_str());

	std::vector<sf::IntRect> frames;
	for (auto& m_pTileMapDef : pTilemapDef->m_pSpriteDefs)
	{
		sf::IntRect rect(m_pTileMapDef.m_PosX, m_pTileMapDef.m_PosY, m_pTileMapDef.m_Width, m_pTileMapDef.m_Height);
		frames.push_back(rect);
	}

	int numTiles = 0;

	for (unsigned int i = 0; i < width * height; i++)
	{
		const unsigned int tilesNumber = tiles[i];
		if (tilesNumber < 0 || tilesNumber >= frames.size())
			continue;

		numTiles++;
	}
	m_Vertices.setPrimitiveType(sf::Quads);

	m_Vertices.resize(numTiles * 4);

	int quadNum = 0;
	for (unsigned int i = 0; i < width; ++i)
	{
		for (unsigned int j = 0; j < height; ++j)
		{
			const unsigned int tileNo = tiles[i + j * width];

			if (tileNo < 0 || tileNo >= frames.size())
				continue;

			const int tu1 = frames[tileNo].left;
			const int tv1 = frames[tileNo].top;
			const int tu2 = tu1 + frames[tileNo].width;
			const int tv2 = tv1 + frames[tileNo].height;

			const int tstartvertindex = quadNum * 4;
			sf::Vertex* quad = &m_Vertices[tstartvertindex];

			//define its 4 corners (Geometric Position)
			quad[0].position = sf::Vector2f(sf::Vector2f(i * frames[tileNo].width, j * frames[tileNo].height));
			quad[1].position = sf::Vector2f(sf::Vector2f((i + 1) * frames[tileNo].width, j * frames[tileNo].height));
			quad[2].position = sf::Vector2f(sf::Vector2f((i + 1) * frames[tileNo].width, (j + 1) * frames[tileNo].height));
			quad[3].position = sf::Vector2f(sf::Vector2f(i * frames[tileNo].width, (j + 1) * frames[tileNo].height));

			//define its 4 texture coordinates
			quad[0].texCoords = sf::Vector2f(sf::Vector2i(tu1, tv1));
			quad[1].texCoords = sf::Vector2f(sf::Vector2i(tu2, tv1));
			quad[2].texCoords = sf::Vector2f(sf::Vector2i(tu2, tv2));
			quad[3].texCoords = sf::Vector2f(sf::Vector2i(tu1, tv2));

			//Add to the total number of Tiles
			quadNum++;
		}
	}
	C_SysContext::Get<RenderManager>()->AddRenderObject(this);
	return true;
}

void GameObjectWithTileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// apply the transform to position the tile map
	states.transform *= getTransform();

	// apply the tile set texture to the shader
	states.texture = m_pTileSet;

	// draw teh vertex array
	target.draw(m_Vertices, states);
}

#include <iostream>
#include <fstream>
#include <sstream>

void GameObjectWithTileMap::LoadFromFile(std::string ptextfile)
{
	std::ifstream file{};
	file.open(ptextfile);

	if (!file.is_open())
	{
		char message[1024];
		strerror_s(message, 1024, errno);
		std::cerr << "Error: " << message;
		return;
	}

	//First Line is the SpriteSheet
	std::string tilemapdef;
	std::getline(file,tilemapdef);

	//First Line is the SpriteSheet
	std::string tdim;
	std::getline(file,tdim);

	//Second Line is the Map Dimensions
	std::istringstream iss(tdim);
	std::vector<std::string> ttokens;
	std::string token;
	while (iss >> token)
	{
		ttokens.push_back(token);		
	}
	
	const int t_mapW = stoi(ttokens[0]); //Width of the map
	const int t_mapH = stoi(ttokens[1]); //Height of the map

	auto pGDM = C_SysContext::Get<GameDataManager>();
	SpritesheetDef* pSSDef = pGDM->GetSpritesheetDef(tilemapdef.c_str());

	//read the file and store the value into our map
	m_pMap = new int[t_mapW * t_mapH];
	int tileinput;
	for (int i = 0; i < t_mapW * t_mapH; i++)
	{
			file >> tileinput;
			this->m_pMap[i] = tileinput;
			tileTypeIndex[i] = tileinput;
	}
	file.close();
	LoadFromTileMapDef(pSSDef, this->m_pMap, t_mapW, t_mapH);

}

sf::Vector2f GameObjectWithTileMap::GetPosition()
{
	return this->getPosition();
}

void GameObjectWithTileMap::GetPosition(float& px, float& py)
{
}

void GameObjectWithTileMap::Initialise()
{
	this->setOrigin(512.0f, 512.0f);
}

void GameObjectWithTileMap::SetPosition(float px, float py)
{
}

void GameObjectWithTileMap::SetPosition(sf::Vector2f ppos)
{
}


void GameObjectWithTileMap::Update()
{
}

void GameObjectWithTileMap::setLevelData(TilemapLevelDef pdef)
{
	this->m_TileMapLevelDef = pdef;
}

TilemapLevelDef GameObjectWithTileMap::getLevelData()
{
	return this->m_TileMapLevelDef;
}

void GameObjectWithTileMap::TileIndexAtPosition(sf::Vector2f playerPos)
{
	int tileX = playerPos.x / 64 - 7;
	int tileY = playerPos.y / 64;

	if (tileX >= 0 && tileX < 1024 && tileY >= 0 && tileY < 1024)
	{
		int tileIndex = m_pMap[tileX * 16 + tileY];
		std::cout << "Player is on tile with index: " << tileX << tileY << std::endl;
		for (int i = 0; i <= 25; i++)
		{
			std::cout << tileTypeIndex[i];
		}
	}
	else
	{
		std::cout << "Player is outside the bounds of the tile map." << std::endl;
	}
}
