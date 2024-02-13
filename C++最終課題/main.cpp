#include<DxLib.h>
#include <algorithm>
#include "gameManager.h"
#include "colorSample.h"
#include "stringHandle.h"

#include <crtdbg.h>

// �f�o�b�O�ł̏ꍇ�A���������[�N�ꏊ����肷��}�N��
#ifdef _DEBUG
#define	new	new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif

const int REFRESH_RATE = 17;//���t���b�V�����[�g�A17�~���b;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR IpCmdLine, int nCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	if (DxLib_Init() == -1) {
		return -1;
	}

	ChangeWindowMode(true);
	SetDrawScreen(DX_SCREEN_BACK);

	//gameManager����;
	gameManager* gm = new gameManager;

	//�����ݒ�;
	gm->Awake();

	// ������;
	colorSample::MakeColors();
	stringHandle::MakeHandles();

	int refreshTime;

	while ((ProcessMessage() == 0) && (gm->GetGameStatus() != gameStatus::end)) {
		ClearDrawScreen();

		refreshTime = GetNowCount();

		gm->Update();
		gm->Print();

		ScreenFlip();
		int timeDist = GetNowCount() - refreshTime;//�����̌o�ߎ���
		WaitTimer((std::max)(REFRESH_RATE - timeDist, 0));
	}

	delete gm;

	DxLib_End();
	return 0;
}