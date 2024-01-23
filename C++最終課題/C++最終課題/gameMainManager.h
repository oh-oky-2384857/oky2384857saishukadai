#pragma once
#include "sceneManager.h"
#include <list>

// ‘O•ûéŒ¾;
class gameManager;
struct mouseInputDate;


class gameMainManager :public manager{
private:
	//ŠÖ”ŒÄ‚Ño‚µ—p;
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