#include "enemyManager.h"

#include "enemy.h"
#include "enemyData.h"
#include "playerManager.h"
#include "gameMainManager.h"

#include "errorCode.h"

#include<string>
#include <DxLib.h>
#include <sstream>
#include <fstream>

using namespace std;

const string ENEMY_DATA_PATH = "./resource/gameMainResource/enemyResource/enemyData.txt";//敵データのパス;

enemyManager::enemyManager(gameMainManager* ptrGM) 
:ptrGameMain(ptrGM)
{
	manager::SetManagerName("enemyManager");
}
enemyManager::~enemyManager() {
	for (enemy* e :enemys) {
		delete e;
	}
	enemys.clear();
	for (enemyData* e : datas) {
		delete e;
	}
	datas.clear();
}
bool enemyManager::Awake() {
	//プレイヤーマネージャー取得;
	ptrPlayerManager = (playerManager*)ptrGameMain->GetManagerPtr("playerManager");
	if (ptrPlayerManager == nullptr) {
		errorData data = { errorCode::objectNotFound,errorSource::enemyManager ,nullptr};
		ptrGameMain->ChangeBlueScreen(&data);
		return false;
	}

	//ファイルを開く;
	ifstream ifs(ENEMY_DATA_PATH.c_str());
	if (ifs.fail()) {//失敗でブルスク;
		ifs.close();
		errorData data = { errorCode::fileNotFound,errorSource::enemyManager ,nullptr };
		ptrGameMain->ChangeBlueScreen(&data);
		return false;
	}

	string input;
	//敵種類取得;
	std::getline(ifs, input);
	stringstream inputSt(input);

	inputSt >> enemyTypeAmount;

	inputSt.clear(); inputSt.str("");//初期化;

	float msBuf;//移動速度のバッファ;
	float hpBuf;//hpのバッファ;
	float atkBuf;//攻撃力のバッファ;
	string pathBuf;
	for (int i = 0; i < enemyTypeAmount; i++) {
		//敵情報取得;
		std::getline(ifs, input);
		inputSt << input;

		//データをコピー;
		inputSt >> msBuf >> hpBuf>> atkBuf >> pathBuf;
		string* newPathBuf = new string(pathBuf);
		
		enemyData* ed = new enemyData;
		if (!ed->Load(msBuf, hpBuf, atkBuf,newPathBuf)) {
			//読んだデータが不正だったら;
			ifs.close();
			stringstream ss;
			ss << "ms" << msBuf << ",hp:" << hpBuf<<
				",atk:"<< atkBuf << ",path:" << newPathBuf;
			string* note = new string(ss.str());

			errorData data = { errorCode::improperData,errorSource::enemyManager ,note };
			ptrGameMain->ChangeBlueScreen(&data);
			return false;
		}

		datas.push_back(ed);

		inputSt.clear(); inputSt.str("");//初期化;
	}

	ifs.close();

	//画像読み込み;
	for (enemyData* e : datas) {
		if (!e->LoadImg()) {
			errorData data = { errorCode::handleRoadFail,errorSource::enemyManager ,nullptr };
			ptrGameMain->ChangeBlueScreen(&data);
			return false;
		}
	}

	Add(enemyType::e001, coordinate(0, 0));
	return true;
}
bool enemyManager::Update() {
	for (enemy* e : enemys) {
		//enemyUpdateは2つのパターンでfalseを返す;
		//1:enemyが死亡したパターン;
		//2:処理が失敗したパターン;
		if (!e->Update()) {
			//isEnemyがtrueだったら(enemyが生きてるのにfalseが返ってくるなら)エラー;
			if (e->GetIsEnemy()) {
				errorData data = { errorCode::processingFailure,errorSource::enemyManager ,nullptr };
				ptrGameMain->ChangeBlueScreen(&data);
				return false;
			}
		}
	}
	return true;
}
void enemyManager::Print() {
	for (enemy* e : enemys) {
		e->Print();
	}
	
}
bool enemyManager::Add(enemyType et, coordinate pos) {
	enemy* newEnemy;
	switch (et)
	{
	case enemyType::none:
		return false;
	case enemyType::e001:
		newEnemy = new enemy001(pos, this,datas[0]);
		break;
	default:
		break;
	}
	enemys.push_back(newEnemy);
	return true;
}

const player* enemyManager::GetPlayerPtr()const {
	return ptrPlayerManager->GetPlayerPtr();
}