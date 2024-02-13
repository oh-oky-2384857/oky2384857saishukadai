#include <DxLib.h>
#include <string>
#include "playerManager.h"
#include "player.h"
#include "gameMainManager.h"
#include "gameCommon.h"
#include "blueScreen.h"
#include "errorCode.h"
#include "inputDate.h"


playerManager::playerManager(gameMainManager* ptrGM) 
	:ptrGameMain(ptrGM){
	//����;
	oplayer = new player(coordinate(0,0));
	
	manager::SetManagerName("playerManager");
}
playerManager::~playerManager() {
}

bool playerManager::Awake() {
	moveInput = ptrGameMain->GetInputDate()->move;
	if (moveInput == nullptr) {
		errorData data = { errorCode::objectNotFound, errorSource::playerManager };
		ptrGameMain->ChangeBlueScreen(&data);
		return false;
	}
	oplayer->Awake();
	if (!oplayer->LoadPlayerHandle()) {
		errorData data = { errorCode::handleRoadFail, errorSource::playerManager };
		ptrGameMain->ChangeBlueScreen(&data);
		return false;
	}
	if (!oplayer->LoadStatus()) {
		errorData data = { errorCode::fileNotFound, errorSource::playerManager };
		ptrGameMain->ChangeBlueScreen(&data);
		return false;
	}

	return true;
}
bool playerManager::Update() {
	oplayer->AddMovePower(moveInput->xPower, moveInput->yPower);
	oplayer->Update();
	return true;

}
void playerManager::Print() {
	oplayer->Print();
}

const coordinate playerManager::GetPosition() {
	return oplayer->GetPos();
}

void playerManager::AddDamage(int damage) {
	if (!oplayer->AddDamage(damage)) {//Hp��0�ȉ��ɂȂ����Ȃ�;

	}
}