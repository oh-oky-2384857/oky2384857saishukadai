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

	virtual bool Awake() { return true; };
	virtual bool Update();
	virtual void Print() ;
	
	//�ړ�;
	void Move();
};

class psNormal : public playerShotBase {
public:
	psNormal(shotData* d, playerShotManager* ptrPS);
	~psNormal();

	bool Awake() { return true; };
	bool Update();
	void Print() { playerShotBase::Print(); };
};