#include <DxLib.h>
#include <string>
#include "cursorManager.h"
#include "gameManager.h"
#include "gameCommon.h"
#include "inputDate.h"
#include "inputManager.h"

static const int CURSOR_UPDATE_CNT = 5;
static const int CURSOR_HANDLE_NUM = 2;//�J�[�\���̉摜�̎��;
//�J�[�\���̉摜�̃p�X;
static const std::string CURSOR_HANDLE_PATH[CURSOR_HANDLE_NUM] =
{
	"./resource/gameCommonResource/scorp1.png",
	"./resource/gameCommonResource/scorp2.png",
};

cursorManager::cursorManager(gameManager* ptrgm)
	:updateCnt(CURSOR_UPDATE_CNT),nowCursorHandle(1), ptrGameManager(ptrgm)
{
	manager::SetManagerName("cursorManager");

	cursorHandles = new int[CURSOR_HANDLE_NUM];
	for (int i = 0; i < CURSOR_HANDLE_NUM; i++) {
		//�摜�ǂݍ���;
		cursorHandles[i] = LoadGraph(CURSOR_HANDLE_PATH[i].c_str());
		if (cursorHandles[i] == -1) {
			exit(1);
		}
	}
	//�摜�T�C�Y�擾;
	GetGraphSize(cursorHandles[0], &cursorWidth, &cursorHeight);
}
cursorManager::~cursorManager() {
	for (int i = 0; i < CURSOR_HANDLE_NUM; i++) {
		//�摜�폜;
		DeleteGraph( cursorHandles[i] );
	}
	delete[] cursorHandles;
}
void cursorManager::Awake() {
	inputManager* ptrim =(inputManager*)ptrGameManager->GetManagerPtr("inputManager");
	if (ptrim == nullptr) {
		exit(0);
	}
	inputDates = ptrim->TellInputDataPtr()->mouse;
}
void cursorManager::Update() {

}
void cursorManager::Print() {
	DrawGraph(inputDates->x - cursorWidth / 2, inputDates->y - cursorHeight / 2, cursorHandles[nowCursorHandle],true);
}