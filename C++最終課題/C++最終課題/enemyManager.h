#pragma once
#include <list>
#include <vector>
#include "manager.h"
#include "enemyData.h"

//前方宣言;
class enemy;

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

	//関数呼び出し用;
	playerManager* ptrPlayerManager;
	gameMainManager* ptrGameMain;

	int enemyTypeAmount;//敵種類;
public:
	enemyManager(gameMainManager* ptrGM);
	~enemyManager();

	bool Awake();
	bool Update();
	void Print();

	bool Add(enemyType et, coordinate pos);

	const coordinate GetPlayerPosition()const;
};