#include <string>

#include "gameManager.h"
#include "blueScreen.h"
#include "titleManager.h"

#include "inputManager.h"
#include "sceneManager.h"
#include "cursorManager.h"

using namespace std;

gameManager::gameManager() {
	manager::SetManagerName("gameManager");
	nowScene = new titleManager(this);

	managers =
	{
		new cursorManager(this),
		new inputManager(this)
	};
}

gameManager::~gameManager() {
	managers.clear();
}

bool gameManager::Awake() {

	for (manager* m : managers) {
		if (!m->Awake())// Awake‚ÉŽ¸”s‚µ‚½‚ç;
		{
			ChangeBlueScreen();
			break;
		}
	}
	return true;
}
bool gameManager::Update() {
	nowScene->Update();
	for (manager* m : managers) {
		m->Update();
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
void gameManager::ChangeBlueScreen(errorData* data) {
	delete nowScene;
	nowScene = new blueScreenManager(this,data);
}