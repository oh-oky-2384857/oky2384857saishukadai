#pragma once
#include "entity.h"
#include "shotData.h"

//‘O•ûéŒ¾;
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
	
	//ˆÚ“®;
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