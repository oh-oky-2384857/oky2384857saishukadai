#pragma once
#include "charactor.h"

struct coordinate;

class player :public charactor {
private:
	int playerHandle;		// プレイヤーの画像ハンドル;
	int playerHandleWidth;	// プレイヤーの画像の幅;
	int playerHandleHeight; // プレイヤーの画像の高さ;


	int playerMoveSpeed;	//プレイヤーの移動速度;

	coordinate position;		//プレイヤーの位置;
	float coordFractionX;	//プレイヤーのx座標の端数
	float coordFractionY;	//プレイヤーのy座標の端数
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

}