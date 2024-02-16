#include<DxLib.h>
#include <algorithm>
#include "gameManager.h"
#include "colorSample.h"
#include "stringHandle.h"

#include <crtdbg.h>

//デバッグ版の場合、メモリリーク場所を特定するマクロ;
#ifdef _DEBUG
#define	new	new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif

const int REFRESH_RATE = 17;//リフレッシュレート、17ミリ秒;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR IpCmdLine, int nCmdShow)
{
	//メモリリークを管理する関数;
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// ＤＸライブラリ初期化処理
	if (DxLib_Init() == -1)
	{
		return -1;        // エラーが起きたら直ちに終了
	}

	//windowModeに変更;
	ChangeWindowMode(true);
	//描画先画面を裏にする;
	SetDrawScreen(DX_SCREEN_BACK);

	//gameManager生成;
	gameManager* gm = new gameManager;

	//初期設定;
	gm->Awake();

	// 下準備,色作ったり文字作ったり;
	colorSample::MakeColors();
	stringHandle::MakeHandles();

	int refreshTime;

	//エラー発生または状態が終了になったら;
	while ((ProcessMessage() == 0) && (gm->GetGameStatus() != gameStatus::end)) {
		//画面リセット
		ClearDrawScreen();

		//リフレッシュタイムに現在時間を代入;
		refreshTime = GetNowCount();

		gm->Update();//更新処理;
		gm->Print();//表示処理;

		//裏画面の内容を表画面に反映;
		ScreenFlip();
		int timeDist = GetNowCount() - refreshTime;//処理の経過時間;
		//リフレッシュレートから経過時間を引いて処理間隔を一定に;
		WaitTimer((std::max)(REFRESH_RATE - timeDist, 0));
	}

	//後始末;
	delete gm;

	DxLib_End();
	return 0;
}