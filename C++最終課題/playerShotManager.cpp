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
const int PLAYER_SHOT_MAX_AMOUNT = 256;//�v���C���[�V���b�g�̍ő呶�ݐ�;
const int PLAYER_SHOT_AMOUNT_OVER_DELETE = 16;//�v���C���[�V���b�g���ő呶�ݐ��𒴂����Ƃ��ɏ�����;

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
	//�v���C���[�}�l�[�W���[�擾;
	ptrPlayerManager = (playerManager*)ptrGameMain->GetManagerPtr("playerManager");
	if (ptrPlayerManager == nullptr) {
		errorData data = { errorCode::objectNotFound,errorSource::playerShotManager ,"playerManager���Ȃ�" };
		ptrGameMain->ChangeBlueScreen(&data);
		return false;
	}
	//�G�l�~�[�}�l�[�W���[�擾;
	ptrEnemyManager = (enemyManager*)ptrGameMain->GetManagerPtr("enemyManager");
	if (ptrEnemyManager == nullptr) {
		errorData data = { errorCode::objectNotFound,errorSource::playerShotManager ,"enemyManager���Ȃ�" };
		ptrGameMain->ChangeBlueScreen(&data);
		return false;
	}
	//�t�@�C�����J��;
	ifstream ifs(PLAYER_SHOT_DATA_PATH.c_str());
	if (ifs.fail()) {//���s�Ńu���X�N;
		ifs.close();
		errorData data = { errorCode::fileNotFound,errorSource::playerShotManager ,"ShotData���Ȃ�" };
		ptrGameMain->ChangeBlueScreen(&data);
		return false;
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
	
	return true;
}
void playerShotManager::Print() {
	for (playerShot* ps : shots) {
		ps->Print();
	}
}

bool playerShotManager::Add(shotData* data) {

	playerShot* ps;

	if (shots.size() > PLAYER_SHOT_MAX_AMOUNT) {//�ő呶�ݐ��𒴂�����;
		for (int i = 0; i < PLAYER_SHOT_AMOUNT_OVER_DELETE; i++) {
			//��ԌÂ��e������;
			playerShot* ps = shots.front();
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