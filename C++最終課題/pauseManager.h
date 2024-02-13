#pragma once
#include "manager.h"

//前方宣言;
class gameManager;
struct mouseInputData;
struct pauseInputData;

//ポーズできるのはmainだけ;
class pauseManager :public manager{
private:
	int pauseCnt;		//ポーズのクールタイムのカウンタ;
	int pauseHandle;	//ポーズメニューの画像ハンドル;
	//関数呼び出し用;
	gameManager* ptrGameManager;
	//入力受け取り;
	mouseInputData* mouseInput;
	pauseInputData* pauseInput;
public:
	pauseManager(gameManager* ptrGM);
	~pauseManager();
	bool Awake() override;
	bool Update()override;
	void Print() override;

	void SetPause();
	void EscapePause();
};