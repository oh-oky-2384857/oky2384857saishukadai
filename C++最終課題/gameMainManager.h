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

	int gameStateHandle;//表示する画像ハンドル;

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

	manager* GetManagerPtr(const char* managerName);

	void ChangeBlueScreen(errorData* data);

	const inputData* GetInputData();

	inline bool GetGamingFlag() { return gamingFlag; };
	void SetGameOver();
	void SetGameClear();

};