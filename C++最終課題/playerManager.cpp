#include <DxLib.h>
#include <string>
#include "playerManager.h"
#include "player.h"
#include "gameMainManager.h"
#include "gameCommon.h"
#include "inputDate.h"
#include "shotData.h"
#include "playerShotManager.h"

playerManager::playerManager(gameMainManager* ptrGM) 
	:ptrGameMain(ptrGM),nowShotData(nullptr){
	//生成;
	oplayer = new player(coordinate(0,0));
	
	manager::SetManagerName("playerManager");
}
playerManager::~playerManager() {
	delete oplayer;
}

errorData* playerManager::Awake() {
	//playerShotManager取得;
	ptrPlayerShotManager = (playerShotManager*)ptrGameMain->GetManagerPtr("playerShotManager");
	if (ptrPlayerShotManager == nullptr) {
		errorData* data =new errorData { errorCode::objectNotFound, errorSource::playerManager ,"プレイヤーショットがない" };
		return data;
	}
	//インプットデータ取得;
	//move;
	moveInput = ptrGameMain->GetInputData()->move;
	if (moveInput == nullptr) {
		errorData* data = new errorData{ errorCode::objectNotFound, errorSource::playerManager ,"moveInputがない" };
		return data;
	}
	//shot;
	shotInput = ptrGameMain->GetInputData()->shot;
	if (shotInput == nullptr) {
		errorData* data = new errorData{ errorCode::objectNotFound,errorSource::playerShotManager ,"shotInputがない" };
		return data;
	}
	//プレイヤーAwake処理;
	oplayer->Awake();
	//画像読み込み;
	if (!oplayer->LoadPlayerHandle()) {
		errorData* data = new errorData{ errorCode::handleRoadFail, errorSource::playerManager ,(std::string*)nullptr };
		return data;
	}
	//ステータス読み込み;
	if (!oplayer->LoadStatus()) {
		errorData* data = new errorData{ errorCode::fileNotFound, errorSource::playerManager ,"playerDateファイルがない" };
		return data;
	}

	return nullptr;
}
errorData* playerManager::Start() {
	nowShotData = ptrPlayerShotManager->GetShotPatternData(0);
	if (nowShotData == nullptr) {
		errorData* data =new errorData { errorCode::objectNotFound,errorSource::playerShotManager ,"初期弾データがない" };
		return data;
	}
	return nullptr;
}
bool playerManager::Update() {
	oplayer->AddMovePower(moveInput->xPower, moveInput->yPower);
	if (!oplayer->Update()) {//hpが0になったら;
		ptrGameMain->SetGameOver();
		return false;
	}

	shotCoolTimeCnt--;
	//shotのボタンが押され、クールタイムがあけているなら;
	if (shotInput->isTrigger && shotCoolTimeCnt < 0) {
		
		shotCoolTimeCnt = nowShotData->shotCoolTime;

		//ショット作成;

		//ベクトルをノーマライズ
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
	if (!oplayer->AddDamage(damage)) {//Hpが0以下になったなら;

	}
}