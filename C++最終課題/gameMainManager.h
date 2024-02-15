#pragma once
#include "sceneManager.h"
#include <list>

// �O���錾;
class gameManager;
class sceneManager;
struct mouseinputData;
struct errorData;
struct inputData;

class gameMainManager :public sceneManager{
private:

	std::list<manager*> managers;
	//�V�[���Έ�;
	int changeSceneCnt;	//�V�[�����ς��܂ł̃J�E���^;
	sceneManager* nextScene;//���̃V�[��;

	/**
	���Q�[���������Ă��邩;
	true  : �����Ă���;
	false : �����Ă��Ȃ�;
	*/
	bool gamingFlag;

	int gameStateHandle;//�\������摜�n���h��;

	//�Q�[���I�[�o�[�֘A;
	int gameOverHandle;	//�摜�n���h��;
	//�Q�[���N���A�֘A;
	int gameClearHandle;//�摜�n���h��;

public:
	gameMainManager(gameManager* ptrGM);
	~gameMainManager();

	errorData* Awake() override;
	bool Update()override;
	void Print() override;

	manager* GetManagerPtr(const char* managerName);

	void ChangeBlueScreen(errorData* data);

	const inputData* GetInputData();

	inline bool GetGamingFlag() { return gamingFlag; };
	void SetGameOver();
	void SetGameClear();

};