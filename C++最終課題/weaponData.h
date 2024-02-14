#pragma once

struct shotPatternData;

enum class weaponImgType {//weaponの外見の種類;
	none,
	red,
	blue
};

struct weaponData {
	int handle;		 //画像ハンドル;
	int handleWidth; //    幅;
	int handleHeight;//    高さ;

	float atk;		//攻撃力;
	coordinate relative;//playerとの相対座標;

	shotPatternData* shotData;

	weaponImgType type;
};