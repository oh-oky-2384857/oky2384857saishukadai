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

	virtual void Awake() = 0;
	virtual void Update() = 0;
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
	std::string* GetManagerName() { return managerName; };
};