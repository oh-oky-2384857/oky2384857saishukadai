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

	virtual bool Awake() = 0;
	virtual bool Start() { return true; };//Awakeの直後に動かす;
	virtual bool Update() = 0;
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
	const std::string* GetManagerName() const { return managerName; };
	const std::string GetManagerNameInstans() const{
		std::string result(managerName->c_str());
		return result;
	};
};