#pragma once
#include <list>
#include <vector>
#include "manager.h"
#include "enemyData.h"

//�O���錾;
class enemy;

class player;
class playerManager;
class gameMainManager;

struct shotData;

enum class enemyType {
	none,
	e001,
};


struct enemyWave {
	enemyType t;	
	int amount;
};

class enemyManager:public manager {
private:
	std::list<enemy*>enemys;//�G����;

	std::vector<enemyData*>datas;//�G�f�[�^;

	std::vector<std::vector<enemyWave*>> waves;//�E�F�[�u�f�[�^;

	int waveAmount;//�E�F�[�u��;
	int waveAddTime;//�G�E�F�[�u�ǉ��Ԋu;
	int enemyTypeAmount;//�G���;

	int enemyWaveAddCnt;//�G�ǉ��̃J�E���^;
	//�֐��Ăяo���p;
	playerManager* ptrPlayerManager;
	gameMainManager* ptrGameMain;

public:
	enemyManager(gameMainManager* ptrGM);
	~enemyManager();

	bool Awake() override;
	bool Update()override;
	void Print() override;

	bool Add(enemyType et, coordinate pos);

	const player* GetPlayerPtr()const;
	inline playerManager* GetPlayerManagerPtr() {return ptrPlayerManager;}

	/**
	�V���b�g���G�ɓ���������
	*@returns bool true:�ڐG,false:��ڐG;
	*/
	bool ShotCheckHitEnemy(shotData* s, int radius);
};