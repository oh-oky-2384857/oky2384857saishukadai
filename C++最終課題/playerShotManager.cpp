#include <DxLib.h>
#include <math.h>
#include <string>
#include <sstream>
#include <fstream>

#include "playerManager.h"
#include "player.h"
#include "enemyManager.h"
#include "playerShotManager.h"
#include "playerShot.h"
#include "gameMainManager.h"
#include "inputDate.h"

#include "errorCode.h"

using namespace std;

const string PLAYER_SHOT_DATA_PATH = "./resource/gameMainResource/playerShotResource/psData.txt";
const int PLAYER_SHOT_MAX_AMOUNT = 256;//プレイヤーショットの最大存在数;
const int PLAYER_SHOT_AMOUNT_OVER_DELETE = 16;//プレイヤーショットが最大存在数を超えたときに消す数;

playerShotManager::playerShotManager(gameMainManager* ptrGM) 
:ptrGameMain(ptrGM){
	manager::SetManagerName("playerShotManager");
}
playerShotManager::~playerShotManager() {
	//shot削除;
	for (playerShotBase* ps : shots) {
		delete ps;
	}
	shots.clear();
	//shotData削除;
	for (shotPatternData* spd : shotPD) {
		//画像ハンドル削除;
		DeleteGraph(spd->handle);
		delete spd;
	}
	shotPD.clear();
}

bool playerShotManager::Awake() {
	//プレイヤーマネージャー取得;
	ptrPlayerManager = (playerManager*)ptrGameMain->GetManagerPtr("playerManager");
	if (ptrPlayerManager == nullptr) {
		errorData* data =new errorData { errorCode::objectNotFound,errorSource::playerShotManager ,"playerManagerがない" };
		throw data;
	}
	//エネミーマネージャー取得;
	ptrEnemyManager = (enemyManager*)ptrGameMain->GetManagerPtr("enemyManager");
	if (ptrEnemyManager == nullptr) {
		errorData* data = new errorData{ errorCode::objectNotFound,errorSource::playerShotManager ,"enemyManagerがない" };
		throw data;
	}
	//ファイルを開く;
	ifstream ifs(PLAYER_SHOT_DATA_PATH.c_str());
	if (ifs.fail()) {//失敗でブルスク;
		ifs.close();
		errorData* data = new errorData{ errorCode::fileNotFound,errorSource::playerShotManager ,"ShotDataがない" };
		throw data;
	}
	//データ読み込み;
	{
		string input;
		getline(ifs, input);
		stringstream inputs(input);

		inputs >> shotsCnt;

		//データ読み取り用バッファ;
		string pathBuf;

		for (int i = 0; i < shotsCnt; i++) {
			//初期化;
			input.clear();
			inputs.clear(); inputs.str("");
			
			getline(ifs, input);

			//stringstreamに入れる;
			inputs << input;

			shotPatternData* spd = new shotPatternData;
			inputs >> pathBuf;
			spd->handle = LoadGraph(pathBuf.c_str());

			if (spd->handle == -1) {//失敗でブルスク;
				ifs.close();
				string* note = new string(pathBuf);
				errorData* data = new errorData{ errorCode::handleRoadFail,errorSource::playerShotManager ,note };
				throw data;
			}
						
			inputs >> spd->moveSpeed >> spd->damageMultiplier >> spd->shotCoolTime;
			spd->type = (shotType)(i + 1);

			shotPD.push_back(spd);
		}
	}
	ifs.close();

	shots.clear();

	return true;
}
bool playerShotManager::Update() {
	for (playerShotBase* ps : shots) {
		if (ps->Update()) {
			shots.remove(ps);
			delete ps;
			break;
		}
	}
	
	return true;
}
void playerShotManager::Print() {
	for (playerShotBase* ps : shots) {
		ps->Print();
	}
}

bool playerShotManager::Add(shotData* data) {

	playerShotBase* ps;

	if (shots.size() > PLAYER_SHOT_MAX_AMOUNT) {//最大存在数を超えたら;
		for (int i = 0; i < PLAYER_SHOT_AMOUNT_OVER_DELETE; i++) {
			//一番古い弾を消す;
			playerShotBase* ps = shots.front();
			delete ps;
			shots.pop_front();
		}
	}

	switch (data->pData->type){
	case shotType::normal: 
		ps = new psNormal(data,this);
		break;
	default:
		return false;
	}

	shots.push_back(ps);



	return true;
}
const player* playerShotManager::GetPlayer() const{
	return ptrPlayerManager->GetPlayerPtr();
}
bool playerShotManager::CheckEnemyHit(shotData* s, int radius) {
	return ptrEnemyManager->ShotCheckHitEnemy(s, radius);
}
shotPatternData* playerShotManager::GetShotPatternData(int ptr) { 
	shotPatternData* spd = new shotPatternData;
	shotPD.push_back(spd);
	if (shotPD.size() > ptr) {
		return shotPD[ptr]; 
	}else {
		return nullptr;
	}
}