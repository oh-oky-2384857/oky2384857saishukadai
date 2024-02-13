#include <string>
#include <DxLib.h>

#include "mapManager.h"
#include "gameMainManager.h"
#include "blueScreen.h"
#include "errorCode.h"
#include "gameCommon.h"
#include "player.h"
#include "playerManager.h"

using namespace std;

const string MAPCHIP_HANDLE_PATH =
{"./resource/gameMainResource/mapResource/backGround01.png"};

const int MAPCHIP_WIDTH_AMOUNT = 4;	//�}�b�v�`�b�v�����ɍő剽�����Ԃ�;
const int MAPCHIP_HEIGHT_AMOUNT = 3;//�}�b�v�`�b�v���c�ɍő剽�����Ԃ�;

const int MAPCHIP_WIDTH = 256;//�}�b�v�`�b�v�̉摜�̕�;
const int MAPCHIP_HEIGHT = 256;//�}�b�v�`�b�v�̉摜�̍���;


mapManager::mapManager(gameMainManager* pgmm) :
ptrGameMain(pgmm),mapChipHandle(-1)
{
	manager::SetManagerName("mapManager");
}
mapManager::~mapManager() {

}
bool mapManager::Awake() {
	ptrPlayerManager = (playerManager*)ptrGameMain->GetManagerPtr("playerManager");
	if (ptrPlayerManager == nullptr) {
		errorData data = { errorCode::objectNotFound,errorSource::playerManager ,"playerManager���Ȃ�" };
		ptrGameMain->ChangeBlueScreen(&data);
		return false;
	}
	mapChipHandle = LoadGraph(MAPCHIP_HANDLE_PATH.c_str());
	if (mapChipHandle == -1) {
		errorData data = {errorCode::handleRoadFail,errorSource::playerManager,(string*)nullptr };
		ptrGameMain->ChangeBlueScreen(&data);
		return false;
	};
	return true;
}
bool mapManager::Update() {

	return true;
}
void mapManager::Print() {
	const player* p = ptrPlayerManager->GetPlayerPtr();
	coordinate coord = p->GetPos();

	int xGap = coord.x % MAPCHIP_WIDTH;	//�v���C���[��x���W�̍�;
	int yGap = coord.y % MAPCHIP_HEIGHT;//�v���C���[��y���W�̍�;
	for (int i = -1; i <= MAPCHIP_HEIGHT_AMOUNT; i++) {
		for (int j = -1; j <= MAPCHIP_WIDTH_AMOUNT; j++) {
			DrawGraph(j * MAPCHIP_WIDTH + xGap, i * MAPCHIP_HEIGHT + yGap, mapChipHandle,true);
		}
	}
}