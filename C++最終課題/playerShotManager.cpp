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
	for (playerShot* ps : shots) {
		delete ps;
	}
	shots.clear();
	for (shotPatternData* spd : shotPD) {
		delete spd;
	}
	shotPD.clear();
	for (int i = 0; i < shotsCnt;i++) {
		DeleteGraph(i);
	}
}

bool playerShotManager::Awake() {
	//プレイヤーマネージャー取得;
	ptrPlayerManager = (playerManager*)ptrGameMain->GetManagerPtr("playerManager");
	if (ptrPlayerManager == nullptr) {
		errorData data = { errorCode::objectNotFound,errorSource::playerShotManager ,"playerManagerがない" };
		ptrGameMain->ChangeBlueScreen(&data);
		return false;
	}
	//エネミーマネージャー取得;
	ptrEnemyManager = (enemyManager*)ptrGameMain->GetManagerPtr("enemyManager");
	if (ptrEnemyManager == nullptr) {
		errorData data = { errorCode::objectNotFound,errorSource::playerShotManager ,"enemyManagerがない" };
		ptrGameMain->ChangeBlueScreen(&data);
		return false;
	}
	//インプットデータ取得;
	shotInput = ptrGameMain->GetInputData()->shot;
	if (shotInput == nullptr) {
		errorData data = { errorCode::objectNotFound,errorSource::playerShotManager ,"shotInputがない" };
		ptrGameMain->ChangeBlueScreen(&data);
		return false;
	}
	//ファイルを開く;
	ifstream ifs(PLAYER_SHOT_DATA_PATH.c_str());
	if (ifs.fail()) {//失敗でブルスク;
		ifs.close();
		errorData data = { errorCode::fileNotFound,errorSource::playerShotManager ,"ShotDataがない" };
		ptrGameMain->ChangeBlueScreen(&data);
		return false;
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
				errorData data = { errorCode::handleRoadFail,errorSource::playerShotManager ,note };
				ptrGameMain->ChangeBlueScreen(&data);
				return false;
			}
						
			inputs >> spd->moveSpeed >> spd->damageMultiplier >> spd->shotCoolTime;
			spd->type = (shotType)(i + 1);

			shotPD.push_back(spd);
		}
	}
	ifs.close();

	shots.clear();

	//発射する弾をnormalに設定;

	nowShotData = shotPD[0];

	return true;
}
bool playerShotManager::Update() {
	for (playerShot* ps : shots) {
		if (ps->Update()) {
			shots.remove(ps);
			delete ps;
			break;
		}
	}
	shotCoolTimeCnt--;
	if (shotInput->isTrigger && shotCoolTimeCnt < 0) {
		if (shots.size() > PLAYER_SHOT_MAX_AMOUNT) {//最大存在数を超えたら;
			for (int i = 0; i < PLAYER_SHOT_AMOUNT_OVER_DELETE; i++) {
				playerShot* ps = shots.front();
				delete ps;
				shots.pop_front();
			}
		}
		shotCoolTimeCnt = nowShotData->shotCoolTime;

		//ショット作成;

		//ベクトルをノーマライズ
		vector2 v2;
		int x = shotInput->x - SCREEN_WIDTH / 2;
		int y = shotInput->y - SCREEN_HEIGHT / 2;
		int hypotenuse = sqrt(x * x + y * y);
		v2.x = (float)x / hypotenuse * -1;
		v2.y = (float)y / hypotenuse * -1;

		const player* ptrP = ptrPlayerManager->GetPlayerPtr();

		coordinate cd = ptrP->GetPos();

		shotData* data = new shotData(cd, v2, ptrP->GetAtk(), nowShotData);
		Add(data);
	}
	return true;
}
void playerShotManager::Print() {
	for (playerShot* ps : shots) {
		ps->Print();
	}
}

bool playerShotManager::Add(shotData* data) {

	playerShot* ps;

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