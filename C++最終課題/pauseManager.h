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
	mouseInputData* mouseInput;//マウス入力
	pauseInputData* pauseInput;//ポーズ入力(エスケープキー,スタートボタン);
public:
	pauseManager(gameManager* ptrGM);
	~pauseManager();
	bool Awake() override;
	bool Update()override;
	void Print() override;

	void SetPause();//ポーズにする;
	void EscapePause();//ポーズから戻す;
};