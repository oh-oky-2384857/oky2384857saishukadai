#pragma once
#include "sceneManager.h"
#include <list>

// �O���錾;
class gameManager;
struct mouseInputDate;


class gameMainManager :public manager{
private:
	//�֐��Ăяo���p;
	gameManager* ptrGameManager;

	mouseInputDate* inputDates;

	std::list<manager*> managers;
public:
	gameMainManager(gameManager* ptrGM);
	~gameMainManager();

	bool Awake();
	bool Update();
	void Print();
};