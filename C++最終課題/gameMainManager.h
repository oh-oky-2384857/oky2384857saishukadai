#pragma once
#include "sceneManager.h"
#include <list>

// �O���錾;
class gameManager;
struct mouseinputData;
struct errorData;
struct inputData;

class gameMainManager :public sceneManager{
private:

	std::list<manager*> managers;

	//�Q�[���I�[�o�[�֘A;
	int gameOverHandle;		//�摜�n���h��;
	int gameOverPrintCnt;	//�\�����鎞��;
	bool gameOverFlag;		//���Q�[���I�[�o�[��;

public:
	gameMainManager(gameManager* ptrGM);
	~gameMainManager();

	bool Awake() override;
	bool Update()override;
	void Print() override;

	manager* GetManagerPtr(const char* managerName);

	void ChangeBlueScreen(errorData* data);

	const inputData* GetInputData();

	inline bool GetGameOverFlag() { return gameOverFlag; };
	void SetGameOver();
};