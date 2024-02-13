#include "inputManager.h"
#include "inputDate.h"

inputManager::inputManager(){
	inputs = new inputDate;
}

inputManager::~inputManager() {
	delete inputs;
}
void inputManager::Update() {
	inputs->mouse.isLeftClick = (GetMouseInput() & MOUSE_INPUT_LEFT) != 0;
	inputs->mouse.isRightClick = (GetMouseInput() & MOUSE_INPUT_RIGHT) != 0;

}