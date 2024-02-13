#include <DxLib.h>
#include <string>
#include "cursorManager.h"
#include "gameManager.h"
#include "gameCommon.h"
#include "inputDate.h"
#include "inputManager.h"

#include "errorCode.h"
#include "blueScreen.h"

static const int CURSOR_UPDATE_CNT = 5;
static const int CURSOR_HANDLE_NUM = 2;//�J�[�\���̉摜�̎��;
//�J�[�\���̉摜�̃p�X;
const std::string CURSOR_HANDLE_PATH[CURSOR_HANDLE_NUM] =
{
	"./resource/gameCommonResource/scorp1.png",
	"./resource/gameCommonResource/scorp2.png",
};

cursorManager::cursorManager(gameManager* ptrgm)
	:updateCnt(CURSOR_UPDATE_CNT),nowCursorHandle(1), ptrGameManager(ptrgm)
{
	manager::SetManagerName("cursorManager");

}
cursorManager::~cursorManager() {
	for (int i = 0; i < CURSOR_HANDLE_NUM; i++) {
		//�摜�폜;
		DeleteGraph( cursorHandles[i] );
	}
	delete[] cursorHandles;
}
bool cursorManager::Awake() {
	//inputdates�擾;
	inputManager* ptrim =(inputManager*)ptrGameManager->GetManagerPtr("inputManager");
	if (ptrim == nullptr) {
		errorData data = { errorCode::objectNotFound,errorSource::cursorManager,"inputManager���Ȃ�" };
		sceneManager* bs = new blueScreenManager(ptrGameManager, &data);
		ptrGameManager->SetNewScene(bs);
		return false;
	}
	inputDatas = ptrim->GetInputDataPtr()->mouse;
	if (inputDatas == nullptr) {
		errorData data = { errorCode::objectNotFound,errorSource::cursorManager,"inputManager���Ȃ�" };
		sceneManager* bs = new blueScreenManager(ptrGameManager, &data);
		ptrGameManager->SetNewScene(bs);
	}
	//�n���h������;
	cursorHandles = new int[CURSOR_HANDLE_NUM];
	for (int i = 0; i < CURSOR_HANDLE_NUM; i++) {
		//�摜�ǂݍ���;
		cursorHandles[i] = LoadGraph(CURSOR_HANDLE_PATH[i].c_str());
		if (cursorHandles[i] == -1) {
			errorData data = { errorCode::handleRoadFail,errorSource::cursorManager,(std::string*)nullptr };
			sceneManager* bs = new blueScreenManager(ptrGameManager, &data);
			ptrGameManager->SetNewScene(bs);
		}
	}
	//�摜�T�C�Y�擾;
	GetGraphSize(cursorHandles[0], &cursorWidth, &cursorHeight);
	return true;
}
bool cursorManager::Update() {
	return true;
}
void cursorManager::Print() {
	DrawGraph(inputDatas->x - cursorWidth / 2, inputDatas->y - cursorHeight / 2, cursorHandles[nowCursorHandle],true);
}