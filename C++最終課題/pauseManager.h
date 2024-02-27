#pragma once
#include "manager.h"

//�O���錾;
class gameManager;
struct mouseInputData;
struct pauseInputData;

//�|�[�Y�ł���̂�main����;
class pauseManager :public manager{
private:
	int pauseCnt;		//�|�[�Y�̃N�[���^�C���̃J�E���^;
	int pauseHandle;	//�|�[�Y���j���[�̉摜�n���h��;
	
	//�֐��Ăяo���p;
	gameManager* ptrGameManager;

	//���͎󂯎��;
	mouseInputData* mouseInput;//�}�E�X����
	pauseInputData* pauseInput;//�|�[�Y����(�G�X�P�[�v�L�[,�X�^�[�g�{�^��);
public:
	pauseManager(gameManager* ptrGM);
	~pauseManager();
	bool Awake() override;
	bool Update()override;
	void Print() override;

	void SetPause();//�|�[�Y�ɂ���;
	void EscapePause();//�|�[�Y����߂�;
};