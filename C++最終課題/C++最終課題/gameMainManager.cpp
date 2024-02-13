#include "gameMainManager.h"
#include "gameManager.h"
#include "playerManager.h"
#include "mapManager.h"
#include "enemyManager.h"
#include "blueScreen.h"
#include "inputManager.h"
#include "inputDate.h"

gameMainManager::gameMainManager(gameManager* ptrGM){
	sceneManager::ptrGameManager = ptrGM;
	manager::SetManagerName("gameMainManager");

	managers =
	{
		new mapManager(this),
		new enemyManager(this),
		new playerManager(this),
	};

}
gameMainManager::~gameMainManager() {
	for (manager* m : managers) {
		delete m;
	}
	managers.clear();
}
bool gameMainManager::Awake() {
	for (manager* m : managers) {
		if (!m->Awake()) {
			break;
		}
	}
	return true;
}
bool gameMainManager::Update(){
	for (manager* m : managers) {
		m->Update();
	}
	return true;
}
void gameMainManager::Print() {
	for (manager* m : managers) {
		m->Print();
	}
}

manager* gameMainManager::GetManagerPtr(const char* managerName) {
	for (manager* m : managers) {
		if (strcmp(m->GetManagerName()->c_str(), managerName) == 0) {
			return m;
		}
	}
	return nullptr;
}

void gameMainManager::ChangeBlueScreen(errorData* data) {
	sceneManager* newScene = new blueScreenManager(ptrGameManager, data);
	sceneManager::ChangeNewScene(newScene);
}

inputDate* gameMainManager::GetInputDate() {
	inputManager* ptrim = (inputManager*)ptrGameManager->GetManagerPtr("inputManager");
	if (ptrim == nullptr) {
		return nullptr;
	}
	return ptrim->TellInputDataPtr();
}