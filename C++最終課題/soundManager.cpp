#include <string>
#include "soundManager.h"

using namespace std;

soundManager::soundManager(gameManager* pgm)
: ptrGameManager(pgm)
{
	manager::SetManagerName("inputManager");
}
soundManager::~soundManager() {

}
errorData* soundManager::Awake() {
	return nullptr;
}
bool soundManager::Update(){
	return true;
}