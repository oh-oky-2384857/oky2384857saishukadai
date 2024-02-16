#pragma once
#include <string>
#include "sceneManager.h"

// 前方宣言
class gameManager;
struct errorData;

/**
エラーが起きたらブルスク画面にする;
エラーの種類と発生場所も表示する;
ブルスク画面でエラーが出たら強制終了;
*/
class blueScreenManager:public sceneManager {
private:
	std::string* errorCodeMassage;//エラーコードの文字列;
	std::string* errorSourceMassage;//エラーソースの文字列;
	std::string* note;	//備考;
public:
	blueScreenManager(gameManager* ptrGameManager, errorData* data);
	~blueScreenManager();
	errorData* Awake();
	bool Update();
	void Print();
};