#include <DxLib.h>
#include <algorithm>
#include "gameManager.h"
#include "colorSample.h"
#include "stringHandle.h"

#include "errorCode.h"
#include "blueScreen.h"
#include "errorManager.h"

#include <crtdbg.h>

//�f�o�b�O�ł̏ꍇ�A���������[�N�ꏊ����肷��}�N��;
#ifdef _DEBUG
#define	new	new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif

using namespace std;

const int REFRESH_RATE = 17;

const string ERROR_LOG_FILE_PATH = "./resource/errorResource/errorLog.txt";//�G���[���O�̃p�X;

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

	//�G���[���b�Z�[�W�o�͗p;
	errorManager* em = new errorManager;
	
	//�����ݒ莸�s�ŋ����I��;
	if(!em->Awake()) {

		delete gm, em;
		DxLib_End();
		return -1;

	}

	//�G���[���O�ǐ�����̂��ߏ����u���b�N�I����,�J�n���Ƀ��O���o��;
	em->AddErrorLog("errorManagerAwakeSuccess");
	em->AddErrorLog("gameManagerAwake");

	//�N��������;
	try {
		gm->Awake();

	//���O�̃G���[������;
	}catch (errorData* d) {

		//�G���[���O�ɏ���;
		em->AddErrorLog(d);
		
		//��������폜;
		delete gm;
		
		//title�}�l�[�W���������Ȃ�u���[�X�N���[���ɒ���;
		if (d->source == errorSource::titleManager) {

			sceneManager* newScene = new blueScreenManager(gm, d);

			//�V�[���w��R���X�g���N�^�𗘗p���Ē��ڃu���X�N��;
			gm = new gameManager(newScene);

			//������x����;
			try {
				gm->Awake();

			//�_����������
			}catch (errorData* d) {

				//���b�Z�[�W���o�͂��ďI��;
				em->AddErrorLog("���A���s");

				delete gm, em;
				DxLib_End();
				return -1;
			}

			//���b�Z�[�W���o�͂��đ��s;
			em->AddErrorLog("���A����");


		}else {
			//title�}�l�[�W���������łȂ��Ȃ�I��;
			delete gm, em;
			DxLib_End();
			return -1;
		}

		return -1;

	//����̃G���[�ȊO��������;
	}catch (exception e) {

		//�G���[���O�ɏ���;
		em->AddErrorLog(e.what());

		delete gm, em;
		DxLib_End();

		return -1;

	//���̑��G���[;
	}catch (...) {
		//�G���[���O�ɏ���;
		em->AddErrorLog("�s���ȃG���[");

		delete gm, em;
		DxLib_End();

		return -1;
	}

	//�G���[���O�o��;
	em->AddErrorLog("gameManagerAwakeSuccess");

	// ������,�F������蕶���������;
	colorSample::MakeColors();
	stringHandle::MakeHandles();

	int refreshTime;

	//�G���[���O�o��;
	em->AddErrorLog("gameRoop");

	//�Q�[�����[�v;
	try {

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
	//���O�̃G���[������;
	}catch (errorData* d) {

		//�G���[���O�ɏ���;
		em->AddErrorLog(d);

		//�u���X�N�ɃV�[���Έ�;
		sceneManager* newScene = new blueScreenManager(gm, d);

		gm->SetNewScene(newScene);
		//�u���X�N���o�����߂̃��[�v;
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


	//����̃G���[�ȊO��������;
	}catch (exception e) {

		//�G���[���O�ɏ���;
		em->AddErrorLog(e.what());

		delete gm, em;
		DxLib_End();

		return -1;

	//���̑��G���[;
	}catch (...) {

		//�G���[���O�ɏ���;
		em->AddErrorLog("�s���ȃG���[");

		delete gm, em;
		DxLib_End();

		return -1;

	}


	//��n��;
	delete gm, em;

	DxLib_End();

	return 0;
}