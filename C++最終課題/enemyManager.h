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

enum class enemyType {
	none,
	e001,
};



class enemyManager:public manager {
private:
	std::list<enemy*>enemys;

	std::vector<enemyData*>datas;

	//�֐��Ăяo���p;
	playerManager* ptrPlayerManager;
	gameMainManager* ptrGameMain;

	int enemyTypeAmount;//�G���;
public:
	enemyManager(gameMainManager* ptrGM);
	~enemyManager();

	bool Awake();
	bool Update();
	void Print();

	bool Add(enemyType et, coordinate pos);

	const player* GetPlayerPtr()const;
	inline playerManager* GetPlayerManagerPtr() {return ptrPlayerManager;}
};