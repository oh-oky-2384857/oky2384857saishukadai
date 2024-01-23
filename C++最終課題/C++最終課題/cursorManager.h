#pragma once
#include "manager.h"

struct coordinate;
struct mouseInputDate;
class gameManager;

class cursorManager:public manager {
	//関数呼び出し用;
	gameManager* ptrGameManager;

	mouseInputDate* inputDates;

	int updateCnt;//カーソルの座標の更新カウンタ;

	int nowCursorHandle;//今使っているカーソル;

	int* cursorHandles;//カーソルの画像;

	int cursorHeight;//カーソルの画像の高さ;
	int cursorWidth;				 //幅;
public:
	cursorManager(gameManager* ptrgm);
	~cursorManager();
	bool Awake();
	bool Update();
	void Print();
};
