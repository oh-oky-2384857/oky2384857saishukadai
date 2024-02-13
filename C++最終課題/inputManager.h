#pragma once
#include "manager.h"

//前方宣言;
struct inputData;
class gameManager;

class inputManager:public manager
{
private:
	//inputDataの保持;
	inputData* inputs;

	gameManager* ptrGameManager;
public:
	inputManager(gameManager* ptrGM);
	~inputManager();
	bool Awake() override;
	bool Update()override;
	void Print() override;

	//マウスの更新処理;
	void MouseUpdate();
	//移動の更新処理;
	void MoveUpdate();
	//shotの更新処理;
	void ShotUpdate();
	//pauseの更新処理;
	void PauseUpdate();

	const inputData* GetInputDataPtr()const;
};