#pragma once

struct shotPatternData;

enum class weaponImgType {//weapon�̊O���̎��;
	none,
	red,
	blue
};

struct weaponData {
	int handle;		 //�摜�n���h��;
	int handleWidth; //    ��;
	int handleHeight;//    ����;

	float atk;		//�U����;
	coordinate relative;//player�Ƃ̑��΍��W;

	shotPatternData* shotData;

	weaponImgType type;
};