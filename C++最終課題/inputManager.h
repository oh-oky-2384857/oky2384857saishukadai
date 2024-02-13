#pragma once
#include "manager.h"

//�O���錾;
struct inputData;
class gameManager;

class inputManager:public manager
{
private:
	//inputData�̕ێ�;
	inputData* inputs;

	gameManager* ptrGameManager;
public:
	inputManager(gameManager* ptrGM);
	~inputManager();
	bool Awake() override;
	bool Update()override;
	void Print() override;

	//�}�E�X�̍X�V����;
	void MouseUpdate();
	//�ړ��̍X�V����;
	void MoveUpdate();
	//shot�̍X�V����;
	void ShotUpdate();
	//pause�̍X�V����;
	void PauseUpdate();

	const inputData* GetInputDataPtr()const;
};