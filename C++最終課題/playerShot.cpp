#include <DxLib.h>
#include "playerShot.h"
#include "playerShotManager.h"
#include "player.h"
#include "gameCommon.h"

playerShotBase::playerShotBase(shotData* d, playerShotManager* ptrPS)
	: data(d),ptrPlayerShot(ptrPS){}
playerShotBase::~playerShotBase() {
	delete data;
}
void playerShotBase::Print() {
	coordinate pcoord = ptrPlayerShot->GetPlayer()->GetPos();
	int distX = pcoord.x - data->position.x;
	int distY = pcoord.y - data->position.y;

	if (abs(distX) > SCREEN_WIDTH / 2 || abs(distY) > SCREEN_HEIGHT / 2) {
		return;
	}

	DrawGraph(distX + SCREEN_WIDTH / 2, distY + SCREEN_HEIGHT / 2,data->pData->handle, true);
}
bool playerShotBase::Update() {
	if (ptrPlayerShot->CheckEnemyHit(data, 2)) {
		return true;
	}
	return false;
}
void  playerShotBase::Move() {
	data->positionFloat += data->vec2 * data->pData->moveSpeed;
	data->position = data->positionFloat;
}

//normal;

psNormal::psNormal(shotData* d, playerShotManager* ptrPS)
	:playerShotBase::playerShotBase(d,ptrPS) {}
psNormal::~psNormal() {
	playerShotBase::~playerShotBase();
}
bool psNormal::Update() {
	playerShotBase::Move();
	if (playerShotBase::Update()) {
		return true;
	}else {
		return false;
	}
}

//normal;