#pragma once
#include <string>
#include "sceneManager.h"

// 前方宣言
class gameManager;
class colorSample;
struct errorData;

//エラーが起きたらブルスク画面にする;
//エラーの種類と発生場所も表示する;
//ブルスク画面でエラーが出たら強制終了;

class blueScreenManager:public sceneManager {
private:
	std::string* errorCodeMassage;
	std::string* errorSourceMassage;
	colorSample* colorS;
public:
	blueScreenManager(gameManager* ptrGameManager, errorData* data);
	~blueScreenManager();
	bool Awake();
	bool Update();
	void Print();
};