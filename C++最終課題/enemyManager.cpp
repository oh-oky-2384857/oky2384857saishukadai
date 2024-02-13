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

const string ENEMY_DATA_PATH = "./resource/gameMainResource/enemyResource/enemyData.txt";//�G�f�[�^�̃p�X;

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
	//�v���C���[�}�l�[�W���[�擾;
	ptrPlayerManager = (playerManager*)ptrGameMain->GetManagerPtr("playerManager");
	if (ptrPlayerManager == nullptr) {
		errorData data = { errorCode::objectNotFound,errorSource::enemyManager ,nullptr};
		ptrGameMain->ChangeBlueScreen(&data);
		return false;
	}

	//�t�@�C�����J��;
	ifstream ifs(ENEMY_DATA_PATH.c_str());
	if (ifs.fail()) {//���s�Ńu���X�N;
		ifs.close();
		errorData data = { errorCode::fileNotFound,errorSource::enemyManager ,nullptr };
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
		inputSt >> msBuf >> hpBuf>> atkBuf >> pathBuf;
		string* newPathBuf = new string(pathBuf);
		
		enemyData* ed = new enemyData;
		if (!ed->Load(msBuf, hpBuf, atkBuf,newPathBuf)) {
			//�ǂ񂾃f�[�^���s����������;
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

		inputSt.clear(); inputSt.str("");//������;
	}

	ifs.close();

	//�摜�ǂݍ���;
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
		//enemyUpdate��2�̃p�^�[����false��Ԃ�;
		//1:enemy�����S�����p�^�[��;
		//2:���������s�����p�^�[��;
		if (!e->Update()) {
			//isEnemy��true��������(enemy�������Ă�̂�false���Ԃ��Ă���Ȃ�)�G���[;
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