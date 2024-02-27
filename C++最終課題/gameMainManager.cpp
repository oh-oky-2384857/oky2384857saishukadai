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

//ゲームオーバーとゲームクリアの画像のパス;
const std::string GAMEOVER_HANDLE_PATH = {"./resource/gameMainResource/gameOver.png"};
const std::string GAMECLEAR_HANDLE_PATH = { "./resource/gameMainResource/gameClear.png" };
const int CHANGE_SCENE_TIME = 500;//シーンが変わるまでの時間;

const coordinate GAME_STATE_PRINT_POINT = {};

gameMainManager::gameMainManager(gameManager* ptrGM) : gamingFlag(true){
	sceneManager::ptrGameManager = ptrGM;
	manager::SetManagerName("gameMainManager");

	//各種マネージャ作成;
	managers ={
		new mapManager(this),
		new enemyManager(this),
		new playerManager(this),
		new playerShotManager(this),
	};

}
gameMainManager::~gameMainManager() {
	//各種マネージャ削除;
	for (manager* m : managers) {
		delete m;
	}
	managers.clear();

	//画像ハンドル削除;
	DeleteGraph(gameClearHandle);
	DeleteGraph(gameOverHandle);
}
bool gameMainManager::Awake() {
	//処理失敗時にはmainでエラーを受け取るため
	//ここでは何もしない

	ptrGameManager->SetGameStatus(gameStatus::main);
	
	//各種マネージャのAwakeを動かす;
	for (manager* m : managers) {
		m->Awake();
	}

	//各種マネージャのStartを動かす;
	for (manager* m : managers) {
		m->Start();
	}

	//画像読み込みに失敗したら;
	gameOverHandle = LoadGraph(GAMEOVER_HANDLE_PATH.c_str());
	if (gameOverHandle == -1) {//失敗でエラーコードを返す;
		errorData* data =new errorData { errorCode::handleRoadFail,errorSource::gameMainManager,(std::string*)nullptr };
		throw data;
	}
	//画像読み込みに失敗したら2;
	gameClearHandle = LoadGraph(GAMECLEAR_HANDLE_PATH.c_str());
	if (gameOverHandle == -1) {//失敗でエラーコードを返す;
		errorData* data =new errorData { errorCode::handleRoadFail,errorSource::gameMainManager,(std::string*)nullptr };
		throw data;
	}

	//正常終了;
	return true;
}
bool gameMainManager::Update(){
	if (gamingFlag) {//ゲームが続いているなら;
		//更新処理;
		for (manager* m : managers) {
			m->Update();
		}

	}else {
		//カウント減少;
		if (changeSceneCnt-- < 0) {//カウントが0になったら;
			//シーン偏移;
			sceneManager::ChangeNewScene(nextScene);
			//輝度を戻す;
			SetDrawBright(255, 255, 255);
			return true;
		}else {
			//時間経過で少しずつ輝度を下げる;
			int brightness = 255 * (((float)changeSceneCnt / CHANGE_SCENE_TIME * 0.875) + 0.125);
			SetDrawBright(brightness, brightness, brightness);
		}
		
	}
	return true;
}
void gameMainManager::Print() {
	//描画処理;
	for (manager* m : managers) {
		m->Print();
	}
	if (!gamingFlag) {//ゲームが続いていないなら;
		DrawGraph(76,216, gameStateHandle, true);
	}
}

manager* gameMainManager::GetManagerPtr(const char* managerName) {
	std::string managerN = managerName;
	for (manager* m : managers) {
		//マネージャーネームが一致したら;
		if (managerN.compare(m->GetManagerNameInstans()) == 0) {
			return m;
		}
	}
	return nullptr;
}

void gameMainManager::ChangeBlueScreen(errorData* data) {
	//ブルースクリーンに偏移;
	sceneManager* newScene = new blueScreenManager(ptrGameManager, data);
	sceneManager::ChangeNewScene(newScene);
}

const inputData* gameMainManager::GetInputData() {
	//inputData取得;
	inputManager* ptrim = (inputManager*)ptrGameManager->GetManagerPtr("inputManager");
	if (ptrim == nullptr) {
		return nullptr;
	}
	return ptrim->GetInputDataPtr();
}
void gameMainManager::SetGameOver() {
	//シーン偏移時間設定;
	changeSceneCnt = CHANGE_SCENE_TIME;
	//フラグ変更;
	gamingFlag = false;
	//次のシーン生成
	nextScene = new titleManager(ptrGameManager);
	//画像ハンドル設定;
	gameStateHandle = gameOverHandle;
}
void gameMainManager::SetGameClear() {
	//シーン偏移時間設定;
	changeSceneCnt = CHANGE_SCENE_TIME;
	//フラグ変更;
	gamingFlag = false;
	//次のシーン生成
	nextScene = new titleManager(ptrGameManager);
	//画像ハンドル設定;
	gameStateHandle = gameClearHandle;
}