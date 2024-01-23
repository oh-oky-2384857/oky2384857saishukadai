#pragma once

// �}�E�X�̓���
struct mouseInputDate {
	bool isRightClick;	//�E�N���b�N;
	bool isLeftClick;	//���N���b�N;
	int x;				//x���W;
	int y;				//y���W;
	int pressingTime;	//���������Ă��鎞��;
	int pressStartx;	//�����n�߂�x���W;
	int pressStarty;	//			y���W;
};

//�ړ�����;
struct moveInputDate {
	//�X�e�B�b�N���͂̏ꍇ��10~-10�̊Ԃŕϓ�;
	//�L�[�{�[�h�A�{�^�����͂̏ꍇ�͍ő�l�Œ�;
	//������i�̓������͂̏ꍇ�A���ׂĂ̓��͒l�𑫂��đ傫���ق�;
	int xPower;//x���͒l,�v���X�l�E���̓}�C�i�X�l������;
	int yPower;//y���͒l,�v���X�l�����̓}�C�i�X�l�����;
};

struct inputDate {

	mouseInputDate* mouse;
	moveInputDate* move;

	inputDate() = default;
};