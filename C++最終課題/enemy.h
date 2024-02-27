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

	//基本データ;
	const enemyData* data;
	
	//コンストラクタ;
	enemy(const enemyData* edata);
	//デフォルトの移動、プレイヤーに近づく;
	virtual bool Move();
public:
	virtual bool Awake() { return true; };
	virtual bool Update() { return true; };
	virtual void Print() {};

	/**
	当たっているか
	*@returns bool true:接触,false:非接触;
	*/
	bool CheckHit(coordinate coord, int radius);

	/**
	生きているか 
	*@returns bool true:生,false:死;
	*/
	inline bool GetIsEnemy() { return isEnemy; };

	/**
	ダメージを与える
	*@returns bool true:死,false:生;
	*/
	virtual bool AddDamage(float damage);
};


class enemy001 : public enemy {
private:
public:
	/**
	コンストラクタ
	*@param	<coordinate>	coord	座標;
	*@param <enemyManager*>	ptrEM	関数呼び出し用;
	*@param <const enemyData*>	edata	基本データ;
	*/
	enemy001(coordinate coord, enemyManager* ptrEM,const enemyData* edata);
	~enemy001();

	bool Awake();
	bool Update();
	void Print();
};

class enemy002 : public enemy {
private:
public:
	enemy002(coordinate coord, enemyManager* ptrEM, const enemyData* edata);
	~enemy002();

	bool Awake();
	bool Update();
	void Print();
};