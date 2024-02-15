#pragma once
#include <list>
#include <vector>
#include "manager.h"

//�O���錾;
class player;
class playerShotBase;
struct shotPatternData;
class gameMainManager;
class playerManager;
class enemyManager;

struct shotData;


class playerShotManager:public manager{

	std::list<playerShotBase*> shots;//�e�̎���;
	
	std::vector<shotPatternData*> shotPD;//�e�̎�ޕʃf�[�^;
	int shotsCnt;//�ʂ̎�ސ�;

	//�֐��Ăяo���p;
	gameMainManager* ptrGameMain;
	playerManager* ptrPlayerManager;
	enemyManager* ptrEnemyManager;

public:
	playerShotManager(gameMainManager* ptrGM);
	~playerShotManager();

	errorData* Awake() override;
	bool Update()override;
	void Print() override;

	bool Add(shotData* data);
	const player* GetPlayer()const;
	bool CheckEnemyHit(shotData* s, int radius);

	shotPatternData* GetShotPatternData(int ptr);
};