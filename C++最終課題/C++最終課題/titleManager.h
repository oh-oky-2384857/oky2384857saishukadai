#pragma once
#include "sceneManager.h"
#include <string>

// �O���錾;
class gameManager;

class titleManager :public sceneManager {
private:
	// �O���t�@�C������ǂݍ���;
	// ./resource/titleResource/title.png ;
	int titleHandle;

	gameManager* ptrGameManager;
public:
	titleManager(gameManager* pgm);
	~titleManager();
	bool Awake();
	bool Update();
	void Print();
};