#pragma once
#include <list>
#include <vector>
#include "manager.h"

//�O���錾;
class player;
class playerShot;
struct shotPatternData;
class gameMainManager;
class playerManager;
class enemyManager;

struct shotData;
struct shotInputData;


class playerShotManager:public manager{

	std::list<playerShot*> shots;//�e�̎���;
	
	std::vector<shotPatternData*> shotPD;//�e�̎�ޕʃf�[�^;
	int shotsCnt;//�ʂ̎��;

	int shotCoolTimeCnt;//�e���˂̗�p���Ԃ̃J�E���^;

	shotPatternData* nowShotData;//���ݔ��˂���e�f�[�^;

	//�֐��Ăяo���p;
	gameMainManager* ptrGameMain;
	playerManager* ptrPlayerManager;
	enemyManager* ptrEnemyManager;

	//���͎󂯎��;
	shotInputData* shotInput;

public:
	playerShotManager(gameMainManager* ptrGM);
	~playerShotManager();

	bool Awake() override;
	bool Update()override;
	void Print() override;

	bool Add(shotData* data);
	const player* GetPlayer()const;
	bool CheckEnemyHit(shotData* s, int radius);

	
};