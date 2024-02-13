#pragma once
#include <list>
#include <vector>
#include "manager.h"
#include "enemyData.h"

//‘O•ûéŒ¾;
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

	//ŠÖ”ŒÄ‚Ño‚µ—p;
	playerManager* ptrPlayerManager;
	gameMainManager* ptrGameMain;

	int enemyTypeAmount;//“Gí—Ş;
public:
	enemyManager(gameMainManager* ptrGM);
	~enemyManager();

	bool Awake();
	bool Update();
	void Print();

	bool Add(enemyType et, coordinate pos);

	const coordinate GetPlayerPosition()const;
};