#include<DxLib.h>
#include <algorithm>
#include "gameManager.h"
#include "colorSample.h"
#include "stringHandle.h"

const int REFRESH_RATE = 17;//リフレッシュレート、17ミリ秒;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR IpCmdLine, int nCmdShow)
{
	if (DxLib_Init() == -1) {
		return -1;
	}

	ChangeWindowMode(true);
	SetDrawScreen(DX_SCREEN_BACK);

	//gameManager生成;
	gameManager* gm = new gameManager;

	//初期設定;
	gm->Awake();

	// 下準備;
	colorSample::MakeColors();
	stringHandle::MakeHandles();

	int refreshTime;

	while ((ProcessMessage() == 0) && (gm->GetGameStatus() != gameStatus::end)) {
		ClearDrawScreen();

		refreshTime = GetNowCount();

		gm->Update();
		gm->Print();

		ScreenFlip();
		int timeDist = GetNowCount() - refreshTime;//処理の経過時間
		WaitTimer((std::max)(REFRESH_RATE - timeDist, 0));
	}

	delete gm;

	DxLib_End();
	return 0;
}