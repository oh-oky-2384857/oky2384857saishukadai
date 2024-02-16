#include <string>
#include <DxLib.h>

#include "gameManager.h"
#include "blueScreen.h"
#include "titleManager.h"

#include "inputManager.h"
#include "sceneManager.h"
#include "cursorManager.h"
#include "pauseManager.h"

using namespace std;

gameManager::gameManager():gs(gameStatus::title) {
	manager::SetManagerName("gameManager");
	nowScene = new titleManager(this);

	managers =
	{
		new inputManager(this),
		new pauseManager(this),
		new cursorManager(this),
	};
}

gameManager::~gameManager() {
	for (manager* m : managers) {
		delete m;
	}
	managers.clear();
	delete nowScene;
	InitGraph();
}

errorData* gameManager::Awake() {
	//nowSceneのAwakeを動かす;
	errorData* e = nowScene->Awake();
	if (nullptr != e) {// Awakeに失敗したら;

		sceneManager* newScene = new blueScreenManager(this, e);
		SetNewScene(newScene);
		return nullptr;//処理を終わらせるためのreturn;
	}
	//各種managerのAwakeを動かす;
	for (manager* m : managers) {
		e = m->Awake();
		if (e != nullptr){// Awakeに失敗したら;
			sceneManager* newScene = new blueScreenManager(this, e);
			SetNewScene(newScene);
			return nullptr;//処理を終わらせるためのreturn;
		}
	}
	return nullptr;//処理を終わらせるためのreturn;
}
bool gameManager::Update() {
	//ポーズまたはオプションでないなら;
	if (gs != gameStatus::pauseMenu && gs != gameStatus::option) {
		//nowSceneのUpdateを動かす;
		nowScene->Update();
	}
	//各種managerのUpdateを動かす;
	for (manager* m : managers) {
		m->Update();
	}
	return true;
}
void gameManager::Print() {
	//nowSceneのPrintを動かす;
	nowScene->Print();
	//各種managerのPrintを動かす;
	for (manager* m : managers) {
		m->Print();
	}
}

bool gameManager::SetNewScene(sceneManager* newScene) {
	//今のシーンを削除;
	delete nowScene;
	//新しいシーンを設定しAwakeを動かす;
	nowScene = newScene;
	nowScene->Awake();
	return true;
}

manager* gameManager::GetManagerPtr(const char* managerName) {
	//managerNameからマネージャのポインタを返す;
	for (manager* m : managers) {
		//文字列比較,一致すればそれを返す;
		if (strcmp(m->GetManagerName()->c_str(), managerName) == 0) {
			return m;
		}
	}
	//何も一致しなければnullptrを返す;
	return nullptr;
}