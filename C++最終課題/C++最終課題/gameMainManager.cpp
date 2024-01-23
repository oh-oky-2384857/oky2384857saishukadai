#include "gameMainManager.h"
#include "gameManager.h"
#include "playerManager.h"

gameMainManager::gameMainManager(gameManager* ptrGM):
ptrGameManager(ptrGM)
{
	manager::SetManagerName("gameMainManager");

	managers =
	{
		new playerManager
	};
}
gameMainManager::~gameMainManager() {
	for (manager* m : managers) {
		delete m;
	}
	managers.clear();
}
bool gameMainManager::Awake() {
	return true;
}
bool gameMainManager::Update(){
	return true;
}
void gameMainManager::Print() {

}