#include <DxLib.h>
#include <math.h>
#include "enemy.h"
#include "gameCommon.h"
#include "enemyManager.h"
#include "enemyData.h"

#include "player.h"
#include "playerManager.h"

bool enemy::CheckHit(coordinate coord, int radius) {

	//‚±‚ê‚Æcoord‚Ì‹——£‚ðŒvŽZ;
	int dist = abs(coord.x - position.x) ^ 2 + abs(coord.y - position.y) ^ 2;

	//•‚Æ‚‚³‚Ì‘å‚«‚¢‚Ù‚¤‚ðÌ—p(‘å’ï‚Ì“G‚Í•‚‚³ˆê);
	int r = max(data->width, data->height);

	if (dist < (radius ^ 2 + r ^ 2)) {
		return true;
	}
	return false;
}

//enemy001;

enemy001::enemy001(coordinate coord, enemyManager* ptrEM,const enemyData* edata)
	:enemy::enemy(edata) {
	;
	position = coord;
	ptrEnemyManager = ptrEM;
}
enemy001::~enemy001() {

}

bool enemy001::Awake() {
	return false;
}
bool enemy001::Update() {
	Move();
	const player* p = ptrEnemyManager->GetPlayerPtr();
	coordinate pcoord = p->GetPos();
	int pr = p->GetRadius();
	if (CheckHit(pcoord, pr)) {//“–‚½‚Á‚½‚ç;
		ptrEnemyManager->GetPlayerManagerPtr()->AddDamage(data->atk);
	}
	return true;
}
void enemy001::Print() {
	const player* p = ptrEnemyManager->GetPlayerPtr();
	coordinate pcoord = p->GetPos();
	int xdist = pcoord.x - position.x;
	int ydist = pcoord.y - position.y;

	if (abs(xdist) > SCREEN_WIDTH / 2 || abs(ydist) > SCREEN_HEIGHT / 2) {
		return;
	}
	DrawGraph(xdist + SCREEN_WIDTH / 2, ydist + SCREEN_HEIGHT / 2, data->handle, true);
}

bool enemy001::Move() {
	return true;
}

//enemy001;
