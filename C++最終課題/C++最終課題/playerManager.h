#pragma once
#include "manager.h"

// �O���錾
struct coordinate;


class playerManager : public manager {
private:
	int playerHandle;		// �v���C���[�̉摜�n���h��;
	int playerHandleWidth;	// �v���C���[�̉摜�̕�;
	int playerHandleHeight; // �v���C���[�̉摜�̍���;
public:
	playerManager();
	~playerManager();
	bool Awake();
	bool Update();
	void Print();
};