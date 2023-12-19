#pragma once
#include "manager.h"

//前方宣言;
struct inputDate;
class gameManager;

class inputManager:public manager
{
private:
	//inputDateの保持;
	inputDate* inputs;

	gameManager* ptrGM;
public:
	inputManager(gameManager* ptrGM);
	~inputManager();
	void Awake() {};
	void Update();
	void Print() {};

	//マウスの更新処理;
	void MouseUpdate();

	inputDate* TellInputDataPtr();
};