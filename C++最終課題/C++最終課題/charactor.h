#pragma once
#include "object.h"
#include "gameCommon.h"

class charactor:public object {
private:
	
	coordinate position;//íÜêSç¿ïW

public:
	virtual bool Awake() = 0;
	virtual bool Update() = 0;
	virtual void Print() = 0;

	bool SetPos(coordinate pos) { position = pos; };
	coordinate GetPos() { return position; };
};	