#pragma once
#include "manager.h"

struct coordinate;

class cursorManager:public manager {
	int updateCnt;//�J�[�\���̍��W�̍X�V�J�E���^;

	int nowCursorHandle;//���g���Ă���J�[�\��;

	int* cursorHandles;//�J�[�\���̉摜;
	coordinate cursorCoord;//�J�[�\���̍��W;

	int cursorHeight;//�J�[�\���̉摜�̍���;
	int cursorWidth;				 //��;
public:
	cursorManager();
	~cursorManager();
	void Awake() {};
	void Update();
	void Print();
};
