#pragma once
#include "charactor.h"

struct coordinate;

class player :public charactor {
private:
	int playerHandle;		// �v���C���[�̉摜�n���h��;
	int playerHandleWidth;	// �v���C���[�̉摜�̕�;
	int playerHandleHeight; // �v���C���[�̉摜�̍���;


	int playerMoveSpeed;	//�v���C���[�̈ړ����x;

	coordinate position;		//�v���C���[�̈ʒu;
	float coordFractionX;	//�v���C���[��x���W�̒[��
	float coordFractionY;	//�v���C���[��y���W�̒[��
public:
	player();
	player(coordinate coord);
	~player();

	bool Awake();
	bool Update();
	void Print();

	bool LoadPlayerHandle();
	bool LoadStatus();
	void AddMovePower(int moveX, int moveY);

}