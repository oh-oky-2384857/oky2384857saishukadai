#pragma once
#include "manager.h"

//�O���錾;
struct inputDate;
class gameManager;

class inputManager:public manager
{
private:
	//inputDate�̕ێ�;
	inputDate* inputs;

	gameManager* ptrGameManager;
public:
	inputManager(gameManager* ptrGM);
	~inputManager();
	bool Awake() ;
	bool Update();
	void Print() {};

	//�}�E�X�̍X�V����;
	void MouseUpdate();
	//�ړ��̍X�V����;
	void MoveUpdate();

	inputDate* TellInputDataPtr();
};