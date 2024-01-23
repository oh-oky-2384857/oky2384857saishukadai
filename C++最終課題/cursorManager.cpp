#include <DxLib.h>
#include <string>
#include "cursorManager.h"
#include "gameManager.h"
#include "gameCommon.h"
#include "inputDate.h"
#include "inputManager.h"

static const int CURSOR_UPDATE_CNT = 5;
static const int CURSOR_HANDLE_NUM = 2;//カーソルの画像の種類;
//カーソルの画像のパス;
const std::string CURSOR_HANDLE_PATH[CURSOR_HANDLE_NUM] =
{
	"./resource/gameCommonResource/scorp1.png",
	"./resource/gameCommonResource/scorp2.png",
};

cursorManager::cursorManager(gameManager* ptrgm)
	:updateCnt(CURSOR_UPDATE_CNT),nowCursorHandle(1), ptrGameManager(ptrgm),inputDates(nullptr)
{
	manager::SetManagerName("cursorManager");

	cursorHandles = new int[CURSOR_HANDLE_NUM];
	for (int i = 0; i < CURSOR_HANDLE_NUM; i++) {
		//画像読み込み;
		cursorHandles[i] = LoadGraph(CURSOR_HANDLE_PATH[i].c_str());
		if (cursorHandles[i] == -1) {
			exit(1);
		}
	}
	//画像サイズ取得;
	GetGraphSize(cursorHandles[0], &cursorWidth, &cursorHeight);
}
cursorManager::~cursorManager() {
	for (int i = 0; i < CURSOR_HANDLE_NUM; i++) {
		//画像削除;
		DeleteGraph( cursorHandles[i] );
	}
	delete[] cursorHandles;
}
bool cursorManager::Awake() {
	inputManager* ptrim =(inputManager*)ptrGameManager->GetManagerPtr("inputManager");
	if (ptrim == nullptr) {
		return false;
	}
	inputDates = ptrim->TellInputDataPtr()->mouse;
	return true;
}
bool cursorManager::Update() {
	return true;
}
void cursorManager::Print() {
	DrawGraph(inputDates->x - cursorWidth / 2, inputDates->y - cursorHeight / 2, cursorHandles[nowCursorHandle],true);
}