#pragma once
#include <list>
#include <vector>
#include "manager.h"
#include "enemyData.h"

//前方宣言;
class enemy;

class player;
class playerManager;
class gameMainManager;

struct shotData;

//敵種類;
enum class enemyType {
	none,
	e001,
};

//敵追加ウェーブの敵種類と追加数;
struct enemyWavePiece {
	enemyType t;	
	int amount;
};

class enemyManager:public manager {
private:
	std::list<enemy*>enemys;//敵実体;

	std::vector<enemyData*>datas;//敵データ;

	std::vector<std::vector<enemyWavePiece*>> waves;//ウェーブデータ;

	int waveAmount;//ウェーブ数;
	int waveAddTime;//敵ウェーブ追加間隔;
	int enemyTypeAmount;//敵種類;

	int enemyWaveAddCnt;//敵追加のカウンタ;
	//関数呼び出し用;
	playerManager* ptrPlayerManager;
	gameMainManager* ptrGameMain;

public:
	enemyManager(gameMainManager* ptrGM);
	~enemyManager();

	bool Awake() override;
	bool Update()override;
	void Print() override;

	//敵追加;
	bool Add(enemyType et, coordinate pos);

	//プレイヤーのポインタ取得;
	//enemyがプレイヤーの座標を入手するときなどで使う;
	const player* GetPlayerPtr()const;
	//プレイヤーマネージャー取得;
	inline playerManager* GetPlayerManagerPtr() {return ptrPlayerManager;}

	/**
	ショットが敵に当たったか
	*@returns bool true:接触,false:非接触;
	*/
	bool ShotCheckHitEnemy(shotData* s, int radius);
};