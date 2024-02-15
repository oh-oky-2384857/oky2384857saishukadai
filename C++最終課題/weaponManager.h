#pragma once
#include <list>
#include "manager.h"

//‘O•ûéŒ¾;
class weapon;
class playerManager;
class gameMainManager;

class weaponManager :public manager{
private:
	std::list<weapon*> weapons;

	//ŠÖ”ŒÄ‚Ño‚µ—p;
	gameMainManager* ptrGameMain;
	playerManager* ptrPlayerManager;
public:
	weaponManager(gameMainManager* ptrGM);
	~weaponManager();

	bool Awake() override;
	bool Update()override;
	void Print() override;

	bool Add(coordinate pos, weaponData* d);
};