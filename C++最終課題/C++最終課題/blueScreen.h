#pragma once
#include <string>
#include "sceneManager.h"

// �O���錾
class gameManager;
class colorSample;
struct errorData;

//�G���[���N������u���X�N��ʂɂ���;
//�G���[�̎�ނƔ����ꏊ���\������;
//�u���X�N��ʂŃG���[���o���狭���I��;

class blueScreenManager:public sceneManager {
private:
	std::string* errorCodeMassage;
	std::string* errorSourceMassage;
	colorSample* colorS;
public:
	blueScreenManager(gameManager* ptrGameManager, errorData* data);
	~blueScreenManager();
	bool Awake();
	bool Update();
	void Print();
};