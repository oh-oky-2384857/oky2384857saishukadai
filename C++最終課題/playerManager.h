#pragma once
#include "manager.h"

// �O���錾
class gameMainManager;
class player;
struct coordinate;
struct moveInputData;

class playerManager : public manager {
private:	
	player* oplayer;//�v���C���[�̎���;

	gameMainManager* ptrGameMain;

	moveInputData* moveInput;
public:
	playerManager(gameMainManager* ptrGM);
	~playerManager();
	bool Awake() override;
	bool Update()override;
	void Print() override;

	const player* GetPlayerPtr() const { return oplayer; }

	void AddDamage(int damage);
};