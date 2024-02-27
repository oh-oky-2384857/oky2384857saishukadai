#include <DxLib.h>

#include "pauseManager.h"

#include "gameManager.h"
#include "inputDate.h"
#include "inputManager.h"

#include "errorCode.h"

const std::string PAUSE_HANDLE_PATH = { "./resource/gameCommonResource/pause.png" };
const coordinate PAUSE_PRINT_POSITION =  {80,20};

const coordinate PAUSE_MENU_RESUME_POSITION[2] = { {62,55} ,{418,121} };//続ける;
const coordinate PAUSE_MENU_OPTION_POSITION[2] = { {62,187},{418,253} };//オプション;
const coordinate PAUSE_MENU_QUIT_POSITION[2]   = { {62,319},{418,385} };//終了;

const int PAUSE_MENU_COOLTIME = 10;//ポーズメニューのクールタイム;

pauseManager::pauseManager(gameManager* ptrGM) 
:ptrGameManager(ptrGM), pauseCnt(0){
	SetManagerName("pauseManager");
}
pauseManager::~pauseManager() {
}
bool pauseManager::Awake() {
	//inputdates取得;
	inputManager* ptrim = (inputManager*)ptrGameManager->GetManagerPtr("inputManager");
	if (ptrim == nullptr) {//なければブルスク行き;
		errorData* data =new errorData { errorCode::objectNotFound,errorSource::pauseManager,"inputManagerがない" };
		throw data;
	}
	//mouse入力取得;
	mouseInput = ptrim->GetInputDataPtr()->mouse;
	if (mouseInput == nullptr) {//なければブルスク行き;
		errorData* data = new errorData{ errorCode::objectNotFound,errorSource::pauseManager,"moveInputがない" };
		throw data;
	}
	//pause入力取得;
	pauseInput = ptrim->GetInputDataPtr()->pause;
	if (mouseInput == nullptr) {//なければブルスク行き;
		errorData* data = new errorData{ errorCode::objectNotFound,errorSource::pauseManager,"moveInputがない" };
		throw data;
	}
	//画像読み込み
	pauseHandle = LoadGraph(PAUSE_HANDLE_PATH.c_str());
	if (pauseHandle == -1) {//失敗でブルスク行き;
		errorData* data = new errorData{ errorCode::handleRoadFail,errorSource::pauseManager,(std::string*) nullptr };
		throw data;
	}

	return true;
}
bool pauseManager::Update() {
	//カウンタを減らす;
	pauseCnt--;
	//inputがあり,カウントが0以下の場合
	if (pauseInput->isPause && pauseCnt < 0) {
		//カウンタ再設定;
		pauseCnt = PAUSE_MENU_COOLTIME;

		if (ptrGameManager->GetGameStatus() == gameStatus::pauseMenu) {
			//今ポーズならポーズ解除;
			EscapePause();
			return true;
		}else if(ptrGameManager->GetGameStatus() == gameStatus::main) {
			//今ポーズでないならポーズ;
			SetPause();
		}
	}

	if (ptrGameManager->GetGameStatus() != gameStatus::pauseMenu) {//ポーズじゃないなら;
		return true;
	}

	if (mouseInput->isLeftClick) {//クリックされたら
		mouseInputData* mi = mouseInput;
		//続けるボタン;
		if (mi->x > PAUSE_MENU_RESUME_POSITION[0].x && mi->x < PAUSE_MENU_RESUME_POSITION[1].x &&
			mi->y > PAUSE_MENU_RESUME_POSITION[0].y && mi->y < PAUSE_MENU_RESUME_POSITION[1].y) {
			EscapePause();
		}else if//オプションボタン;
		   (mi->x > PAUSE_MENU_OPTION_POSITION[0].x && mi->x < PAUSE_MENU_OPTION_POSITION[1].x &&
			mi->y > PAUSE_MENU_OPTION_POSITION[0].y && mi->y < PAUSE_MENU_OPTION_POSITION[1].y) {
			
			//未作成;

		}else if//終了ボタン;
		   (mi->x > PAUSE_MENU_QUIT_POSITION[0].x && mi->x < PAUSE_MENU_QUIT_POSITION[1].x &&
			mi->y > PAUSE_MENU_QUIT_POSITION[0].y && mi->y < PAUSE_MENU_QUIT_POSITION[1].y) {
			ptrGameManager->SetGameStatus(gameStatus::end);
		}
		
	}

	return true;
}
void pauseManager::Print() {
	if (ptrGameManager->GetGameStatus() != gameStatus::pauseMenu) {//ポーズじゃないなら;
		return;
	}
	DrawGraph(PAUSE_PRINT_POSITION.x, PAUSE_PRINT_POSITION.y, pauseHandle, true);

}

void pauseManager::SetPause() { 
	//すでにポーズなら;
	if (ptrGameManager->GetGameStatus() == gameStatus::pauseMenu) {
		return;
	}
	//状態をポーズに;
	ptrGameManager->SetGameStatus(gameStatus::pauseMenu);
	//輝度設定;
	SetDrawBright(128, 128, 128);
}
void pauseManager::EscapePause() {
	//ポーズじゃないなら;
	if(ptrGameManager->GetGameStatus() != gameStatus::pauseMenu) {
		return;
	}
	//状態を戻す;
	ptrGameManager->SetGameStatus(gameStatus::main);
	//輝度設定;
	SetDrawBright(255, 255, 255);
}