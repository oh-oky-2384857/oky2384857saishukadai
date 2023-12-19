#include<DxLib.h>
#include "gameManager.h"
#include "colorSample.h"
#include "stringHandle.h"

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

	while ((ProcessMessage() == 0) && (CheckHitKey(KEY_INPUT_ESCAPE) == 0)) {
		ClearDrawScreen();

		gm->Update();
		gm->Print();

		ScreenFlip();
		WaitTimer(10);
	}

	delete gm;

	WaitKey();
	DxLib_End();
	return 0;
}