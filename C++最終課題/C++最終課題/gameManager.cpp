#include <string>

#include "gameManager.h"
#include "titleManager.h"
#include "sceneManager.h"
#include "cursorManager.h"
#include "inputManager.h"

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

}

void gameManager::Awake() {

	for (manager* m : managers) {
		m->Awake();
	}
}
void gameManager::Update() {
	nowScene->Update();
	for (manager* m : managers) {
		m->Update();
	}
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