#pragma once
#include "sceneManager.h"
#include <list>

// ‘O•ûéŒ¾;
class gameManager;
struct mouseInputDate;
struct errorData;
struct inputDate;

class gameMainManager :public sceneManager{
private:

	std::list<manager*> managers;
public:
	gameMainManager(gameManager* ptrGM);
	~gameMainManager();

	bool Awake();
	bool Update();
	void Print();

	manager* GetManagerPtr(const char* managerName);

	void ChangeBlueScreen(errorData* data);

	inputDate* GetInputDate();

};