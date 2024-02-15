#pragma once
#include <string>
#include "sceneManager.h"

// �O���錾
class gameManager;
struct errorData;

//�G���[���N������u���X�N��ʂɂ���;
//�G���[�̎�ނƔ����ꏊ���\������;
//�u���X�N��ʂŃG���[���o���狭���I��;

class blueScreenManager:public sceneManager {
private:
	std::string* errorCodeMassage;
	std::string* errorSourceMassage;
	std::string* note;	//���l;
public:
	blueScreenManager(gameManager* ptrGameManager, errorData* data);
	~blueScreenManager();
	errorData* Awake();
	bool Update();
	void Print();
};