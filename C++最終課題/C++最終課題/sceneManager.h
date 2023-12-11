#pragma once
#include "manager.h"


// ‘O•ûéŒ¾;
class gameManager;


class sceneManager :public manager {
protected:
	gameManager* ptrGameManager;

public:
	sceneManager() : manager(), ptrGameManager(nullptr){}
	virtual void Awake() = 0;
	virtual void Update() = 0;
	virtual void Print() = 0;

	bool ChangeNewScene(sceneManager* nextScene);
};