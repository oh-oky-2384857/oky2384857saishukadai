#pragma once
#include <list>
#include "manager.h"

// ‘O•ûéŒ¾;
class sceneManager;

class gameManager :public manager {
private:
	sceneManager* nowScene;
	std::list <manager*> managers;
public:
	gameManager();
	~gameManager();

	void Awake();
	void Update();
	void Print();

	bool SetNewScene(sceneManager* newScene);
};