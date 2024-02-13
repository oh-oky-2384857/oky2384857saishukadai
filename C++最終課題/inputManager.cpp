#include "inputManager.h"
#include "inputDate.h"
#include "gameManager.h"
#include <string>
#include <DxLib.h>

//�Q�[���p�b�h�̃A�i���O�X�e�B�b�N�̓��͒l�̕�;
const int ANALOG_STICK_INPUT_MAX = 10;
const int ANALOG_STICK_INPUT_MIN = -10;
const int DIVITION_ANALOG_STICK_INPUT_POWER = 100;//�A�i���O�X�e�B�b�N�̓��͒l�����鐔;


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

	int xinp = 0;//x�̓��͒l;
	int yinp = 0;//y�̓��͒l;

	DINPUT_JOYSTATE inputPad;
	GetJoypadDirectInputState(DX_INPUT_PAD1, &inputPad);//�p�b�h�̏��擾;
	
	//�X�e�B�b�N����;
	xinp -= inputPad.X / DIVITION_ANALOG_STICK_INPUT_POWER;
	yinp -= inputPad.Y / DIVITION_ANALOG_STICK_INPUT_POWER;

	//�\���{�^������;
	switch (inputPad.POV[0])
	{
	case -1://���͂Ȃ�;
		break;
	case 0://�����;
		yinp -= ANALOG_STICK_INPUT_MIN;
		break;
	case 4500://�E�����;
		xinp -= ANALOG_STICK_INPUT_MAX;
		yinp -= ANALOG_STICK_INPUT_MIN;
		break;
	case 9000://�E����;
		xinp -= ANALOG_STICK_INPUT_MAX;
		break;
	case 13500://�E������;
		xinp -= ANALOG_STICK_INPUT_MAX;
		yinp -= ANALOG_STICK_INPUT_MAX;
		break;
	case 18000://������;
		yinp -= ANALOG_STICK_INPUT_MAX;
		break;
	case 22500://��������;
		xinp -= ANALOG_STICK_INPUT_MIN;
		yinp -= ANALOG_STICK_INPUT_MAX;
		break;
	case 27000://������;
		xinp -= ANALOG_STICK_INPUT_MIN;
		break;
	case 31500://�������;
		xinp -= ANALOG_STICK_INPUT_MIN;
		yinp -= ANALOG_STICK_INPUT_MIN;
		break;
	default:
		break;
	}

	//�L�[�{�[�h����;
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


	//�K��l�Ɏ��߂�;
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

void inputManager::Print() {
	//DrawFormatString(0, 0, GetColor(255, 255, 255), "%d", inputs->move->xPower);
}