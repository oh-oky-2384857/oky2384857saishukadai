#include "soundManager.h"

soundManager::soundManager(gameManager* pgm)
: ptrGameManager(pgm)
{
	manager::SetManagerName("soundManager");
}
soundManager::~soundManager() {

}
bool soundManager::Awake() {
	return true;
}
bool soundManager::Update(){
	return true;
}