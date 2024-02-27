#include <string>
#include <DxLib.h>
#include "inputManager.h"
#include "inputDate.h"
#include "gameManager.h"

//�Q�[���p�b�h�̃A�i���O�X�e�B�b�N�̓��͒l�̕�;
const int ANALOG_STICK_INPUT_MAX = 10;
const int ANALOG_STICK_INPUT_MIN = -10;
const int DIVITION_ANALOG_STICK_INPUT_POWER = 100;//�A�i���O�X�e�B�b�N�̓��͒l�����鐔;

const int SHOT_RANGE_LIMIT_INPUT = 320;//shot�̓��͒l�̌W��;
const float SHOT_RANGE_STICK_INPUT_SMOUNT = 3.125;//shot�̃A�i���O�X�e�B�b�N�̓��͒l�����鐔;

inputManager::inputManager(gameManager* ptrGM) :
ptrGameManager(ptrGM) 
{
	manager::SetManagerName("inputManager");
	inputs = new inputData;
	inputs->mouse = new mouseInputData;
	inputs->move  = new moveInputData;
	inputs->shot  = new shotInputData;
	inputs->pause = new pauseInputData;
}

inputManager::~inputManager() {
	delete inputs->mouse;
	delete inputs->move;
	delete inputs->shot;
	delete inputs->pause;
	delete inputs;
}
bool inputManager::Awake(){
	return true;
}
bool inputManager::Update() {

	MouseUpdate();
	MoveUpdate();
	ShotUpdate();
	PauseUpdate();

	return true;
}
void inputManager::MouseUpdate() {

	mouseInputData* ptrinp = inputs->mouse;

	ptrinp->isLeftClick = (GetMouseInput() & MOUSE_INPUT_LEFT) != 0; 
	ptrinp->isRightClick = (GetMouseInput() & MOUSE_INPUT_RIGHT) != 0;

	GetMousePoint(&ptrinp->x, &ptrinp->y);

}

void inputManager::MoveUpdate() {
	moveInputData* ptrinp = inputs->move;

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

void inputManager::ShotUpdate() {
	shotInputData* ptrinp = inputs->shot;

	//shot��pad���͂�D�悷��Apad���͂��Ȃ��Ȃ�}�E�X���͂ɐ؂�ւ���;
	DINPUT_JOYSTATE inputPad;
	GetJoypadDirectInputState(DX_INPUT_PAD1, &inputPad);//�p�b�h�̏��擾;

	int x, y;

	if (inputPad.Rx == 0 && inputPad.Ry == 0) {
		//pad���͂��Ȃ��Ȃ�;
		//�}�E�X���W�擾;
		GetMousePoint(&x, &y);

	}else {
		//����Ȃ�;
		x = inputPad.X / SHOT_RANGE_STICK_INPUT_SMOUNT;
		y = inputPad.Y / SHOT_RANGE_STICK_INPUT_SMOUNT;
	}


	//�m�[�}���C�Y;

	//��ʒ��������_��
	x -= SCREEN_WIDTH / 2;
	y -= SCREEN_HEIGHT / 2;
	int dist = sqrt(x * x + y * y);

	if (dist >= SHOT_RANGE_LIMIT_INPUT) {
		float nx, ny;
		nx = (float)x / dist;
		ny = (float)y / dist;

		//�W����������;
		x = nx * SHOT_RANGE_LIMIT_INPUT;
		y = ny * SHOT_RANGE_LIMIT_INPUT / 4 * 3;
	}

	//��ʍ�������_�ɖ߂��Ainputs�Ɏ��߂�;
	ptrinp->x = x + SCREEN_WIDTH / 2;
	ptrinp->y = y + SCREEN_HEIGHT / 2;

	if (inputPad.Z  < 0) {
		ptrinp->isTrigger = true;
	}else {
		//���N���b�N;
		ptrinp->isTrigger = (GetMouseInput() & MOUSE_INPUT_LEFT) != 0;
	}
}
void inputManager::PauseUpdate() {
	//�G�X�P�[�v�L�[�܂��̓X�^�[�g�{�^��;
	
	pauseInputData* ptrinp = inputs->pause;
	DINPUT_JOYSTATE inputPad;
	GetJoypadDirectInputState(DX_INPUT_PAD1, &inputPad);//�p�b�h�̏��擾;
	ptrinp->isPause = false;

	//�G�X�P�[�v�L�[;
	if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) {
		ptrinp->isPause = true;
		return;
	}
	//�G�X�P�[�v�L�[;

	//�X�^�[�g�{�^��;
	if (inputPad.Buttons[7] == 128) {
		ptrinp->isPause = true;
		return;
	}
	//�X�^�[�g�{�^��;

}

const inputData* inputManager::GetInputDataPtr()const{
	return inputs;
}

void inputManager::Print() {
	//DrawFormatString(0, 0, GetColor(255, 255, 0), "x %d,y %d", inputs->shot->x, inputs->shot->y);
}