#pragma once
#include "entity.h"
#include "shotData.h"

//ëOï˚êÈåæ;
class playerShotManager;


class playerShot : public entity {
private:
	shotData* data;
	playerShotManager* ptrPlayerShot;
public:
	playerShot(shotData* d, playerShotManager* ptrPS);
	~playerShot();

	virtual bool Awake() { return true; };
	virtual bool Update();
	virtual void Print() ;

	void Move();
};

class psNormal : public playerShot {
public:
	psNormal(shotData* d, playerShotManager* ptrPS);
	~psNormal();

	bool Awake() { return true; };
	bool Update();
	void Print() { playerShot::Print(); };
};