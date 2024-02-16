#include <DxLib.h>
#include <math.h>
#include "enemy.h"
#include "gameCommon.h"
#include "enemyManager.h"
#include "enemyData.h"

#include "player.h"
#include "playerManager.h"

//enemy
enemy::enemy(const enemyData* edata) :data(edata),nowHp(edata->hp), isEnemy(true){}

bool enemy::CheckHit(coordinate coord, int radius) {


	int x = coord.x - position.x;
	int y = coord.y - position.y;
	//これとcoordの距離を計算;
	int dist =  sqrt(x * x + y * y);

	//幅と高さの大きいほうを採用(大抵の敵は幅高さ一緒);
	int r = max(data->width, data->height);

	//これと対象の半径の合計値が距離より大きいなら接触;
	if (dist < (radius + r)) {
		return true;
	}

	return false;
}
bool enemy::Move() {
	//playerの座標取得;
	const player* p = ptrEnemyManager->GetPlayerPtr();
	coordinate pcoord = p->GetPos();

	//これとplayerの距離計算;
	int distx, disty;
	distx = pcoord.x - position.x;
	disty = pcoord.y - position.y;

	float dist = sqrt(distx * distx + disty * disty);

	//ベクトルを正規化、0除算を避けるため1との最大をとる;
	vector2 v2;
	v2.x = (float)distx / max(dist, 1);
	v2.y = (float)disty / max(dist, 1);

	//出したベクトルと移動速度の積を座標に加算;
	floatPos += v2 * data->moveSpeed;
	position = floatPos;
	return true;
}
//ダメージを与える
bool enemy::AddDamage(float damage) {
	//体力を減らす;
	nowHp = nowHp - damage;
	if (nowHp > 0) {
		return false;
	}else {//体力が尽きたら;
		isEnemy = false;
		return true;
	}
}
//enemy

//enemy001;

enemy001::enemy001(coordinate coord, enemyManager* ptrEM,const enemyData* edata)
	:enemy::enemy(edata)/*enemyのコンストラクタ呼び出し*/ {
	;
	//各種データ登録;
	position = coord;
	ptrEnemyManager = ptrEM;
	floatPos = { position.x,position.y };
}
enemy001::~enemy001() {
	//デストラクタ;
	enemy::~enemy();
}

errorData* enemy001::Awake() {
	return nullptr;
}
bool enemy001::Update() {
	enemy::Move();
	const player* p = ptrEnemyManager->GetPlayerPtr();
	coordinate pcoord = p->GetPos();
	int pr = p->GetRadius();
	if (CheckHit(pcoord, pr)) {//当たったら;
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

//enemy001;

//enemy002;
enemy002::enemy002(coordinate coord, enemyManager* ptrEM, const enemyData* edata)
	:enemy::enemy(edata) {
	;
	position = coord;
	ptrEnemyManager = ptrEM;
	floatPos = { position.x,position.y };
}
enemy002::~enemy002() {
	enemy::~enemy();
}
errorData* enemy002::Awake() {
	return nullptr;
}
bool enemy002::Update() {
	enemy::Move();
	const player* p = ptrEnemyManager->GetPlayerPtr();
	coordinate pcoord = p->GetPos();
	int pr = p->GetRadius();
	if (CheckHit(pcoord, pr)) {//当たったら;
		ptrEnemyManager->GetPlayerManagerPtr()->AddDamage(data->atk);
	}
	return true;
}
void enemy002::Print() {
	const player* p = ptrEnemyManager->GetPlayerPtr();
	coordinate pcoord = p->GetPos();
	int xdist = pcoord.x - position.x;
	int ydist = pcoord.y - position.y;

	if (abs(xdist) > SCREEN_WIDTH / 2 || abs(ydist) > SCREEN_HEIGHT / 2) {
		return;
	}
	DrawGraph(xdist + SCREEN_WIDTH / 2, ydist + SCREEN_HEIGHT / 2, data->handle, true);
}
//enemy002;