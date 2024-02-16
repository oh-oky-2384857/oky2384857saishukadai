#pragma once
#include "entity.h"

//前方宣言;
class enemyManager;
struct enemyData;


//中間クラス;
class enemy : public entity {
protected:
	bool isEnemy;	//生きているか;
	float nowHp;	//現在Hp;

	vector2 floatPos;
	//関数呼び出し用;
	enemyManager* ptrEnemyManager;

	const enemyData* data;
	
	//コンストラクタ;
	enemy(const enemyData* edata);
public:
	virtual errorData* Awake() { return nullptr; };
	virtual bool Update() { return true; };
	virtual void Print() {};

	virtual bool Move();

	/**
	*@returns bool true:接触,false:非接触;
	*/
	bool CheckHit(coordinate coord, int radius);

	inline bool GetIsEnemy() { return isEnemy; };

	/**
	*@returns bool true:死,false:生;
	*/
	virtual bool AddDamage(float damage);
};


class enemy001 : public enemy {
private:
public:
	enemy001(coordinate coord, enemyManager* ptrEM,const enemyData* edata);
	~enemy001();

	errorData* Awake();
	bool Update();
	void Print();
};

class enemy002 : public enemy {
private:
public:
	enemy002(coordinate coord, enemyManager* ptrEM, const enemyData* edata);
	~enemy002();

	errorData* Awake();
	bool Update();
	void Print();
};