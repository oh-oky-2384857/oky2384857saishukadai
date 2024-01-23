#pragma once
#include "charactor.h"

//前方宣言
class enemyManager;

//中間クラス;
class enemy : public charactor {
private:
	int enemyHandle;
	int enemyWidth;
	int enemyHeight;
	
	enemyManager* ptrEnemyManager;
public:
	virtual bool Awake() = 0;
	virtual bool Update() = 0;
	virtual void Print() = 0;

	bool CheckHit(coordinate point, int radius);
};

class enemy01 : public enemy {
public:
	enemy01(coordinate coord, enemyManager* ptrEM);
	~enemy01();

	bool Awake();
	bool Update();
	void Print();
};