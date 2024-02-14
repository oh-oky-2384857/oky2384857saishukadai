#include <DxLib.h>
#include <string>

#include "titleManager.h"
#include "gameManager.h"
#include "inputDate.h"
#include "inputManager.h"

#include "gameMainManager.h"

#include "blueScreen.h"
#include "errorCode.h"

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

bool titleManager::Awake(){
	//�摜�ǂݍ���;
	titleHandle = LoadGraph(TITLE_HANDLE_PATH.c_str());
	if (titleHandle == -1) {//���s�Ńu���X�N�s��;
		errorData data = { errorCode::handleRoadFail, errorSource::titleManager ,(string*)nullptr };
		sceneManager* newScene = new blueScreenManager(ptrGameManager,&data);
		sceneManager::ChangeNewScene(newScene);
		return false;
	}
	//�C���v�b�g�f�[�^�擾;
	//inputManager�擾;
	inputManager* ptrim = (inputManager*)ptrGameManager->GetManagerPtr("inputManager");
	if (ptrim == nullptr) {//�Ȃ���΃u���X�N�s��;
		errorData data = { errorCode::objectNotFound , errorSource::titleManager ,"inputManager���Ȃ�" };
		sceneManager* newScene = new blueScreenManager(ptrGameManager, &data);
		sceneManager::ChangeNewScene(newScene);
		return false;
	}
	//inputDara�擾;
	input = ptrim->GetInputDataPtr()->mouse;
	if (input == nullptr) {//�Ȃ���΃u���X�N�s��;
		errorData data = { errorCode::objectNotFound , errorSource::titleManager ,"inputData���Ȃ�" };
		sceneManager* newScene = new blueScreenManager(ptrGameManager, &data);
		sceneManager::ChangeNewScene(newScene);
		return false;
	}

	return true;
}

bool titleManager::Update() {
	//start�{�^��;
	if (input->isLeftClick && 
		input->x > TITLE_BUTTON_START_POSITION[0].x && input->x < TITLE_BUTTON_START_POSITION[1].x &&
		input->y > TITLE_BUTTON_START_POSITION[0].y && input->y < TITLE_BUTTON_START_POSITION[1].y) {
		//�V�[���؂�ւ�;
		ptrGameManager->SetGameStatus(gameStatus::main);
			
		sceneManager* newScene = new gameMainManager(ptrGameManager);
		sceneManager::ChangeNewScene(newScene);

		return true;
	}

	//end�{�^��;
	if (input->isLeftClick &&
		input->x > TITLE_BUTTON_END_POSITION[0].x && input->x < TITLE_BUTTON_END_POSITION[1].x &&
		input->y > TITLE_BUTTON_END_POSITION[0].y && input->y < TITLE_BUTTON_END_POSITION[1].y) {
		//gameStatus�ύX;
		ptrGameManager->SetGameStatus(gameStatus::end);
		return true;
	}
	return true;
}
void titleManager::Print()
{
	DrawGraph(0, 0, titleHandle, false);
}