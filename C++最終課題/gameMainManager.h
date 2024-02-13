#pragma once
#include "sceneManager.h"
#include <list>

// ‘O•ûéŒ¾;
class gameManager;
struct mouseinputData;
struct errorData;
struct inputData;

class gameMainManager :public sceneManager{
private:

	std::list<manager*> managers;
public:
	gameMainManager(gameManager* ptrGM);
	~gameMainManager();

	bool Awake() override;
	bool Update()override;
	void Print() override;

	manager* GetManagerPtr(const char* managerName);

	void ChangeBlueScreen(errorData* data);

	const inputData* GetInputData();

};