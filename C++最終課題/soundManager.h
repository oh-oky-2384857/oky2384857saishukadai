#pragma once
#include "manager.h"

class gameManager;

class soundManager :public manager{
private:
	int bgmVolume;	//bgm�̉���,0~255
	int seVolume;	//se�̉���,0~255

	//�֐��Ăяo���p;
	gameManager* ptrGameManager;

public:
	soundManager(gameManager* pgm);
	~soundManager();
	bool Awake() override;
	bool Update()override;
	void Print() override {};
};