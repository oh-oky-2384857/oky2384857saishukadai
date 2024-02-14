#pragma once
#include <list>
#include "manager.h"

//�O���錾;
class weapon;

class weaponManager :public manager{
private:
	std::list<weapon*> weapons;

public:
	bool Awake() override;
	bool Update()override;
	void Print() override;

	bool Add();
};