#pragma once
#include "sceneManager.h"
#include <list>

// 前方宣言;
class gameManager;
class sceneManager;
struct mouseinputData;
struct errorData;
struct inputData;

class gameMainManager :public sceneManager{
private:

	std::list<manager*> managers;
	//シーン偏移;
	int changeSceneCnt;	//シーンが変わるまでのカウンタ;
	sceneManager* nextScene;//次のシーン;

	/**
	今ゲームが続いているか;
	true  : 続いている;
	false : 続いていない;
	*/
	bool gamingFlag;

	int gameStateHandle;//ゲームオーバーまたはゲームクリアを代入;

	//ゲームオーバー関連;
	int gameOverHandle;	//画像ハンドル;
	//ゲームクリア関連;
	int gameClearHandle;//画像ハンドル;

public:
	gameMainManager(gameManager* ptrGM);
	~gameMainManager();

	errorData* Awake() override;
	bool Update()override;
	void Print() override;

	//マネージャーポインタ取得;
	manager* GetManagerPtr(const char* managerName);

	//ブルースクリーンシーンに強制変位;
	void ChangeBlueScreen(errorData* data);

	//インプットデータのポインタ取得;
	const inputData* GetInputData();

	/**
	今ゲームが続いているか;
	*@return true : 続いている,false : 続いていない;
	*/
	inline bool GetGamingFlag() { return gamingFlag; };

	//ゲームオーバーにする;
	void SetGameOver();

	//ゲームクリアにする;
	void SetGameClear();

};