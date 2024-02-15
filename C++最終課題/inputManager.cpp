#include "inputManager.h"
#include "inputDate.h"
#include "gameManager.h"
#include <string>
#include <DxLib.h>

//ゲームパッドのアナログスティックの入力値の幅;
const int ANALOG_STICK_INPUT_MAX = 10;
const int ANALOG_STICK_INPUT_MIN = -10;
const int DIVITION_ANALOG_STICK_INPUT_POWER = 100;//アナログスティックの入力値を割る数;

const int SHOT_RANGE_LIMIT_INPUT = 320;//shotの入力値の係数;
const float SHOT_RANGE_STICK_INPUT_SMOUNT = 3.125;//shotのアナログスティックの入力値を割る数;

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
errorData* inputManager::Awake(){
	return nullptr;
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

void inputManager::ShotUpdate() {
	shotInputData* ptrinp = inputs->shot;

	//shotはpad入力を優先する、pad入力がないならマウス入力に切り替える;
	DINPUT_JOYSTATE inputPad;
	GetJoypadDirectInputState(DX_INPUT_PAD1, &inputPad);//パッドの情報取得;

	int x, y;

	if (inputPad.Rx == 0 && inputPad.Ry == 0) {
		//pad入力がないなら;
		//マウス座標取得;
		GetMousePoint(&x, &y);

	}else {
		//あるなら;
		x = inputPad.X / SHOT_RANGE_STICK_INPUT_SMOUNT;
		y = inputPad.Y / SHOT_RANGE_STICK_INPUT_SMOUNT;
	}


	//ノーマライズ;

	//画面中央を原点に
	x -= SCREEN_WIDTH / 2;
	y -= SCREEN_HEIGHT / 2;
	int dist = sqrt(x * x + y * y);

	if (dist >= SHOT_RANGE_LIMIT_INPUT) {
		float nx, ny;
		nx = (float)x / dist;
		ny = (float)y / dist;

		//係数をかける;
		x = nx * SHOT_RANGE_LIMIT_INPUT;
		y = ny * SHOT_RANGE_LIMIT_INPUT / 4 * 3;
	}

	//画面左上を原点に戻し、inputsに収める;
	ptrinp->x = x + SCREEN_WIDTH / 2;
	ptrinp->y = y + SCREEN_HEIGHT / 2;

	if (inputPad.Z  < 0) {
		ptrinp->isTrigger = true;
	}else {
		//左クリック;
		ptrinp->isTrigger = (GetMouseInput() & MOUSE_INPUT_LEFT) != 0;
	}
}
void inputManager::PauseUpdate() {
	//エスケープキーまたはスタートボタン;
	
	pauseInputData* ptrinp = inputs->pause;
	DINPUT_JOYSTATE inputPad;
	GetJoypadDirectInputState(DX_INPUT_PAD1, &inputPad);//パッドの情報取得;
	ptrinp->isPause = false;

	//エスケープキー;
	if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) {
		ptrinp->isPause = true;
		return;
	}
	//エスケープキー;

	//スタートボタン;
	if (inputPad.Buttons[7] == 128) {
		ptrinp->isPause = true;
		return;
	}
	//スタートボタン;

}

const inputData* inputManager::GetInputDataPtr()const{
	return inputs;
}

void inputManager::Print() {
	//DrawFormatString(0, 0, GetColor(255, 255, 0), "x %d,y %d", inputs->shot->x, inputs->shot->y);
}