#include "gameMainManager.h"
#include "gameManager.h"
#include "playerManager.h"
#include "mapManager.h"
#include "enemyManager.h"
#include "playerShotManager.h"
#include "inputManager.h"
#include "inputDate.h"
#include "titleManager.h"

#include "blueScreen.h"
#include "errorCode.h"

//�Q�[���I�[�o�[�ƃQ�[���N���A�̉摜�̃p�X;
const std::string GAMEOVER_HANDLE_PATH = {"./resource/gameMainResource/gameOver.png"};
const std::string GAMECLEAR_HANDLE_PATH = { "./resource/gameMainResource/gameClear.png" };
const int CHANGE_SCENE_TIME = 500;//�V�[�����ς��܂ł̎���;

const coordinate GAME_STATE_PRINT_POINT = {};

gameMainManager::gameMainManager(gameManager* ptrGM) : gamingFlag(true){
	sceneManager::ptrGameManager = ptrGM;
	manager::SetManagerName("gameMainManager");

	managers =
	{
		new mapManager(this),
		new enemyManager(this),
		new playerManager(this),
		new playerShotManager(this),
	};

}
gameMainManager::~gameMainManager() {
	for (manager* m : managers) {
		delete m;
	}
	managers.clear();
	//�摜�n���h���폜;
	DeleteGraph(gameClearHandle);
	DeleteGraph(gameOverHandle);
}
bool gameMainManager::Awake() {
	//�e��}�l�[�W����Awake�𓮂���;
	for (manager* m : managers) {
		if (!m->Awake()) {
			break;
		}
	}
	for (manager* m : managers) {
		if (!m->Start()) {
			break;
		}
	}
	//�摜�ǂݍ��݂Ɏ��s������;
	gameOverHandle = LoadGraph(GAMEOVER_HANDLE_PATH.c_str());
	if (gameOverHandle == -1) {//�u���X�N�s��;
		errorData data = { errorCode::handleRoadFail,errorSource::gameMainManager,(std::string*)nullptr };
		ChangeBlueScreen(&data);
		return false;
	}
	//�摜�ǂݍ��݂Ɏ��s������2;
	gameClearHandle = LoadGraph(GAMECLEAR_HANDLE_PATH.c_str());
	if (gameOverHandle == -1) {//�u���X�N�s��;
		errorData data = { errorCode::handleRoadFail,errorSource::gameMainManager,(std::string*)nullptr };
		ChangeBlueScreen(&data);
		return false;
	}

	return true;
}
bool gameMainManager::Update(){
	if (gamingFlag) {//�Q�[���������Ă���Ȃ�;

		//�f�o�b�O�p;
		SetGameClear();
		//�f�o�b�O�p;


		for (manager* m : managers) {
			m->Update();
		}
	}else {
		if (changeSceneCnt-- < 0) {
			//�V�[���Έ�;
			sceneManager::ChangeNewScene(nextScene);
			//�P�x��߂�;
			SetDrawBright(255, 255, 255);
			return true;
		}else {
			//�������P�x��������;
			int brightness = 255 * (((float)changeSceneCnt / CHANGE_SCENE_TIME * 0.875) + 0.125);
			SetDrawBright(brightness, brightness, brightness);
		}
		
	}
	return true;
}
void gameMainManager::Print() {
	for (manager* m : managers) {
		m->Print();
	}
	if (!gamingFlag) {//�Q�[���������Ă��Ȃ��Ȃ�;
		DrawGraph(76,216, gameStateHandle, true);
	}
}

manager* gameMainManager::GetManagerPtr(const char* managerName) {
	std::string managerN = managerName;
	for (manager* m : managers) {
		//�}�l�[�W���[�l�[������v������;
		if (managerN.compare(m->GetManagerNameInstans()) == 0) {
			return m;
		}
	}
	return nullptr;
}

void gameMainManager::ChangeBlueScreen(errorData* data) {
	//�u���[�X�N���[���ɕΈ�;
	sceneManager* newScene = new blueScreenManager(ptrGameManager, data);
	sceneManager::ChangeNewScene(newScene);
}

const inputData* gameMainManager::GetInputData() {
	//inputData�擾;
	inputManager* ptrim = (inputManager*)ptrGameManager->GetManagerPtr("inputManager");
	if (ptrim == nullptr) {
		return nullptr;
	}
	return ptrim->GetInputDataPtr();
}
void gameMainManager::SetGameOver() {
	//�V�[���Έڎ��Ԑݒ�;
	changeSceneCnt = CHANGE_SCENE_TIME;
	//�t���O�ύX;
	gamingFlag = false;
	//���̃V�[������
	nextScene = new titleManager(ptrGameManager);
	//�摜�n���h���ݒ�;
	gameStateHandle = gameOverHandle;
}
void gameMainManager::SetGameClear() {
	//�V�[���Έڎ��Ԑݒ�;
	changeSceneCnt = CHANGE_SCENE_TIME;
	//�t���O�ύX;
	gamingFlag = false;
	//���̃V�[������
	nextScene = new titleManager(ptrGameManager);
	//�摜�n���h���ݒ�;
	gameStateHandle = gameClearHandle;
}