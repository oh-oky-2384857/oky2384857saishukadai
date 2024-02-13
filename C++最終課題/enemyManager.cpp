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

const string ENEMY_DATA_PATH = "./resource/gameMainResource/enemyResource/enemyData.txt";//�G�f�[�^�̃p�X;
const string ENEMY_WAVE_DATA_PATH = "./resource/gameMainResource/enemyResource/enemyWaveData.txt";//�G�E�F�[�u�f�[�^�̃p�X;

const int ENEMY_ADD_POSITION_RAND_X[2] = {320 + 20,640 + 20};//�G���N����͈͂�X;
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
	for (std::vector<enemyWave*> w : waves) {
		for (enemyWave* e : w) {
			delete e;
		}
		w.clear();
	}
	waves.clear();
}
bool enemyManager::Awake() {
	//�v���C���[�}�l�[�W���[�擾;
	ptrPlayerManager = (playerManager*)ptrGameMain->GetManagerPtr("playerManager");
	if (ptrPlayerManager == nullptr) {
		errorData data = { errorCode::objectNotFound,errorSource::enemyManager ,"playerManager���Ȃ�"};
		ptrGameMain->ChangeBlueScreen(&data);
		return false;
	}

	//�G�f�[�^�ǂݍ���
	{
		//�t�@�C�����J��;
		ifstream ifs(ENEMY_DATA_PATH.c_str());
		if (ifs.fail()) {//���s�Ńu���X�N;
			ifs.close();
			errorData data = { errorCode::fileNotFound,errorSource::enemyManager ,"enemyDate�̃t�@�C�����Ȃ�" };
			ptrGameMain->ChangeBlueScreen(&data);
			return false;
		}

		string input;
		//�G��ގ擾;
		std::getline(ifs, input);
		stringstream inputSt(input);

		inputSt >> enemyTypeAmount;

		inputSt.clear(); inputSt.str("");//������;

		float msBuf;//�ړ����x�̃o�b�t�@;
		float hpBuf;//hp�̃o�b�t�@;
		float atkBuf;//�U���͂̃o�b�t�@;
		string pathBuf;
		for (int i = 0; i < enemyTypeAmount; i++) {
			//�G���擾;
			std::getline(ifs, input);
			inputSt << input;

			//�f�[�^���R�s�[;
			inputSt >> msBuf >> hpBuf >> atkBuf >> pathBuf;
			string* newPathBuf = new string(pathBuf);

			enemyData* ed = new enemyData;
			if (!ed->Load(msBuf, hpBuf, atkBuf, newPathBuf)) {
				//�ǂ񂾃f�[�^���s����������u���X�N;
				ifs.close();
				stringstream ss;
				ss << "ms" << msBuf << ",hp:" << hpBuf <<
					",atk:" << atkBuf << ",path:" << newPathBuf;
				string* note = new string(ss.str());

				errorData data = { errorCode::improperData,errorSource::enemyManager ,note };
				ptrGameMain->ChangeBlueScreen(&data);
				return false;
			}

			datas.push_back(ed);

			inputSt.clear(); inputSt.str("");//������;
		}

		ifs.close();

	}
	//�G�f�[�^�ǂݍ���

	//�G�E�F�[�u�f�[�^�ǂݍ���;
	{
		//�t�@�C�����J��;
		ifstream ifs(ENEMY_WAVE_DATA_PATH.c_str());
		if (ifs.fail()) {//���s�Ńu���X�N;
			ifs.close();
			errorData data = { errorCode::fileNotFound,errorSource::enemyManager ,"enemyWaveData�̃t�@�C�����Ȃ�" };
			ptrGameMain->ChangeBlueScreen(&data);
			return false;
		}

		string input;
		//�E�F�[�u��,�E�F�[�u�Ԋu�擾;
		std::getline(ifs, input);
		stringstream inputSt(input);

		inputSt >> waveAmount >> waveAddTime;
	
		int enemyTypeBuf;
		int enemyTypeNum;
		for (int i = 0; i < waveAmount; i++) {
			inputSt.clear(); inputSt.str("");//������;
			vector<enemyWave*> enemyWaves;
			
			//�G���,���擾;
			std::getline(ifs, input);
			inputSt << input;
			//�G���;
			inputSt >> enemyTypeNum;
			for (int j = 0; j < enemyTypeNum; j++) {
				enemyWave* oew = new enemyWave;
				inputSt >> enemyTypeBuf >> oew->amount;
				oew->t = (enemyType)enemyTypeBuf;
				enemyWaves.push_back(oew);
			}

			waves.push_back(enemyWaves);
		}
	}
	//�G�E�F�[�u�f�[�^�ǂݍ���;

	//�摜�ǂݍ���;
	for (enemyData* e : datas) {
		if (!e->LoadImg()) {
			errorData data = { errorCode::handleRoadFail,errorSource::enemyManager ,(string*)nullptr };
			ptrGameMain->ChangeBlueScreen(&data);
			return false;
		}
	}

	return true;
}
bool enemyManager::Update() {
	for (enemy* e : enemys) {
		//enemyUpdate��2�̃p�^�[����false��Ԃ�;
		//1:enemy�����S�����p�^�[��;
		//2:���������s�����p�^�[��;
		if (!e->Update()) {
			//isEnemy��true��������(enemy�������Ă�̂�false���Ԃ��Ă���Ȃ�)�G���[;
			if (e->GetIsEnemy()) {
				errorData data = { errorCode::processingFailure,errorSource::enemyManager ,(string*)nullptr };
				ptrGameMain->ChangeBlueScreen(&data);
				return false;
			}
		}
	}
	enemyWaveAddCnt--;
	if (enemyWaveAddCnt < 0) {
		enemyWaveAddCnt = waveAddTime;
		if (waves.size() != 0) {//�E�F�[�u���c���Ă���Ȃ�;
			//�擪���o��;
			std::vector<enemyWave*> wave = waves[0];
			waves.erase(waves.begin());

			const player* p = ptrPlayerManager->GetPlayerPtr();
			coordinate pcoord = p->GetPos();

			int waveEnemys = wave.size();
			for (int i = 0; i < waveEnemys; i++) {
				for (int j = 0; j < wave[i]->amount; j++) {
					
					int x = GetRand(ENEMY_ADD_POSITION_RAND_X[1] - ENEMY_ADD_POSITION_RAND_X[0]) + ENEMY_ADD_POSITION_RAND_X[0];
					int y = GetRand(ENEMY_ADD_POSITION_RAND_Y[1] - ENEMY_ADD_POSITION_RAND_Y[0]) + ENEMY_ADD_POSITION_RAND_Y[0];

					int sx = GetRand(1) * 2 - 1;
					int sy = GetRand(1)  * 2- 1;


					coordinate coord = {x * sx ,y * sy};


					Add(wave[i]->t, coord + pcoord);
				}
			}

			wave.clear();
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
