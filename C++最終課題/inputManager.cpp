#include "inputManager.h"
#include "inputDate.h"
#include "gameManager.h"
#include <string>
#include <DxLib.h>
//ゲームパッドのアナログスティックの入力値の幅;
const int ANALOG_STICK_INPUT_MAX = 10;
const int ANALOG_STICK_INPUT_MIN = -10;
const int DIVITION_ANALOG_STICK_INPUT_POWER = 100;//アナログスティックの入力値を割る数;


inputManager::inputManager(gameManager* ptrGM) :
ptrGameManager(ptrGM) 
{

	manager::SetManagerName("inputManager");
	inputs = new inputDate;
	inputs->mouse = new mouseInputDate;
	inputs->move = new moveInputDate;
}

inputManager::~inputManager() {
	delete inputs->mouse;
	delete inputs;
}
bool inputManager::Awake(){
	return true;
}
bool inputManager::Update() {

	MouseUpdate();
	MoveUpdate();
	return true;
}
void inputManager::MouseUpdate() {

	mouseInputDate* ptrinp = inputs->mouse;

	ptrinp->isLeftClick = (GetMouseInput() & MOUSE_INPUT_LEFT) != 0; 
	ptrinp->isRightClick = (GetMouseInput() & MOUSE_INPUT_RIGHT) != 0;

	GetMousePoint(&ptrinp->x, &ptrinp->y);

}

void inputManager::MoveUpdate() {
	moveInputDate* ptrinp = inputs->move;

	int xinp = 0;//xの入力値;
	int yinp = 0;//yの入力値;

	DINPUT_JOYSTATE inputPad;
	GetJoypadDirectInputState(DX_INPUT_PAD1, &inputPad);//パッドの情報取得;
	
	//スティック入力;
	xinp -= inputPad.X / DIVITION_ANALOG_STICK_INPUT_POWER;
	yinp -= inputPad.Y / DIVITION_ANALOG_STICK_INPUT_POWER;

	//十字ボタン入力;
	switch (inputPad.POV[0])
	{
	case -1://入力なし;
		break;
	case 0://上入力;
		yinp -= ANALOG_STICK_INPUT_MIN;
		break;
	case 4500://右上入力;
		xinp -= ANALOG_STICK_INPUT_MAX;
		yinp -= ANALOG_STICK_INPUT_MIN;
		break;
	case 9000://右入力;
		xinp -= ANALOG_STICK_INPUT_MAX;
		break;
	case 13500://右下入力;
		xinp -= ANALOG_STICK_INPUT_MAX;
		yinp -= ANALOG_STICK_INPUT_MAX;
		break;
	case 18000://下入力;
		yinp -= ANALOG_STICK_INPUT_MAX;
		break;
	case 22500://左下入力;
		xinp -= ANALOG_STICK_INPUT_MIN;
		yinp -= ANALOG_STICK_INPUT_MAX;
		break;
	case 27000://左入力;
		xinp -= ANALOG_STICK_INPUT_MIN;
		break;
	case 31500://左上入力;
		xinp -= ANALOG_STICK_INPUT_MIN;
		yinp -= ANALOG_STICK_INPUT_MIN;
		break;
	default:
		break;
	}

	//キーボード入力;
	if (CheckHitKey(KEY_INPUT_W) == 1 || CheckHitKey(KEY_INPUT_UP) == 1) {
		yinp -= ANALOG_STICK_INPUT_MIN;
	}
	if (CheckHitKey(KEY_INPUT_A) == 1 || CheckHitKey(KEY_INPUT_LEFT) == 1) {
		xinp -= ANALOG_STICK_INPUT_MIN;
	}
	if (CheckHitKey(KEY_INPUT_S) == 1 || CheckHitKey(KEY_INPUT_DOWN) == 1) {
		yinp -= ANALOG_STICK_INPUT_MAX;
	}
	if (CheckHitKey(KEY_INPUT_D) == 1 || CheckHitKey(KEY_INPUT_RIGHT) == 1) {
		xinp -= ANALOG_STICK_INPUT_MAX;
	}

	//規定値に収める;
	if (xinp < ANALOG_STICK_INPUT_MIN) {
		xinp = ANALOG_STICK_INPUT_MIN;
	}
	if (xinp > ANALOG_STICK_INPUT_MAX) {
		xinp = ANALOG_STICK_INPUT_MAX;
	}
	if (yinp < ANALOG_STICK_INPUT_MIN) {
		yinp = ANALOG_STICK_INPUT_MIN;
	}
	if (yinp > ANALOG_STICK_INPUT_MAX) {
		yinp = ANALOG_STICK_INPUT_MAX;
	}

	ptrinp->xPower = xinp;
	ptrinp->yPower = yinp;
}

inputDate* inputManager::TellInputDataPtr() {
	return inputs;
}