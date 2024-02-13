#pragma once
#include "sceneManager.h"
#include <list>

// 前方宣言;
class gameManager;
struct mouseinputData;
struct errorData;
struct inputData;

class gameMainManager :public sceneManager{
private:

	std::list<manager*> managers;

	//ゲームオーバー関連;
	int gameOverHandle;		//画像ハンドル;
	int gameOverPrintCnt;	//表示する時間;
	bool gameOverFlag;		//今ゲームオーバーか;

public:
	gameMainManager(gameManager* ptrGM);
	~gameMainManager();

	bool Awake() override;
	bool Update()override;
	void Print() override;

	manager* GetManagerPtr(const char* managerName);

	void ChangeBlueScreen(errorData* data);

	const inputData* GetInputData();

	inline bool GetGameOverFlag() { return gameOverFlag; };
	void SetGameOver();
};