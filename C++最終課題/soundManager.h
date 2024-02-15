#pragma once
#include "manager.h"

class gameManager;

class soundManager :public manager{
private:
	int bgmVolume;	//bgm‚Ì‰¹—Ê,0~255
	int seVolume;	//se‚Ì‰¹—Ê,0~255

	//ŠÖ”ŒÄ‚Ño‚µ—p;
	gameManager* ptrGameManager;

public:
	soundManager(gameManager* pgm);
	~soundManager();
	errorData* Awake() override;
	bool Update()override;
	void Print() override {};
};