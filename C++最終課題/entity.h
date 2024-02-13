#pragma once
#include "object.h"
#include "gameCommon.h"

class entity :public object {
private:
protected:
	coordinate position;//íÜêSç¿ïW;
public:
	virtual bool Awake() = 0;
	virtual bool Update() = 0;
	virtual void Print() = 0;

	bool SetPos(coordinate pos) { position = pos; };
	const coordinate GetPos() { return position; };

};	