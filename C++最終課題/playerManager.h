#pragma once
#include "manager.h"

// 前方宣言
class gameMainManager;
class player;
struct coordinate;
struct moveInputData;

class playerManager : public manager {
private:	
	player* oplayer;//プレイヤーの実体;

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