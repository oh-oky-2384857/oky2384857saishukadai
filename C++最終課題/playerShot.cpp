#include "playerShot.h"
#include "playerShotManager.h"
#include "player.h"
#include "gameCommon.h"
#include <DxLib.h>

playerShot::playerShot(shotData* d, playerShotManager* ptrPS)
	: data(d),ptrPlayerShot(ptrPS){}
playerShot::~playerShot() {
	delete data;
}
void playerShot::Print() {
	coordinate pcoord = ptrPlayerShot->GetPlayer()->GetPos();
	int distX = pcoord.x - data->position.x;
	int distY = pcoord.y - data->position.y;

	if (abs(distX) > SCREEN_WIDTH / 2 || abs(distY) > SCREEN_HEIGHT / 2) {
		return;
	}

	DrawGraph(distX + SCREEN_WIDTH / 2, distY + SCREEN_HEIGHT / 2,data->pData->handle, true);
}
bool playerShot::Update() {
	if (ptrPlayerShot->CheckEnemyHit(data, 2)) {
		return true;
	}
	return false;
}
void  playerShot::Move() {
	data->positionFloat += data->vec2 * data->pData->moveSpeed;
	data->position = data->positionFloat;
}

//normal;

psNormal::psNormal(shotData* d, playerShotManager* ptrPS)
	:playerShot::playerShot(d,ptrPS) {}
psNormal::~psNormal() {
	playerShot::~playerShot();
}
bool psNormal::Update() {
	playerShot::Move();
	if (playerShot::Update()) {
		return true;
	}else {
		return false;
	}
}

//normal;