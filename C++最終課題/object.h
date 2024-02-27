#pragma once
#include "gameCommon.h"

// 基底クラス
class object {
public:
	
	virtual bool Awake() = 0;	// コンストラクタの後に動かす;
									//ほかのオブジェクトの生成を待つ場合など;
									//エラーコードを返す、エラーがなければnullptrを返す
	virtual void Print() = 0;
	virtual bool Update() = 0;
};