#pragma once
#include <list>
#include "manager.h"

//前方宣言;
class weapon;
class playerManager;
class gameMainManager;
struct weaponData;

class weaponManager :public manager{
private:
	std::list<weapon*> weapons;

	//関数呼び出し用;
	gameMainManager* ptrGameMain;
	playerManager* ptrPlayerManager;
public:
	weaponManager(gameMainManager* ptrGM);
	~weaponManager();

	errorData* Awake() override;
	bool Update()override;
	void Print() override;

	bool Add(coordinate pos, weaponData* d);
};