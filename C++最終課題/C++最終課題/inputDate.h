#pragma once

// マウスの入力
struct mouseInputDate {
	bool isRightClick;	//右クリック;
	bool isLeftClick;	//左クリック;
	int x;				//x座標;
	int y;				//y座標;
	int pressingTime;	//押し続けている時間;
	int pressStartx;	//押し始めたx座標;
	int pressStarty;	//			y座標;
};

struct inputDate {

	mouseInputDate* mouse;


	inputDate() = default;
};