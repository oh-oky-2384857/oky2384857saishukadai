#pragma once
#include "gameCommon.h"
#include "errorCode.h"

// ���N���X
class object {
public:
	
	virtual errorData* Awake() = 0;	// �R���X�g���N�^�̌�ɓ�����;
									//�ق��̃I�u�W�F�N�g�̐�����҂ꍇ�Ȃ�;
									//�G���[�R�[�h��Ԃ��A�G���[���Ȃ����nullptr��Ԃ�
	virtual void Print() = 0;
	virtual bool Update() = 0;
};