#pragma once
#include "entity.h"

//前方宣言;
class enemyManager;
struct enemyData;


//中間クラス;
class enemy : public entity {
protected:
	bool isEnemy;//生きているか;

	//関数呼び出し用;
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