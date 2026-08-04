#ifndef _GAME_DATA_MANAGER_H
#define _GAME_DATA_MANAGER_H

#include <map>

struct SpritesheetDef;
struct TilemapDef;

class GameDataManager
{
public:
	GameDataManager();
	~GameDataManager();

	static void Initialise();

	void AddSpritesheetDef(const char* filename, SpritesheetDef* pSpritesheetDef);
	void AddTilemapDef(const char* filename, TilemapDef* pTilemapDef);
	SpritesheetDef* GetSpritesheetDef(const char* filename);
	TilemapDef* GetTilemapDef(const char* filename);

	bool LoadSpritesheetDefFromFile(const char* filename);
	bool LoadTilemapDefFromFile(const char* filename);

private:

	std::map<int, SpritesheetDef*> m_SpritesheetDefs;
	std::map<int, TilemapDef*> m_Tilemapdefs;

};

#endif
