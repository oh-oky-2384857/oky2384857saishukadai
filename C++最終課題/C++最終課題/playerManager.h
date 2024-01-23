#pragma once
#include "manager.h"

// 前方宣言
struct coordinate;


class playerManager : public manager {
private:
	int playerHandle;		// プレイヤーの画像ハンドル;
	int playerHandleWidth;	// プレイヤーの画像の幅;
	int playerHandleHeight; // プレイヤーの画像の高さ;
public:
	playerManager();
	~playerManager();
	bool Awake();
	bool Update();
	void Print();
};