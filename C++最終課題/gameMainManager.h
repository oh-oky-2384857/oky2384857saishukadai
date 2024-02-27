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

	int gameStateHandle;//�Q�[���I�[�o�[�܂��̓Q�[���N���A����;

	//�Q�[���I�[�o�[�֘A;
	int gameOverHandle;	//�摜�n���h��;
	//�Q�[���N���A�֘A;
	int gameClearHandle;//�摜�n���h��;

public:
	gameMainManager(gameManager* ptrGM);
	~gameMainManager();

	bool Awake() override;
	bool Update()override;
	void Print() override;

	//�}�l�[�W���[�|�C���^�擾;
	manager* GetManagerPtr(const char* managerName);

	//�u���[�X�N���[���V�[���ɋ����ψ�;
	void ChangeBlueScreen(errorData* data);

	//�C���v�b�g�f�[�^�̃|�C���^�擾;
	const inputData* GetInputData();

	/**
	���Q�[���������Ă��邩;
	*@return true : �����Ă���,false : �����Ă��Ȃ�;
	*/
	inline bool GetGamingFlag() { return gamingFlag; };

	//�Q�[���I�[�o�[�ɂ���;
	void SetGameOver();

	//�Q�[���N���A�ɂ���;
	void SetGameClear();

};