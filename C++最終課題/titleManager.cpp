#include <DxLib.h>
#include <string>

#include "titleManager.h"
#include "gameManager.h"
#include "inputDate.h"
#include "inputManager.h"

#include "gameMainManager.h"

using namespace std;

const string TITLE_HANDLE_PATH = "./resource/titleResource/title.png";
const coordinate TITLE_BUTTON_START_POSITION[2] = { { 82,300},{245,400} };
const coordinate TITLE_BUTTON_END_POSITION[2]	= { {598,  2},{638, 42} };

titleManager::titleManager(gameManager* pgm){
	sceneManager::ptrGameManager = pgm;
	manager::SetManagerName("titleManager");

}

titleManager::~titleManager(){
	DeleteGraph(titleHandle);
}

errorData* titleManager::Awake(){
	//画像読み込み;
	titleHandle = LoadGraph(TITLE_HANDLE_PATH.c_str());
	if (titleHandle == -1) {//失敗でブルスク行き;
		errorData* data =new errorData { errorCode::handleRoadFail, errorSource::titleManager ,(string*)nullptr };
		return data;
	}
	//インプットデータ取得;
	//inputManager取得;
	inputManager* ptrim = (inputManager*)ptrGameManager->GetManagerPtr("inputManager");
	if (ptrim == nullptr) {//なければブルスク行き;
		errorData* data = new errorData{ errorCode::objectNotFound , errorSource::titleManager ,"inputManagerがない" };
		return data;
	}
	//inputDara取得;
	input = ptrim->GetInputDataPtr()->mouse;
	if (input == nullptr) {//なければブルスク行き;
		errorData* data = new errorData{ errorCode::objectNotFound , errorSource::titleManager ,"inputDataがない" };
		return data;
	}

	return nullptr;
}

bool titleManager::Update() {
	//startボタン;
	if (input->isLeftClick && 
		input->x > TITLE_BUTTON_START_POSITION[0].x && input->x < TITLE_BUTTON_START_POSITION[1].x &&
		input->y > TITLE_BUTTON_START_POSITION[0].y && input->y < TITLE_BUTTON_START_POSITION[1].y) {
		//シーン切り替え;
		ptrGameManager->SetGameStatus(gameStatus::main);
			
		sceneManager* newScene = new gameMainManager(ptrGameManager);
		sceneManager::ChangeNewScene(newScene);

		return true;
	}

	//endボタン;
	if (input->isLeftClick &&
		input->x > TITLE_BUTTON_END_POSITION[0].x && input->x < TITLE_BUTTON_END_POSITION[1].x &&
		input->y > TITLE_BUTTON_END_POSITION[0].y && input->y < TITLE_BUTTON_END_POSITION[1].y) {
		//gameStatus変更;
		ptrGameManager->SetGameStatus(gameStatus::end);
		return true;
	}
	return true;
}
void titleManager::Print()
{
	DrawGraph(0, 0, titleHandle, false);
}