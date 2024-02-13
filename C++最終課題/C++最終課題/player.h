#pragma once
#include "entity.h"


class player :public entity {
private:
	int playerHandle;			// プレイヤーの画像ハンドル;
	int playerHandleWidth;		// プレイヤーの画像の幅;
	int playerHandleHeight;		// プレイヤーの画像の高さ;


	int playerMoveSpeed;		//プレイヤーの移動速度;

	float coordFractionX;		//プレイヤーのx座標の端数;
	float coordFractionY;		//プレイヤーのy座標の端数;

	float playerHpMax;			//プレイヤーの最大Hp;
	float playerHpNow;			//プレイヤーの現在Hp;

	int invincibilityTimeCnt;	//無敵時間のカウント;
	int invincibilityTime;		//無敵時間;

	void PrintHpBar();			//hpバー描画関数;
public:
	player();
	player(coordinate coord);
	~player();

	bool Awake();
	bool Update();
	void Print();

	bool LoadPlayerHandle();
	bool LoadStatus();
	void AddMovePower(int moveX, int moveY);

	bool AddDamage(int damage);
};