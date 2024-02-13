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
bool soundManager::Awake() {
	return true;
}
bool soundManager::Update(){
	return true;
}