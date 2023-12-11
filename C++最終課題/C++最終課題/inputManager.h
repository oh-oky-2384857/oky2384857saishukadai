#pragma once
#include "manager.h"
#include "inputDate.h"

struct inputDate;


class inputManager:public manager
{
private:
	//inputDateの保持;
	inputDate* inputs;
public:
	inputManager();
	~inputManager();
	void Awake() {};
	void Update();
	void Print() {};

	bool TellInputMouse(mouseInputDate date);//マウスの入力があったとき;
};