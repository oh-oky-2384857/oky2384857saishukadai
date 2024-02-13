#pragma once
#include "manager.h"

// 前方宣言
class gameMainManager;
class player;
struct coordinate;
struct moveInputDate;

class playerManager : public manager {
private:	
	player* oplayer;//プレイヤーの実体;

	gameMainManager* ptrGameMain;

	moveInputDate* moveInput;
public:
	playerManager(gameMainManager* ptrGM);
	~playerManager();
	bool Awake();
	bool Update();
	void Print();

	const player* GetPlayerPtr() const { return oplayer; }

	void AddDamage(int damage);
};