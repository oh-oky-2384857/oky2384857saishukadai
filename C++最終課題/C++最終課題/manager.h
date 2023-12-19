#pragma once
#include <string>
#include "object.h"
#include "gameCommon.h"


class manager :public object{
private:

	std::string* managerName;//managerの名前;

public:
	//デフォルトコンストラクタ;
	manager() :managerName(nullptr) {};
	virtual ~manager() 
	{
		if (managerName != nullptr) {
			delete managerName;
		}
	}

	virtual void Awake() = 0;
	virtual void Update() = 0;
	virtual void Print() = 0;

	//managerName設定;
	//引数string型;
	bool SetManagerName(std::string* s) { 
		if (managerName == nullptr) {
			//名前が設定されていなければ;
			managerName = s;	
			return true;
		}else {
			//設定されていれば;
			return false;
		}
	};
	
	//managerName設定;
	//引数char型;
	bool SetManagerName(const char* c) {
		if (managerName == nullptr) {
			//名前が設定されていなければ;
			managerName = new std::string(c);
			return true;
		}
		else {
			//設定されていれば;
			return false;
		}
	}

	//managerName取得;
	std::string* GetManagerName() { return managerName; };
};