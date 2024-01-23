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

//移動入力;
struct moveInputDate {
	//スティック入力の場合は10~-10の間で変動;
	//キーボード、ボタン入力の場合は最大値固定;
	//複数手段の同時入力の場合、すべての入力値を足して大きいほう;
	int xPower;//x入力値,プラス値右入力マイナス値左入力;
	int yPower;//y入力値,プラス値下入力マイナス値上入力;
};

struct inputDate {

	mouseInputDate* mouse;
	moveInputDate* move;

	inputDate() = default;
};