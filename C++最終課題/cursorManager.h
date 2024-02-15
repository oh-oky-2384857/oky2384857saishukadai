#pragma once
#include "manager.h"

struct coordinate;
struct mouseInputData;
class gameManager;

class cursorManager:public manager {
private:
	//�֐��Ăяo���p;
	gameManager* ptrGameManager;

	mouseInputData* inputDatas;

	int updateCnt;//�J�[�\���̍��W�̍X�V�J�E���^;

	int nowCursorHandle;//���g���Ă���J�[�\��;

	int* cursorHandles;//�J�[�\���̉摜;

	int cursorHeight;//�J�[�\���̉摜�̍���;
	int cursorWidth;				 //��;
public:
	cursorManager(gameManager* ptrgm);
	~cursorManager();
	errorData* Awake() override;
	bool Update()override;
	void Print() override;
};
