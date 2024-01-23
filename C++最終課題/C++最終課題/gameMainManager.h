#pragma once
#include "sceneManager.h"
#include <list>

// 前方宣言;
class gameManager;
struct mouseInputDate;


class gameMainManager :public manager{
private:
	//関数呼び出し用;
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