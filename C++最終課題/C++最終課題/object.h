#pragma once
#include "gameCommon.h"

// ���N���X
class object {
public:
	
	virtual void Awake() = 0;// �R���X�g���N�^�̌�ɓ�����;
							 //�ق��̃I�u�W�F�N�g�̐�����҂ꍇ�Ȃ�;
	virtual void Print() = 0;
	virtual void Update() = 0;
};