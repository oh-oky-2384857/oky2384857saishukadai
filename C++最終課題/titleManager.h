#pragma once
#include "sceneManager.h"
#include <string>

// �O���錾;
class gameManager;

class titleManager :public sceneManager {
private:
	// �O���t�@�C������ǂݍ���;
	// ./resource/titleResource/title.png ;
	int titleHandle;
public:
	titleManager(gameManager* pgm);
	~titleManager();
	void Awake() {};
	void Update() {};
	void Print();
};