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

using namespace std;

const string PLAYER_SHOT_DATA_PATH = "./resource/gameMainResource/playerShotResource/psData.txt";
const int PLAYER_SHOT_MAX_AMOUNT = 256;//�v���C���[�V���b�g�̍ő呶�ݐ�;
const int PLAYER_SHOT_AMOUNT_OVER_DELETE = 16;//�v���C���[�V���b�g���ő呶�ݐ��𒴂����Ƃ��ɏ�����;

playerShotManager::playerShotManager(gameMainManager* ptrGM) 
:ptrGameMain(ptrGM){
	manager::SetManagerName("playerShotManager");
}
playerShotManager::~playerShotManager() {
	//shot�폜;
	for (playerShotBase* ps : shots) {
		delete ps;
	}
	shots.clear();
	//shotData�폜;
	for (shotPatternData* spd : shotPD) {
		//�摜�n���h���폜;
		DeleteGraph(spd->handle);
		delete spd;
	}
	shotPD.clear();
}

errorData* playerShotManager::Awake() {
	//�v���C���[�}�l�[�W���[�擾;
	ptrPlayerManager = (playerManager*)ptrGameMain->GetManagerPtr("playerManager");
	if (ptrPlayerManager == nullptr) {
		errorData* data =new errorData { errorCode::objectNotFound,errorSource::playerShotManager ,"playerManager���Ȃ�" };
		return data;
	}
	//�G�l�~�[�}�l�[�W���[�擾;
	ptrEnemyManager = (enemyManager*)ptrGameMain->GetManagerPtr("enemyManager");
	if (ptrEnemyManager == nullptr) {
		errorData* data = new errorData{ errorCode::objectNotFound,errorSource::playerShotManager ,"enemyManager���Ȃ�" };
		return data;
	}
	//�t�@�C�����J��;
	ifstream ifs(PLAYER_SHOT_DATA_PATH.c_str());
	if (ifs.fail()) {//���s�Ńu���X�N;
		ifs.close();
		errorData* data = new errorData{ errorCode::fileNotFound,errorSource::playerShotManager ,"ShotData���Ȃ�" };
		return data;
	}
	//�f�[�^�ǂݍ���;
	{
		string input;
		getline(ifs, input);
		stringstream inputs(input);

		inputs >> shotsCnt;

		//�f�[�^�ǂݎ��p�o�b�t�@;
		string pathBuf;

		for (int i = 0; i < shotsCnt; i++) {
			//������;
			input.clear();
			inputs.clear(); inputs.str("");
			
			getline(ifs, input);

			//stringstream�ɓ����;
			inputs << input;

			shotPatternData* spd = new shotPatternData;
			inputs >> pathBuf;
			spd->handle = LoadGraph(pathBuf.c_str());

			if (spd->handle == -1) {//���s�Ńu���X�N;
				ifs.close();
				string* note = new string(pathBuf);
				errorData* data = new errorData{ errorCode::handleRoadFail,errorSource::playerShotManager ,note };
				return data;
			}
						
			inputs >> spd->moveSpeed >> spd->damageMultiplier >> spd->shotCoolTime;
			spd->type = (shotType)(i + 1);

			shotPD.push_back(spd);
		}
	}
	ifs.close();

	shots.clear();

	return nullptr;
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

	if (shots.size() > PLAYER_SHOT_MAX_AMOUNT) {//�ő呶�ݐ��𒴂�����;
		for (int i = 0; i < PLAYER_SHOT_AMOUNT_OVER_DELETE; i++) {
			//��ԌÂ��e������;
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