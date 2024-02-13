#pragma once
#include "entity.h"


class player :public entity {
private:
	int playerHandle;			// �v���C���[�̉摜�n���h��;
	int playerHandleWidth;		// �v���C���[�̉摜�̕�;
	int playerHandleHeight;		// �v���C���[�̉摜�̍���;


	int playerMoveSpeed;		//�v���C���[�̈ړ����x;

	float coordFractionX;		//�v���C���[��x���W�̒[��;
	float coordFractionY;		//�v���C���[��y���W�̒[��;

	float playerHpMax;			//�v���C���[�̍ő�Hp;
	float playerHpNow;			//�v���C���[�̌���Hp;

	int invincibilityTimeCnt;	//���G���Ԃ̃J�E���g;
	int invincibilityTime;		//���G����;

	void PrintHpBar();			//hp�o�[�`��֐�;
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

	bool AddDamage(int damage);
};