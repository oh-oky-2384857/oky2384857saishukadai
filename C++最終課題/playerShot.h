#pragma once
#include "entity.h"
#include "shotData.h"

//�O���錾;
class playerShotManager;


class playerShotBase : public entity {
private:
	shotData* data;
	playerShotManager* ptrPlayerShot;
public:
	playerShotBase(shotData* d, playerShotManager* ptrPS);
	~playerShotBase();

	virtual errorData* Awake() { return nullptr; };
	virtual bool Update();
	virtual void Print() ;
	
	//�ړ�;
	void Move();
};

class psNormal : public playerShotBase {
public:
	psNormal(shotData* d, playerShotManager* ptrPS);
	~psNormal();

	errorData* Awake() { return nullptr; };
	bool Update();
	void Print() { playerShotBase::Print(); };
};