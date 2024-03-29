#pragma once
#include "manager.h"

// 前方宣言;
class gameMainManager;
class playerManager;

//同じタイルを敷き詰める;
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