#pragma once
#include "sceneManager.h"
#include <string>

// 前方宣言;
class gameManager;

struct mouseInputData;

class titleManager :public sceneManager {
private:
	// 外部ファイルから読み込む;
	// ./resource/titleResource/title.png ;
	int titleHandle;
	//入力受け取り;
	mouseInputData* input;

public:
	titleManager(gameManager* pgm);
	~titleManager();
	errorData* Awake() override;
	bool Update()override;
	void Print() override;
};