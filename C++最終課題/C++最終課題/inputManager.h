#pragma once
#include "manager.h"
#include "inputDate.h"

struct inputDate;


class inputManager:public manager
{
private:
	//inputDate‚Ì•Û;
	inputDate* inputs;
public:
	inputManager();
	~inputManager();
	void Awake() {};
	void Update();
	void Print() {};

	bool TellInputMouse(mouseInputDate date);//ƒ}ƒEƒX‚Ì“ü—Í‚ª‚ ‚Á‚½‚Æ‚«;
};