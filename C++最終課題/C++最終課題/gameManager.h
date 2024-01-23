#pragma once
#include <list>
#include "manager.h"


// �O���錾;
class sceneManager;
struct errorData;

class gameManager :public manager {
private:
	sceneManager* nowScene;
	std::list <manager*> managers;

public:
	gameManager();
	~gameManager();

	bool Awake();
	bool Update();
	void Print();

	bool SetNewScene(sceneManager* newScene);

	manager* GetManagerPtr(const char* managerName);

	void ChangeBlueScreen(errorData* data);
};