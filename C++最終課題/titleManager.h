#pragma once
#include "sceneManager.h"
#include <string>

// 前方宣言;
class gameManager;

class titleManager :public sceneManager {
private:
	// 外部ファイルから読み込む;
	// ./resource/titleResource/title.png ;
	int titleHandle;

public:
	titleManager(gameManager* pgm);
	~titleManager();
	bool Awake();
	bool Update();
	void Print();
};