#include <string>
#include <DxLib.h>

#include "mapManager.h"
#include "gameMainManager.h"
#include "blueScreen.h"
#include "errorCode.h"
#include "gameCommon.h"
#include "playerManager.h"

using namespace std;

const string MAPCHIP_HANDLE_PATH =
{"./resource/gameMainResource/mapResource/backGround01.png"};

const int MAPCHIP_WIDTH_AMOUNT = 4;	//マップチップが横に最大何枚並ぶか;
const int MAPCHIP_HEIGHT_AMOUNT = 3;//マップチップが縦に最大何枚並ぶか;

const int MAPCHIP_WIDTH = 256;//マップチップの画像の幅;
const int MAPCHIP_HEIGHT = 256;//マップチップの画像の高さ;


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
		errorData data = { errorCode::objectNotFound,errorSource::playerManager };
		ptrGameMain->ChangeBlueScreen(&data);
		return false;
	}
	mapChipHandle = LoadGraph(MAPCHIP_HANDLE_PATH.c_str());
	if (mapChipHandle == -1) {
		errorData data = {errorCode::handleRoadFail,errorSource::playerManager};
		ptrGameMain->ChangeBlueScreen(&data);
		return false;
	};
	return true;
}
bool mapManager::Update() {

	return true;
}
void mapManager::Print() {
	coordinate coord = ptrPlayerManager->GetPosition();

	int xGap = coord.x % MAPCHIP_WIDTH;	//プレイヤーのx座標の差;
	int yGap = coord.y % MAPCHIP_HEIGHT;//プレイヤーのy座標の差;
	for (int i = -1; i <= MAPCHIP_HEIGHT_AMOUNT; i++) {
		for (int j = -1; j <= MAPCHIP_WIDTH_AMOUNT; j++) {
			DrawGraph(j * MAPCHIP_WIDTH + xGap, i * MAPCHIP_HEIGHT + yGap, mapChipHandle,true);
		}
	}
}