#include <DxLib.h>
#include <string>

#include "gameCommon.h"
#include "titleManager.h"
#include "gameManager.h"

using namespace std;

static const string TITLE_HANDLE_PATH = "./resource/titleResource/title.png";


titleManager::titleManager(gameManager* pgm){

	manager::SetManagerName("titleManager");

	titleHandle = LoadGraph(TITLE_HANDLE_PATH.c_str());
	if (titleHandle == -1) {
		exit(1);
	}
}

titleManager::~titleManager(){
	DeleteGraph(titleHandle);
}

void titleManager::Print()
{
	DrawGraph(0, 0, titleHandle, true);
}