#include "inputManager.h"
#include "inputDate.h"
#include <string>

inputManager::inputManager(gameManager* ptrGM){

	manager::SetManagerName("inputManager");
	inputs = new inputDate;
	inputs->mouse = new mouseInputDate;
}

inputManager::~inputManager() {
	delete inputs->mouse;
	delete inputs;
}
void inputManager::Update() {

	MouseUpdate();

}
void inputManager::MouseUpdate() {

	mouseInputDate* ptrinp = inputs->mouse;

	ptrinp->isLeftClick = (GetMouseInput() & MOUSE_INPUT_LEFT) != 0; 
	ptrinp->isRightClick = (GetMouseInput() & MOUSE_INPUT_RIGHT) != 0;

	GetMousePoint(&ptrinp->x, &ptrinp->y);

}

inputDate* inputManager::TellInputDataPtr() {
	return inputs;
}