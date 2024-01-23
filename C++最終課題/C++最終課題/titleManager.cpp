#include <DxLib.h>
#include <string>

#include "gameCommon.h"
#include "titleManager.h"
#include "gameManager.h"

using namespace std;

static const string TITLE_HANDLE_PATH = "./resource/titleResource/title.png";


titleManager::titleManager(gameManager* pgm):ptrGameManager(pgm){

	manager::SetManagerName("titleManager");

}

titleManager::~titleManager(){
	DeleteGraph(titleHandle);
}

bool titleManager::Awake(){
	titleHandle = LoadGraph(TITLE_HANDLE_PATH.c_str());
	if (titleHandle == -1) {
		return false;
	}
	return true;
}

bool titleManager::Update() {
	if (GetMouseInput() & MOUSE_INPUT_RIGHT) {
		ptrGameManager->ChangeBlueScreen();
	}
	return true;
}
void titleManager::Print()
{
	DrawGraph(0, 0, titleHandle, true);
}