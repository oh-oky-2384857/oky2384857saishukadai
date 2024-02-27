#pragma once
#include "sceneManager.h"
#include <string>

// �O���錾;
class gameManager;

struct mouseInputData;

class titleManager :public sceneManager {
private:
	// �O���t�@�C������ǂݍ���;
	// ./resource/titleResource/title.png ;
	int titleHandle;
	//���͎󂯎��;
	mouseInputData* input;

public:
	titleManager(gameManager* pgm);
	~titleManager();
	bool Awake() override;
	bool Update()override;
	void Print() override;
};