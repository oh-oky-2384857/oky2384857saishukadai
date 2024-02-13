#pragma once
#include "entity.h"

//�O���錾;
class enemyManager;
struct enemyData;


//���ԃN���X;
class enemy : public entity {
protected:
	bool isEnemy;//�����Ă��邩;

	//�֐��Ăяo���p;
	enemyManager* ptrEnemyManager;

	const enemyData* data;
	
	enemy(const enemyData* edata) :data(edata) ,isEnemy(true){};
public:
	virtual bool Awake() { return true; };
	virtual bool Update() { return true; };
	virtual void Print() {};

	virtual bool Move() { return true; };

	bool CheckHit(coordinate coord, int radius);

	inline bool GetIsEnemy() { return isEnemy; };
};


class enemy001 : public enemy {
private:
public:
	enemy001(coordinate coord, enemyManager* ptrEM,const enemyData* edata);
	~enemy001();

	bool Awake();
	bool Update();
	void Print();

	bool Move()override;
};