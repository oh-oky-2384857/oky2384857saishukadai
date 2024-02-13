#pragma once
#include "manager.h"

struct coordinate;
struct mouseInputData;
class gameManager;

class cursorManager:public manager {
private:
	//関数呼び出し用;
	gameManager* ptrGameManager;

	mouseInputData* inputDatas;

	int updateCnt;//カーソルの座標の更新カウンタ;

	int nowCursorHandle;//今使っているカーソル;

	int* cursorHandles;//カーソルの画像;

	int cursorHeight;//カーソルの画像の高さ;
	int cursorWidth;				 //幅;
public:
	cursorManager(gameManager* ptrgm);
	~cursorManager();
	bool Awake() override;
	bool Update()override;
	void Print() override;
};
