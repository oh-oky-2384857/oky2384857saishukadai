#include <string>
#include <DxLib.h>

#include "gameManager.h"
#include "blueScreen.h"
#include "titleManager.h"

#include "inputManager.h"
#include "sceneManager.h"
#include "cursorManager.h"
#include "pauseManager.h"

#include "errorCode.h"
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

bool gameManager::Awake() {
	//nowScene��Awake�𓮂���;
	if (!nowScene->Awake()) {// Awake�Ɏ��s������;
		return false;
	}
	//�e��manager��Awake�𓮂���;
	for (manager* m : managers) {
		if (!m->Awake())
		{
			return false;
		}
	}
	return true;
}
bool gameManager::Update() {
	//�|�[�Y�܂��̓I�v�V�����łȂ��Ȃ�;
	if (gs != gameStatus::pauseMenu && gs != gameStatus::option) {
		//nowScene��Update�𓮂���;
		nowScene->Update();
	}
	//�e��manager��Update�𓮂���;
	for (manager* m : managers) {
		m->Update();
	}
	return true;
}
void gameManager::Print() {
	//nowScene��Print�𓮂���;
	nowScene->Print();
	//�e��manager��Print�𓮂���;
	for (manager* m : managers) {
		m->Print();
	}
}

bool gameManager::SetNewScene(sceneManager* newScene) {
	//���̃V�[�����폜;
	delete nowScene;
	//�V�����V�[����ݒ肵Awake�𓮂���;
	nowScene = newScene;
	nowScene->Awake();
	return true;
}

manager* gameManager::GetManagerPtr(const char* managerName) {
	//managerName����}�l�[�W���̃|�C���^��Ԃ�;
	for (manager* m : managers) {
		//�������r,��v����΂����Ԃ�;
		if (strcmp(m->GetManagerName()->c_str(), managerName) == 0) {
			return m;
		}
	}
	//������v���Ȃ����nullptr��Ԃ�;
	return nullptr;
}