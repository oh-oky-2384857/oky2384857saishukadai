#pragma once
#include <fstream>
#include "entity.h"

//�O���錾;
class playerManager;
struct weaponData;

class weapon :public entity {
private:
	weaponData* data;

	playerManager* ptrPlayerManager;
	errorData* Awake() override { return nullptr; };
public:
	weapon(playerManager* ptrPM, coordinate pos, weaponData* d);
	~weapon();

	bool Awake(std::ifstream ifs);
	bool Update()override { return true; };
	void Print() override;
};