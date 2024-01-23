#include "gameManager.h"
#include "sceneManager.h"

bool sceneManager::ChangeNewScene(sceneManager* nextScene) {
	if (ptrGameManager->SetNewScene(nextScene)) {
		return true;
	}else {
		return false;
	}

}