#pragma once
#include "manager.h"

struct coordinate;

class cursorManager:public manager {
	int updateCnt;//カーソルの座標の更新カウンタ;

	int nowCursorHandle;//今使っているカーソル;

	int* cursorHandles;//カーソルの画像;
	coordinate cursorCoord;//カーソルの座標;

	int cursorHeight;//カーソルの画像の高さ;
	int cursorWidth;				 //幅;
public:
	cursorManager();
	~cursorManager();
	void Awake() {};
	void Update();
	void Print();
};
