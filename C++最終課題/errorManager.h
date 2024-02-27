#pragma once
#include <fstream>
#include "manager.h"
#include "errorCode.h"

class errorManager :public manager {
private:
	//�o�͐�;
	std::ofstream errorLogFile;
public:
	// { �R���X�g���N�^,�f�X�g���N�^;
		errorManager();
		~errorManager();
	// } �R���X�g���N�^,�f�X�g���N�^;

	// { override
		bool Awake() override;
	
		//�X�V���`������Ȃ�;
		bool Update()override { return false; };
		void Print() override {};
	// } override

	//�G���[���O�ǉ�;
	void AddErrorLog(const char* newlog);
	void AddErrorLog(const errorData* newlog);
};