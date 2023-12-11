#include <DxLib.h>
#include <string>
#include "cursorManager.h"
#include "gameCommon.h"

static const int cursor_UPDATE_CNT = 5;
static const int cursor_HANDLE_NUM = 2;//カーソルの画像の種類;
//カーソルの画像のパス;
static const std::string cursor_HANDLE_PATH[cursor_HANDLE_NUM] =
{
	"./resource/gameCommonResource/scorp1.png",
	"./resource/gameCommonResource/scorp2.png",
};

cursorManager::cursorManager():updateCnt(cursor_UPDATE_CNT),nowCursorHandle(1){
	cursorHandles = new int[cursor_HANDLE_NUM];
	for (int i = 0; i < cursor_HANDLE_NUM; i++) {
		//画像読み込み;
		cursorHandles[i] = LoadGraph(cursor_HANDLE_PATH[i].c_str());
		if (cursorHandles[i] == -1) {
			exit(1);
		}
	}
	//画像サイズ取得;
	GetGraphSize(cursorHandles[0], &cursorWidth, &cursorHeight);
}
cursorManager::~cursorManager() {
	for (int i = 0; i < cursor_HANDLE_NUM; i++) {
		//画像削除;
		DeleteGraph( cursorHandles[i] );
	}
	delete[] cursorHandles;
}
void cursorManager::Update() {
	if (updateCnt-- < 0) {
		GetMousePoint(&cursorCoord.x, &cursorCoord.y);
		updateCnt = cursor_UPDATE_CNT;
	}
}
void cursorManager::Print() {
	DrawGraph(cursorCoord.x - cursorWidth / 2, cursorCoord.y - cursorHeight / 2, cursorHandles[nowCursorHandle],true);
}