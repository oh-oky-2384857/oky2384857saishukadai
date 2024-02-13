#pragma once
#include <string>
#include "object.h"
#include "gameCommon.h"


class manager :public object{
private:

	std::string* managerName;//manager�̖��O;

public:
	//�f�t�H���g�R���X�g���N�^;
	manager() :managerName(nullptr) {};
	virtual ~manager() 
	{
		if (managerName != nullptr) {
			delete managerName;
		}
	}

	virtual bool Awake() = 0;
	virtual bool Update() = 0;
	virtual void Print() = 0;

	//managerName�ݒ�;
	//����string�^;
	bool SetManagerName(std::string* s) { 
		if (managerName == nullptr) {
			//���O���ݒ肳��Ă��Ȃ����;
			managerName = s;	
			return true;
		}else {
			//�ݒ肳��Ă����;
			return false;
		}
	};
	
	//managerName�ݒ�;
	//����char�^;
	bool SetManagerName(const char* c) {
		if (managerName == nullptr) {
			//���O���ݒ肳��Ă��Ȃ����;
			managerName = new std::string(c);
			return true;
		}
		else {
			//�ݒ肳��Ă����;
			return false;
		}
	}

	//managerName�擾;
	const std::string* GetManagerName() const { return managerName; };
	const std::string GetManagerNameInstans() const{
		std::string result(managerName->c_str());
		return result;
	};
};