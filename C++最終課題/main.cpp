#include<DxLib.h>
#include <algorithm>
#include "gameManager.h"
#include "colorSample.h"
#include "stringHandle.h"

#include <crtdbg.h>

//�f�o�b�O�ł̏ꍇ�A���������[�N�ꏊ����肷��}�N��;
#ifdef _DEBUG
#define	new	new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif

const int REFRESH_RATE = 17;//���t���b�V�����[�g�A17�~���b;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR IpCmdLine, int nCmdShow)
{
	//���������[�N���Ǘ�����֐�;
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// �c�w���C�u��������������
	if (DxLib_Init() == -1)
	{
		return -1;        // �G���[���N�����璼���ɏI��
	}

	//windowMode�ɕύX;
	ChangeWindowMode(true);
	//�`����ʂ𗠂ɂ���;
	SetDrawScreen(DX_SCREEN_BACK);

	//gameManager����;
	gameManager* gm = new gameManager;

	//�����ݒ�;
	gm->Awake();

	// ������,�F������蕶���������;
	colorSample::MakeColors();
	stringHandle::MakeHandles();

	int refreshTime;

	//�G���[�����܂��͏�Ԃ��I���ɂȂ�����;
	while ((ProcessMessage() == 0) && (gm->GetGameStatus() != gameStatus::end)) {
		//��ʃ��Z�b�g
		ClearDrawScreen();

		//���t���b�V���^�C���Ɍ��ݎ��Ԃ���;
		refreshTime = GetNowCount();

		gm->Update();//�X�V����;
		gm->Print();//�\������;

		//����ʂ̓��e��\��ʂɔ��f;
		ScreenFlip();
		int timeDist = GetNowCount() - refreshTime;//�����̌o�ߎ���;
		//���t���b�V�����[�g����o�ߎ��Ԃ������ď����Ԋu������;
		WaitTimer((std::max)(REFRESH_RATE - timeDist, 0));
	}

	//��n��;
	delete gm;

	DxLib_End();
	return 0;
}