#pragma once
#include "entity.h"
#include "shotData.h"

//前方宣言;
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
	
	//移動;
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