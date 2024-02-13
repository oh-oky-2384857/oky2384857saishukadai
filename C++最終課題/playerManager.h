#pragma once
#include "manager.h"

// 前方宣言
class gameMainManager;
class player;
class playerShotManager;
struct coordinate;
struct moveInputData;
struct shotInputData;
struct shotPatternData;

class playerManager : public manager {
private:	
	player* oplayer;//プレイヤーの実体;

	gameMainManager* ptrGameMain;
	playerShotManager* ptrPlayerShotManager;

	//shot関連;
	int shotCoolTimeCnt;//弾発射の冷却時間のカウンタ;
	shotPatternData* nowShotData;//現在発射する弾データ;

	//入力受け取り;
	moveInputData* moveInput;
	shotInputData* shotInput;
public:
	playerManager(gameMainManager* ptrGM);
	~playerManager();
	bool Awake() override;
	bool Start() override;
	bool Update()override;
	void Print() override;

	const player* GetPlayerPtr() const { return oplayer; }

	void AddDamage(int damage);
};