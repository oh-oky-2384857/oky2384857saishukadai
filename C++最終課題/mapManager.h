#pragma once
#include "manager.h"

// �O���錾;
class gameMainManager;
class playerManager;

//�����^�C����~���l�߂�;
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