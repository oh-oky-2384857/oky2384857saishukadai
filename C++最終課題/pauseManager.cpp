#include <DxLib.h>

#include "pauseManager.h"

#include "gameManager.h"
#include "inputDate.h"
#include "inputManager.h"

#include "errorCode.h"
#include "blueScreen.h"

const std::string PAUSE_HANDLE_PATH = { "./resource/gameCommonResource/pause.png" };
const coordinate PAUSE_PRINT_POSITION =  {80,20};

const coordinate PAUSE_MENU_RESUME_POSITION[2] = { {62,55} ,{418,121} };//������;
const coordinate PAUSE_MENU_OPTION_POSITION[2] = { {62,187},{418,253} };//�I�v�V����;
const coordinate PAUSE_MENU_QUIT_POSITION[2]   = { {62,319},{418,385} };//�I��;

const int PAUSE_MENU_COOLTIME = 10;//�|�[�Y���j���[�̃N�[���^�C��;

pauseManager::pauseManager(gameManager* ptrGM) 
:ptrGameManager(ptrGM), pauseCnt(0){
	SetManagerName("pauseManager");
}
pauseManager::~pauseManager() {

}
bool pauseManager::Awake() {
	//inputdates�擾;
	inputManager* ptrim = (inputManager*)ptrGameManager->GetManagerPtr("inputManager");
	if (ptrim == nullptr) {
		errorData data = { errorCode::objectNotFound,errorSource::pauseManager,"inputManager���Ȃ�" };
		sceneManager* bs = new blueScreenManager(ptrGameManager, &data);
		ptrGameManager->SetNewScene(bs);
		return false;
	}
	mouseInput = ptrim->GetInputDataPtr()->mouse;
	pauseInput = ptrim->GetInputDataPtr()->pause;
	if (mouseInput == nullptr) {
		errorData data = { errorCode::objectNotFound,errorSource::pauseManager,"moveInput���Ȃ�" };
		sceneManager* bs = new blueScreenManager(ptrGameManager, &data);
		ptrGameManager->SetNewScene(bs);
	}

	//�摜�ǂݍ���
	pauseHandle = LoadGraph(PAUSE_HANDLE_PATH.c_str());
	if (pauseHandle == -1) {
		errorData data = { errorCode::handleRoadFail,errorSource::pauseManager,(std::string*) nullptr};
		sceneManager* bs = new blueScreenManager(ptrGameManager, &data);
		ptrGameManager->SetNewScene(bs);
	}

	return true;
}
bool pauseManager::Update() {
	pauseCnt--;
	if (pauseInput->isPause && pauseCnt < 0) {
		
		pauseCnt = PAUSE_MENU_COOLTIME;
		if (ptrGameManager->GetGameStatus() == gameStatus::pauseMenu) {//�|�[�Y����;
			EscapePause();
			return true;
		}else if(ptrGameManager->GetGameStatus() == gameStatus::main) {//�|�[�Y;
			SetPause();
		}
	}

	if (ptrGameManager->GetGameStatus() != gameStatus::pauseMenu) {//�|�[�Y����Ȃ��Ȃ�;
		return true;
	}

	if (mouseInput->isLeftClick) {//�N���b�N���ꂽ��
		mouseInputData* mi = mouseInput;
		//������;
		if (mi->x > PAUSE_MENU_RESUME_POSITION[0].x && mi->x < PAUSE_MENU_RESUME_POSITION[1].x &&
			mi->y > PAUSE_MENU_RESUME_POSITION[0].y && mi->y < PAUSE_MENU_RESUME_POSITION[1].y) {
			EscapePause();
		}else if//�I�v�V����;
		   (mi->x > PAUSE_MENU_OPTION_POSITION[0].x && mi->x < PAUSE_MENU_OPTION_POSITION[1].x &&
			mi->y > PAUSE_MENU_OPTION_POSITION[0].y && mi->y < PAUSE_MENU_OPTION_POSITION[1].y) {

		}else if//�I��;
		   (mi->x > PAUSE_MENU_QUIT_POSITION[0].x && mi->x < PAUSE_MENU_QUIT_POSITION[1].x &&
			mi->y > PAUSE_MENU_QUIT_POSITION[0].y && mi->y < PAUSE_MENU_QUIT_POSITION[1].y) {
			ptrGameManager->SetGameStatus(gameStatus::end);
		}
		
	}

	return true;
}
void pauseManager::Print() {
	if (ptrGameManager->GetGameStatus() != gameStatus::pauseMenu) {//�|�[�Y����Ȃ��Ȃ�;
		return;
	}
	DrawGraph(PAUSE_PRINT_POSITION.x, PAUSE_PRINT_POSITION.y, pauseHandle, true);

}

void pauseManager::SetPause() { 
	//���łɃ|�[�Y�Ȃ�;
	if (ptrGameManager->GetGameStatus() == gameStatus::pauseMenu) {
		return;
	}

	ptrGameManager->SetGameStatus(gameStatus::pauseMenu);
	//�P�x�ݒ�;
	SetDrawBright(128, 128, 128);
}
void pauseManager::EscapePause() {
	//�|�[�Y����Ȃ��Ȃ�;
	if(ptrGameManager->GetGameStatus() != gameStatus::pauseMenu) {
		return;
	}

	ptrGameManager->SetGameStatus(gameStatus::main);
	//�P�x�ݒ�;
	SetDrawBright(255, 255, 255);
}