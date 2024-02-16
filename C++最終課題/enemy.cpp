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
	//�����coord�̋������v�Z;
	int dist =  sqrt(x * x + y * y);

	//���ƍ����̑傫���ق����̗p(���̓G�͕������ꏏ);
	int r = max(data->width, data->height);

	//����ƑΏۂ̔��a�̍��v�l���������傫���Ȃ�ڐG;
	if (dist < (radius + r)) {
		return true;
	}

	return false;
}
bool enemy::Move() {
	//player�̍��W�擾;
	const player* p = ptrEnemyManager->GetPlayerPtr();
	coordinate pcoord = p->GetPos();

	//�����player�̋����v�Z;
	int distx, disty;
	distx = pcoord.x - position.x;
	disty = pcoord.y - position.y;

	float dist = sqrt(distx * distx + disty * disty);

	//�x�N�g���𐳋K���A0���Z������邽��1�Ƃ̍ő���Ƃ�;
	vector2 v2;
	v2.x = (float)distx / max(dist, 1);
	v2.y = (float)disty / max(dist, 1);

	//�o�����x�N�g���ƈړ����x�̐ς����W�ɉ��Z;
	floatPos += v2 * data->moveSpeed;
	position = floatPos;
	return true;
}
//�_���[�W��^����
bool enemy::AddDamage(float damage) {
	//�̗͂����炷;
	nowHp = nowHp - damage;
	if (nowHp > 0) {
		return false;
	}else {//�̗͂��s������;
		isEnemy = false;
		return true;
	}
}
//enemy

//enemy001;

enemy001::enemy001(coordinate coord, enemyManager* ptrEM,const enemyData* edata)
	:enemy::enemy(edata)/*enemy�̃R���X�g���N�^�Ăяo��*/ {
	;
	//�e��f�[�^�o�^;
	position = coord;
	ptrEnemyManager = ptrEM;
	floatPos = { position.x,position.y };
}
enemy001::~enemy001() {
	//�f�X�g���N�^;
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
	if (CheckHit(pcoord, pr)) {//����������;
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