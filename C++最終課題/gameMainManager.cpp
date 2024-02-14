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

const std::string GAMEOVER_HANDLE_PATH = {"./resource/gameMainResource/gameOver.png"};
const int GAMEOVER_PRINT_TIME = 500;//�Q�[���I�[�o�[�̕\������;

gameMainManager::gameMainManager(gameManager* ptrGM) : gameOverFlag(false){
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
	DeleteGraph(gameOverHandle);
}
bool gameMainManager::Awake() {
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

	gameOverHandle = LoadGraph(GAMEOVER_HANDLE_PATH.c_str());
	if (gameOverHandle == -1) {
		errorData data = { errorCode::handleRoadFail,errorSource::gameMainManager,(std::string*)nullptr };
		ChangeBlueScreen(&data);
		return false;
	}

	return true;
}
bool gameMainManager::Update(){
	if (!gameOverFlag) {//�Q�[���I�[�o�[����Ȃ��Ȃ�

		//�f�o�b�O�p;
		SetGameOver();
		//�f�o�b�O�p;


		for (manager* m : managers) {
			m->Update();
		}
	}else {
		if (gameOverPrintCnt-- < 0) {
			//title�ɖ߂�;
			sceneManager* newScene = new titleManager(ptrGameManager);
			sceneManager::ChangeNewScene(newScene);
			SetDrawBright(255, 255, 255);
			return true;
		}else {
			//�������P�x��������;
			int brightness = 255 * (((float)gameOverPrintCnt / GAMEOVER_PRINT_TIME * 0.875) + 0.125);
			SetDrawBright(brightness, brightness, brightness);
		}
		
	}
	return true;
}
void gameMainManager::Print() {
	for (manager* m : managers) {
		m->Print();
	}
	if (gameOverFlag) {//�Q�[���I�[�o�[�Ȃ�;
		DrawGraph(76,216,gameOverHandle, true);
	}
}

manager* gameMainManager::GetManagerPtr(const char* managerName) {
	std::string managerN = managerName;
	for (manager* m : managers) {
		if (managerN.compare(m->GetManagerNameInstans()) == 0) {
			return m;
		}
	}
	return nullptr;
}

void gameMainManager::ChangeBlueScreen(errorData* data) {
	sceneManager* newScene = new blueScreenManager(ptrGameManager, data);
	sceneManager::ChangeNewScene(newScene);
}

const inputData* gameMainManager::GetInputData() {
	inputManager* ptrim = (inputManager*)ptrGameManager->GetManagerPtr("inputManager");
	if (ptrim == nullptr) {
		return nullptr;
	}
	return ptrim->GetInputDataPtr();
}
void gameMainManager::SetGameOver() {
	gameOverPrintCnt = GAMEOVER_PRINT_TIME;
	gameOverFlag = true;
}