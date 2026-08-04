#include "GameDataManager.h"
#include "../../Engine/Core/Types.h"
#include "SpritesheetDef.h"
#include "TilemapDef.h"

#include <tinyxml2.h>

GameDataManager::GameDataManager()
= default;

GameDataManager::~GameDataManager()
= default;

void GameDataManager::Initialise()
{

}

void GameDataManager::AddSpritesheetDef(const char* filename, SpritesheetDef* pSpritesheetDef)
{
	C_Hash32 filenameHash(filename);

	if (m_SpritesheetDefs.find(filenameHash.GetHashValue()) != m_SpritesheetDefs.end())
		return;

	m_SpritesheetDefs[filenameHash.GetHashValue()] = pSpritesheetDef;
}

void GameDataManager::AddTilemapDef(const char* filename, TilemapDef* pTilemapDef)
{
	C_Hash32 filenameHash(filename);

	if (m_Tilemapdefs.find(filenameHash.GetHashValue()) != m_Tilemapdefs.end())
	return;

	m_Tilemapdefs[filenameHash.GetHashValue()] = pTilemapDef;
}


SpritesheetDef* GameDataManager::GetSpritesheetDef(const char* filename)
{
	C_Hash32 filenameHash(filename);

	const auto iter = m_SpritesheetDefs.find(filenameHash.GetHashValue());
	
	if (iter != m_SpritesheetDefs.end())
		return iter->second;

	if (LoadSpritesheetDefFromFile(filename))
	{
		return GetSpritesheetDef(filename);
	}

	return nullptr;
}

TilemapDef* GameDataManager::GetTilemapDef(const char* filename)
{
	C_Hash32 filenameHash(filename);

	const auto iter = m_Tilemapdefs.find(filenameHash.GetHashValue());

	if (iter != m_Tilemapdefs.end())
		return iter->second;

	if (LoadTilemapDefFromFile(filename))
	{
		return GetTilemapDef(filename);
	}

	return nullptr;
}


bool GameDataManager::LoadTilemapDefFromFile(const char* filename)
{
	tinyxml2::XMLDocument doc;

	if (doc.LoadFile(filename) != tinyxml2::XMLError::XML_SUCCESS)
		return false;

	tinyxml2::XMLElement* pTextureAtlas = doc.FirstChildElement("TextureAtlas");

	if (pTextureAtlas)
	{
		auto* pTilemapDef = new TilemapDef();

		//extract attributes from TextureAtlas
		for (const tinyxml2::XMLAttribute* attribute = pTextureAtlas->FirstAttribute(); attribute; attribute = attribute->Next())
		{
			if (strcmp(attribute->Name(), "imagePath") == 0)
			{
				pTilemapDef->m_Filename = attribute->Value();
			}
			else if (strcmp(attribute->Name(), "width") == 0)
			{
				pTilemapDef->m_Width = attribute->IntValue();
			}
			else if (strcmp(attribute->Name(), "height") == 0)
			{
				pTilemapDef->m_Height = attribute->IntValue();
			}
		}

		//loop through sprites
		for (tinyxml2::XMLNode* ele = pTextureAtlas->FirstChild(); ele; ele = ele->NextSibling())
		{
			TilemapLevelDef tilemapLevelDef;

			//extract attributes from sprite
			for (const tinyxml2::XMLAttribute* attribute = ((tinyxml2::XMLElement*)ele)->FirstAttribute(); attribute; attribute = attribute->Next())
			{
				if (strcmp(attribute->Name(), "n") == 0)
				{
					tilemapLevelDef.m_Name = attribute->Value();
				}
				else if (strcmp(attribute->Name(), "x") == 0)
				{
					tilemapLevelDef.m_PosX = attribute->IntValue();
				}
				else if (strcmp(attribute->Name(), "y") == 0)
				{
					tilemapLevelDef.m_PosY = attribute->IntValue();
				}
				else if (strcmp(attribute->Name(), "w") == 0)
				{
					tilemapLevelDef.m_Width = attribute->IntValue();
				}
				else if (strcmp(attribute->Name(), "h") == 0)
				{
					tilemapLevelDef.m_Height = attribute->IntValue();
				}
				else if (strcmp(attribute->Name(), "pX") == 0)
				{
					tilemapLevelDef.m_PivotX = attribute->FloatValue();
				}
				else if (strcmp(attribute->Name(), "pY") == 0)
				{
					tilemapLevelDef.m_PivotY = attribute->FloatValue();
				}
				else if (strcmp(attribute->Name(), "oX") == 0)
				{
					tilemapLevelDef.m_OffsetX = static_cast<float>(attribute->IntValue());
				}
				else if (strcmp(attribute->Name(), "oY") == 0)
				{
					tilemapLevelDef.m_OffsetY = static_cast<float>(attribute->IntValue());
				}
				else if (strcmp(attribute->Name(), "oW") == 0)
				{
					tilemapLevelDef.m_OriginalWidth = attribute->IntValue();
				}
				else if (strcmp(attribute->Name(), "oH") == 0)
				{
					tilemapLevelDef.m_OriginalHeight = attribute->IntValue();
				}
				else if (strcmp(attribute->Name(), "r") == 0)
				{
					tilemapLevelDef.m_Rotated = true;
				}
			}

			pTilemapDef->m_pTilemapDefs.push_back(tilemapLevelDef);
		}

		AddTilemapDef(filename, pTilemapDef);

		return true;

	}

	return false;
}


bool GameDataManager::LoadSpritesheetDefFromFile(const char* filename)
{
	tinyxml2::XMLDocument doc;

	if (doc.LoadFile(filename) != tinyxml2::XMLError::XML_SUCCESS)
		return false;

	tinyxml2::XMLElement* pTextureAtlas = doc.FirstChildElement("TextureAtlas");

	if (pTextureAtlas)
	{
		auto* pSpritesheetDef = new SpritesheetDef();

		//extract attributes from TextureAtlas
		for (const tinyxml2::XMLAttribute* attribute = pTextureAtlas->FirstAttribute(); attribute; attribute = attribute->Next())
		{
			if (strcmp(attribute->Name(), "imagePath") == 0)
			{
				pSpritesheetDef->m_Filename = attribute->Value();
			}
			else if (strcmp(attribute->Name(), "width") == 0)
			{
				pSpritesheetDef->m_Width = attribute->IntValue();
			}
			else if (strcmp(attribute->Name(), "height") == 0)
			{
				pSpritesheetDef->m_Height = attribute->IntValue();
			}
		}

		//loop through sprites
		for (tinyxml2::XMLNode* ele = pTextureAtlas->FirstChild(); ele; ele = ele->NextSibling())
		{
			SpritesheetSpriteDef spritesheetSpriteDef;

			//extract attributes from sprite
			for (const tinyxml2::XMLAttribute* attribute = ((tinyxml2::XMLElement*)ele)->FirstAttribute(); attribute; attribute = attribute->Next())
			{
				if(strcmp(attribute->Name(), "n") == 0)
				{
					spritesheetSpriteDef.m_Name = attribute->Value();
				}
				else if (strcmp(attribute->Name(), "x") == 0)
				{
					spritesheetSpriteDef.m_PosX = attribute->IntValue();
				}
				else if (strcmp(attribute->Name(), "y") == 0)
				{
					spritesheetSpriteDef.m_PosY = attribute->IntValue();
				}
				else if (strcmp(attribute->Name(), "w") == 0)
				{
					spritesheetSpriteDef.m_Width = attribute->IntValue();
				}
				else if (strcmp(attribute->Name(), "h") == 0)
				{
					spritesheetSpriteDef.m_Height = attribute->IntValue();
				}
				else if (strcmp(attribute->Name(), "pX") == 0)
				{
					spritesheetSpriteDef.m_PivotX = attribute->FloatValue();
				}
				else if (strcmp(attribute->Name(), "pY") == 0)
				{
					spritesheetSpriteDef.m_PivotY = attribute->FloatValue();
				}
				else if (strcmp(attribute->Name(), "oX") == 0)
				{
					spritesheetSpriteDef.m_OffsetX = static_cast<float>(attribute->IntValue());
				}
				else if (strcmp(attribute->Name(), "oY") == 0)
				{
					spritesheetSpriteDef.m_OffsetY = static_cast<float>(attribute->IntValue());
				}
				else if (strcmp(attribute->Name(), "oW") == 0)
				{
					spritesheetSpriteDef.m_OriginalWidth = attribute->IntValue();
				}
				else if (strcmp(attribute->Name(), "oH") == 0)
				{
					spritesheetSpriteDef.m_OriginalHeight = attribute->IntValue();
				}
				else if (strcmp(attribute->Name(), "r") == 0)
				{
					spritesheetSpriteDef.m_Rotated = true;
				}					
			}

			pSpritesheetDef->m_pSpriteDefs.push_back(spritesheetSpriteDef);
		}

		AddSpritesheetDef(filename, pSpritesheetDef);

		return true;

	}

	return false;
}
