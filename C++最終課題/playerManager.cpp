#include <DxLib.h>
#include <string>
#include "playerManager.h"
#include "player.h"
#include "gameMainManager.h"
#include "gameCommon.h"
#include "inputDate.h"
#include "shotData.h"
#include "playerShotManager.h"

#include "errorCode.h"

playerManager::playerManager(gameMainManager* ptrGM) 
	:ptrGameMain(ptrGM),nowShotData(nullptr){
	//����;
	oplayer = new player(coordinate(0,0));
	
	manager::SetManagerName("playerManager");
}
playerManager::~playerManager() {
	delete oplayer;
}

bool playerManager::Awake() {
	//playerShotManager�擾;
	ptrPlayerShotManager = (playerShotManager*)ptrGameMain->GetManagerPtr("playerShotManager");
	if (ptrPlayerShotManager == nullptr) {
		errorData* data =new errorData { errorCode::objectNotFound, errorSource::playerManager ,"�v���C���[�V���b�g���Ȃ�" };
		throw data;
	}
	//�C���v�b�g�f�[�^�擾;
	//move;
	moveInput = ptrGameMain->GetInputData()->move;
	if (moveInput == nullptr) {
		errorData* data = new errorData{ errorCode::objectNotFound, errorSource::playerManager ,"moveInput���Ȃ�" };
		throw data;
	}
	//shot;
	shotInput = ptrGameMain->GetInputData()->shot;
	if (shotInput == nullptr) {
		errorData* data = new errorData{ errorCode::objectNotFound,errorSource::playerShotManager ,"shotInput���Ȃ�" };
		throw data;
	}
	//�v���C���[Awake����;
	oplayer->Awake();
	//�摜�ǂݍ���;
	if (!oplayer->LoadPlayerHandle()) {
		errorData* data = new errorData{ errorCode::handleRoadFail, errorSource::playerManager ,(std::string*)nullptr };
		throw data;
	}
	//�X�e�[�^�X�ǂݍ���;
	if (!oplayer->LoadStatus()) {
		errorData* data = new errorData{ errorCode::fileNotFound, errorSource::playerManager ,"playerDate�t�@�C�����Ȃ�" };
		throw data;
	}

	return true;
}
bool playerManager::Start() {
	nowShotData = ptrPlayerShotManager->GetShotPatternData(0);
	if (nowShotData == nullptr) {
		errorData* data =new errorData { errorCode::objectNotFound,errorSource::playerShotManager ,"�����e�f�[�^���Ȃ�" };
		throw data;
	}
	return true;
}
bool playerManager::Update() {
	oplayer->AddMovePower(moveInput->xPower, moveInput->yPower);
	if (!oplayer->Update()) {//hp��0�ɂȂ�����;
		ptrGameMain->SetGameOver();
		return false;
	}

	shotCoolTimeCnt--;
	//shot�̃{�^����������A�N�[���^�C���������Ă���Ȃ�;
	if (shotInput->isTrigger && shotCoolTimeCnt < 0) {
		
		shotCoolTimeCnt = nowShotData->shotCoolTime;

		//�V���b�g�쐬;

		//�x�N�g�����m�[�}���C�Y
		vector2 v2;
		int x = shotInput->x - SCREEN_WIDTH / 2;
		int y = shotInput->y - SCREEN_HEIGHT / 2;
		int hypotenuse = sqrt(x * x + y * y);
		v2.x = (float)x / hypotenuse * -1;
		v2.y = (float)y / hypotenuse * -1;

		coordinate cd = oplayer->GetPos();

		shotData* data = new shotData(cd, v2, oplayer->GetAtk(), nowShotData);
		
		ptrPlayerShotManager->Add(data);
	}
	return true;

}
void playerManager::Print() {
	oplayer->Print();
}

void playerManager::AddDamage(int damage) {
	if (!oplayer->AddDamage(damage)) {//Hp��0�ȉ��ɂȂ����Ȃ�;

	}
}