#pragma once
#include "entity.h"


//‘O•ûéŒ¾;



class playerShot : public entity {
private:
	int handle;

public:
	playerShot(coordinate coord);
	~playerShot();

	virtual bool Awake() { return true; };
	virtual bool Update() { return true; };
	virtual void Print() ;
};

class psNormal : public playerShot {
	bool Awake() { return true; };
	bool Update() { return true; };
	void Print() { playerShot::Print(); };
};