#pragma once
#include "manager.h"

// �O���錾
class gameMainManager;
class player;
struct coordinate;
struct moveInputDate;

class playerManager : public manager {
private:	
	player* oplayer;//�v���C���[�̎���;

	gameMainManager* ptrGameMain;

	moveInputDate* moveInput;
public:
	playerManager(gameMainManager* ptrGM);
	~playerManager();
	bool Awake();
	bool Update();
	void Print();

	const coordinate* GetPosition();
};