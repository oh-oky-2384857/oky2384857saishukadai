#pragma once
#include "manager.h"

class gameManager;

class soundManager :public manager{
private:
	int bgmVolume;	//bgmの音量,0~255
	int seVolume;	//seの音量,0~255

	//関数呼び出し用;
	gameManager* ptrGameManager;

public:
	soundManager(gameManager* pgm);
	~soundManager();
	errorData* Awake() override;
	bool Update()override;
	void Print() override {};
};