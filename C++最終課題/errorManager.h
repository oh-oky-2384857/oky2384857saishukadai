#pragma once
#include <fstream>
#include "manager.h"
#include "errorCode.h"

class errorManager :public manager {
private:
	//出力先;
	std::ofstream errorLogFile;
public:
	// { コンストラクタ,デストラクタ;
		errorManager();
		~errorManager();
	// } コンストラクタ,デストラクタ;

	// { override
		bool Awake() override;
	
		//更新も描画もしない;
		bool Update()override { return false; };
		void Print() override {};
	// } override

	//エラーログ追加;
	void AddErrorLog(const char* newlog);
	void AddErrorLog(const errorData* newlog);
};