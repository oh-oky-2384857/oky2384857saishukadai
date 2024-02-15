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
	errorData* Awake() override;
	bool Update()override;
	void Print() override;
};