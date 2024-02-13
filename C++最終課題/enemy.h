#pragma once
#include "entity.h"

//�O���錾;
class enemyManager;
struct enemyData;


//���ԃN���X;
class enemy : public entity {
protected:
	bool isEnemy;	//�����Ă��邩;
	float nowHp;	//����Hp;

	vector2 floatPos;
	//�֐��Ăяo���p;
	enemyManager* ptrEnemyManager;

	const enemyData* data;
	
	//�R���X�g���N�^;
	enemy(const enemyData* edata);
public:
	virtual bool Awake() { return true; };
	virtual bool Update() { return true; };
	virtual void Print() {};

	virtual bool Move() { return true; };

	/**
	*@returns bool true:�ڐG,false:��ڐG;
	*/
	bool CheckHit(coordinate coord, int radius);

	inline bool GetIsEnemy() { return isEnemy; };

	/**
	*@returns bool true:��,false:��;
	*/
	virtual bool AddDamage(float damage);
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