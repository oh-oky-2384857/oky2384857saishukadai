#include <string>
#include <DxLib.h>

#include "gameManager.h"
#include "blueScreen.h"
#include "titleManager.h"

#include "inputManager.h"
#include "sceneManager.h"
#include "cursorManager.h"
#include "pauseManager.h"

#include "errorCode.h"
using namespace std;

gameManager::gameManager():gs(gameStatus::title) {
	manager::SetManagerName("gameManager");
	nowScene = new titleManager(this);

	managers =
	{
		new inputManager(this),
		new pauseManager(this),
		new cursorManager(this),
	};
}

gameManager::~gameManager() {
	for (manager* m : managers) {
		delete m;
	}
	managers.clear();
	delete nowScene;
	InitGraph();
}

bool gameManager::Awake() {
	nowScene->Awake();
	for (manager* m : managers) {
		if (!m->Awake())// Awake‚ÉŽ¸”s‚µ‚½‚ç;
		{
			return false;
		}
	}

	ptrPauseManager = (pauseManager*)GetManagerPtr("pauseManager");
	return true;
}
bool gameManager::Update() {
	for (manager* m : managers) {
		m->Update();
	}

	if (gs != gameStatus::pauseMenu && gs != gameStatus::option) {
		nowScene->Update();
	}
	return true;
}
void gameManager::Print() {
	nowScene->Print();
	for (manager* m : managers) {
		m->Print();
	}
}

bool gameManager::SetNewScene(sceneManager* newScene) {
	delete nowScene;
	nowScene = newScene;
	nowScene->Awake();
	return true;
}

manager* gameManager::GetManagerPtr(const char* managerName) {
	for (manager* m : managers) {
		if (strcmp(m->GetManagerName()->c_str(), managerName) == 0) {
			return m;
		}
	}
	return nullptr;
}