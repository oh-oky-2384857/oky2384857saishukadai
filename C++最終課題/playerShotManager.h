#pragma once
#include <list>
#include <vector>
#include "manager.h"

//前方宣言;
class player;
class playerShotBase;
struct shotPatternData;
class gameMainManager;
class playerManager;
class enemyManager;

struct shotData;


class playerShotManager:public manager{

	std::list<playerShotBase*> shots;//弾の実体;
	
	std::vector<shotPatternData*> shotPD;//弾の種類別データ;
	int shotsCnt;//玉の種類数;

	//関数呼び出し用;
	gameMainManager* ptrGameMain;
	playerManager* ptrPlayerManager;
	enemyManager* ptrEnemyManager;

public:
	playerShotManager(gameMainManager* ptrGM);
	~playerShotManager();

	bool Awake() override;
	bool Update()override;
	void Print() override;

	bool Add(shotData* data);
	const player* GetPlayer()const;
	bool CheckEnemyHit(shotData* s, int radius);

	shotPatternData* GetShotPatternData(int ptr);
};