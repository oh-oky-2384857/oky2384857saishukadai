#pragma once
#include "entity.h"


class player :public entity {
private:
	int playerHandle;			// �v���C���[�̉摜�n���h��;
	int playerHandleWidth;		// �v���C���[�̉摜�̕�;
	int playerHandleHeight;		// �v���C���[�̉摜�̍���;

	float playerAtk;			//�v���C���[�̍U����;

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

	inline int GetRadius() const {
		//�c���Ɖ����̑傫���ق���Ԃ�;
		return (playerHandleWidth > playerHandleHeight) ? playerHandleWidth : playerHandleHeight;
	}
	inline float GetAtk()const { return playerAtk; };

	void AddMovePower(int moveX, int moveY);
	bool AddDamage(int damage);
};