#include <string>

#include "gameManager.h"
#include "titleManager.h"
#include "sceneManager.h"
#include "cursorManager.h"


using namespace std;

gameManager::gameManager() {
	string* s = new string("gameManager");
	manager::SetManagetrName(s);
	nowScene = new titleManager(this);

	managers =
	{
		new cursorManager
	};
}

gameManager::~gameManager() {

}

void gameManager::Awake() {
	nowScene->Awake();
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