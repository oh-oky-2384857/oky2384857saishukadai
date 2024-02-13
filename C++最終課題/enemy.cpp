#include <DxLib.h>
#include <math.h>
#include "enemy.h"
#include "gameCommon.h"
#include "enemyManager.h"
#include "enemyData.h"

#include "player.h"
#include "playerManager.h"

enemy::enemy(const enemyData* edata) :data(edata),nowHp(edata->hp), isEnemy(true){}

bool enemy::CheckHit(coordinate coord, int radius) {


	int x = abs(coord.x - position.x);
	int y = abs(coord.y - position.y);
	//�����coord�̋������v�Z;
	int dist =  x * x + y * y;

	//���ƍ����̑傫���ق����̗p(���̓G�͕������ꏏ);
	int r = max(data->width, data->height);

	if (dist < (radius * radius + r * r)) {
		return true;
	}
	return false;
}
bool enemy::AddDamage(float damage) {
	nowHp = nowHp - damage;
	if (nowHp > 0) {
		return false;
	}else {
		return true;
	}
}

//enemy001;

enemy001::enemy001(coordinate coord, enemyManager* ptrEM,const enemyData* edata)
	:enemy::enemy(edata) {
	;
	position = coord;
	ptrEnemyManager = ptrEM;
	floatPos = { position.x,position.y };
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
	if (CheckHit(pcoord, pr)) {//����������;
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
	const player* p = ptrEnemyManager->GetPlayerPtr();
	coordinate pcoord = p->GetPos();
	
	int distx, disty;
	distx = pcoord.x - position.x;
	disty = pcoord.y - position.y;

	float dist = sqrt(distx * distx + disty * disty);

	vector2 v2;
	v2.x = (float)distx / max(dist, 1);
	v2.y = (float)disty / max(dist, 1);

	floatPos += v2 * data->moveSpeed;
	position = floatPos;

	return true;
}

//enemy001;
