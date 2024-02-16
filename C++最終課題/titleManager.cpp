#include <DxLib.h>
#include <string>

#include "titleManager.h"
#include "gameManager.h"
#include "inputDate.h"
#include "inputManager.h"

#include "gameMainManager.h"

using namespace std;

const string TITLE_HANDLE_PATH = "./resource/titleResource/title.png";//�^�C�g���摜�̃p�X;

//�^�C�g���̃X�^�[�g�{�^���̏ꏊ:[0]����[1]�E��;
const coordinate TITLE_BUTTON_START_POSITION[2] = { { 82,300},{245,400} };

//�^�C�g���̏I���{�^���̏ꏊ:[0]����[1]�E��;
const coordinate TITLE_BUTTON_END_POSITION[2]	= { {598,  2},{638, 42} };

titleManager::titleManager(gameManager* pgm){
	sceneManager::ptrGameManager = pgm;
	manager::SetManagerName("titleManager");

}

titleManager::~titleManager(){
	//�摜�n���h���폜;s
	DeleteGraph(titleHandle);
}

errorData* titleManager::Awake(){
	//�摜�ǂݍ���;
	titleHandle = LoadGraph(TITLE_HANDLE_PATH.c_str());
	if (titleHandle == -1) {//���s�Ńu���X�N�s��;
		errorData* data =new errorData { errorCode::handleRoadFail, errorSource::titleManager ,(string*)nullptr };
		return data;
	}
	//�C���v�b�g�f�[�^�擾;
	//inputManager�擾;
	inputManager* ptrim = (inputManager*)ptrGameManager->GetManagerPtr("inputManager");
	if (ptrim == nullptr) {//�Ȃ���΃u���X�N�s��;
		errorData* data = new errorData{ errorCode::objectNotFound , errorSource::titleManager ,"inputManager���Ȃ�" };
		return data;
	}
	//inputDara�擾;
	input = ptrim->GetInputDataPtr()->mouse;
	if (input == nullptr) {//�Ȃ���΃u���X�N�s��;
		errorData* data = new errorData{ errorCode::objectNotFound , errorSource::titleManager ,"inputData���Ȃ�" };
		return data;
	}

	return nullptr;
}

bool titleManager::Update() {
	//start�{�^��;
	if (input->isLeftClick && 
		input->x > TITLE_BUTTON_START_POSITION[0].x && input->x < TITLE_BUTTON_START_POSITION[1].x &&
		input->y > TITLE_BUTTON_START_POSITION[0].y && input->y < TITLE_BUTTON_START_POSITION[1].y) {
		//�V�[���؂�ւ�;
		ptrGameManager->SetGameStatus(gameStatus::main);
			
		//���C���V�[����;
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
	//�摜�`��;
	DrawGraph(0, 0, titleHandle, false);
}