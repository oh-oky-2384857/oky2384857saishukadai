#include <DxLib.h>
#include <string>

#include "titleManager.h"
#include "gameManager.h"

#include "gameMainManager.h"

#include "blueScreen.h"
#include "errorCode.h"

using namespace std;

const string TITLE_HANDLE_PATH = "./resource/titleResource/title.png";


titleManager::titleManager(gameManager* pgm){
	sceneManager::ptrGameManager = pgm;
	manager::SetManagerName("titleManager");

}

titleManager::~titleManager(){
	DeleteGraph(titleHandle);
}

bool titleManager::Awake(){
	titleHandle = LoadGraph(TITLE_HANDLE_PATH.c_str());
	if (titleHandle == -1) {
		errorData data = { errorCode::handleRoadFail, errorSource::titleManager ,nullptr };
		sceneManager* newScene = new blueScreenManager(ptrGameManager,&data);

		sceneManager::ChangeNewScene(newScene);
		return false;
	}
	int x, y;
	GetGraphSize(titleHandle, &x, &y);
	int* a = new int;
	return true;
}

bool titleManager::Update() {
	if (GetMouseInput() & MOUSE_INPUT_RIGHT) {
		//ƒV[ƒ“Ø‚è‘Ö‚¦;
		sceneManager* newScene = new gameMainManager(ptrGameManager);

		sceneManager::ChangeNewScene(newScene);
		return true;
	}
	return true;
}
void titleManager::Print()
{
	DrawGraph(0, 0, titleHandle, false);
}