#include "enemyManager.h"

#include "enemy.h"
#include "enemyData.h"
#include "playerManager.h"
#include "player.h"
#include "gameMainManager.h"
#include "shotData.h"

#include "errorCode.h"

#include <string>
#include <DxLib.h>
#include <sstream>
#include <fstream>

using namespace std;

const string ENEMY_DATA_PATH = "./resource/gameMainResource/enemyResource/enemyData.txt";//敵データのパス;
const string ENEMY_WAVE_DATA_PATH = "./resource/gameMainResource/enemyResource/enemyWaveData.txt";//敵ウェーブデータのパス;

const int ENEMY_ADD_POSITION_RAND_X[2] = {320 + 20,640 + 20};//敵が湧ける範囲のX;
const int ENEMY_ADD_POSITION_RAND_Y[2] = {240 + 20,480 + 20};//                Y;

enemyManager::enemyManager(gameMainManager* ptrGM) 
:ptrGameMain(ptrGM),enemyWaveAddCnt(0)
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
	for (std::vector<enemyWavePiece*> w : waves) {
		for (enemyWavePiece* e : w) {
			delete e;
		}
		w.clear();
	}
	waves.clear();
}
errorData* enemyManager::Awake() {
	//プレイヤーマネージャー取得;
	ptrPlayerManager = (playerManager*)ptrGameMain->GetManagerPtr("playerManager");
	if (ptrPlayerManager == nullptr) {
		errorData* data =new errorData { errorCode::objectNotFound,errorSource::enemyManager ,"playerManagerがない"};
		return data;
	}

	//敵データ読み込み
	{
		//ファイルを開く;
		ifstream ifs(ENEMY_DATA_PATH.c_str());
		if (ifs.fail()) {//失敗でブルスク;
			ifs.close();
			errorData* data = new errorData{ errorCode::fileNotFound,errorSource::enemyManager ,"enemyDateのファイルがない" };
			return data;
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
			inputSt >> msBuf >> hpBuf >> atkBuf >> pathBuf;
			string* newPathBuf = new string(pathBuf);

			enemyData* ed = new enemyData;
			if (!ed->Load(msBuf, hpBuf, atkBuf, newPathBuf)) {
				//読んだデータが不正だったらブルスク;
				ifs.close();
				stringstream ss;
				ss << "ms" << msBuf << ",hp:" << hpBuf <<
					",atk:" << atkBuf << ",path:" << newPathBuf;
				string* note = new string(ss.str());

				errorData* data =new errorData { errorCode::improperData,errorSource::enemyManager ,note };
				return data;
			}

			datas.push_back(ed);

			inputSt.clear(); inputSt.str("");//初期化;
		}

		ifs.close();

	}
	//敵データ読み込み

	//敵ウェーブデータ読み込み;
	{
		//ファイルを開く;
		ifstream ifs(ENEMY_WAVE_DATA_PATH.c_str());
		if (ifs.fail()) {//失敗でブルスク;
			ifs.close();
			errorData* data = new errorData{ errorCode::fileNotFound,errorSource::enemyManager ,"enemyWaveDataのファイルがない" };
			return data;
		}

		string input;
		//ウェーブ数,ウェーブ間隔取得;
		std::getline(ifs, input);
		stringstream inputSt(input);

		inputSt >> waveAmount >> waveAddTime;
	
		int enemyTypeBuf;
		int enemyTypeNum;
		for (int i = 0; i < waveAmount; i++) {
			inputSt.clear(); inputSt.str("");//初期化;
			vector<enemyWavePiece*> enemyWaves;
			
			//敵種類,数取得;
			std::getline(ifs, input);
			inputSt << input;
			//敵種類;
			inputSt >> enemyTypeNum;
			for (int j = 0; j < enemyTypeNum; j++) {
				enemyWavePiece* oew = new enemyWavePiece;
				inputSt >> enemyTypeBuf >> oew->amount;
				oew->t = (enemyType)enemyTypeBuf;
				enemyWaves.push_back(oew);
			}

			waves.push_back(enemyWaves);
		}
	}
	//敵ウェーブデータ読み込み;

	//画像読み込み;
	for (enemyData* e : datas) {
		if (!e->LoadImg()) {
			errorData* data = new errorData{ errorCode::handleRoadFail,errorSource::enemyManager ,(string*)nullptr };
			return data;
		}
	}

	return nullptr;
}
bool enemyManager::Update() {
	for (enemy* e : enemys) {
		//enemyUpdateは2つのパターンでfalseを返す;
		//1:enemyが死亡したパターン;
		//2:処理が失敗したパターン;
		if (!e->Update()) {
			//isEnemyがtrueだったら(enemyが生きてるのにfalseが返ってくるなら)エラー;
			if (e->GetIsEnemy()) {
				errorData data = { errorCode::processingFailure,errorSource::enemyManager ,(string*)nullptr };
				ptrGameMain->ChangeBlueScreen(&data);
				return false;
			}
		}
	}
	//敵追加カウント減少;
	enemyWaveAddCnt--;
	if (enemyWaveAddCnt < 0) {
		//敵追加カウントリセット;
		enemyWaveAddCnt = waveAddTime;
		if (waves.size() != 0) {//ウェーブが残っているなら;
			
			std::vector<enemyWavePiece*> wave = waves[0];//先頭取り出し;
			waves.erase(waves.begin());//先頭を削除;

			//プレイヤーの座標取得;
			const player* p = ptrPlayerManager->GetPlayerPtr();
			coordinate pcoord = p->GetPos();

			//ウェーブ内の敵種類;
			int waveEnemysType = wave.size();
			for (int i = 0; i < waveEnemysType; i++) {
				for (int j = 0; j < wave[i]->amount; j++) {

					int x = GetRand(ENEMY_ADD_POSITION_RAND_X[1] - ENEMY_ADD_POSITION_RAND_X[0]) + ENEMY_ADD_POSITION_RAND_X[0];
					int y = GetRand(ENEMY_ADD_POSITION_RAND_Y[1] - ENEMY_ADD_POSITION_RAND_Y[0]) + ENEMY_ADD_POSITION_RAND_Y[0];

					int sx = GetRand(1) * 2 - 1;
					int sy = GetRand(1) * 2 - 1;


					coordinate coord = { x * sx + pcoord.x ,y * sy + pcoord.y };


					Add(wave[i]->t, coord);
				}
				delete wave[i];
			}

			wave.clear();
		}
	}

	//敵ウェーブをすべて倒したら;
	if (waves.size() == 0 && enemys.size() == 0) {
		ptrGameMain->SetGameClear();
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
	case enemyType::e002:
		newEnemy = new enemy002(pos, this, datas[1]);
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
bool enemyManager::ShotCheckHitEnemy(shotData* s, int radius) {
	if (enemys.size() == 0) {
		return false;
	}
	for (enemy* e : enemys) {
		if (e->CheckHit(s->position, radius)) {
			if (e->AddDamage(s->damage)) {
				enemys.remove(e);
				delete e;
			}
			return true;
		}
	}
	return false;
}
