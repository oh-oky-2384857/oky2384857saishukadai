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

struct inputDate {

	mouseInputDate mouse;

};