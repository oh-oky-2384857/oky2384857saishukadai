#pragma once
#include "manager.h"

// ‘O•ûéŒ¾;
class gameMainManager;
class playerManager;

//“¯‚¶ƒ^ƒCƒ‹‚ğ•~‚«‹l‚ß‚é;
class mapManager :public manager{
private:
	int mapChipHandle;
	gameMainManager* ptrGameMain;

	playerManager* ptrPlayerManager;
public:
	mapManager(gameMainManager* pgmm);
	~mapManager();
	bool Awake();
	bool Update();
	void Print();
};