#pragma once
#include "gameCommon.h"

// 基底クラス
class object {
public:
	
	virtual void Awake() = 0;// コンストラクタの後に動かす;
							 //ほかのオブジェクトの生成を待つ場合など;
	virtual void Print() = 0;
	virtual void Update() = 0;
};