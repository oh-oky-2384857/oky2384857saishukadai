#pragma once
#include <list>
#include "manager.h"

// �O���錾;
class pauseManager;
class sceneManager;
struct errorData;

enum class gameStatus {
	none = 0,
	title,
	pauseMenu,
	option,
	main,
	end
};

class gameManager :public manager {
private:
	sceneManager* nowScene;
	std::list <manager*> managers;

	//�֐��Ăяo���p;
	pauseManager* ptrPauseManager;

	gameStatus gs;
public:
	gameManager();
	gameManager(sceneManager* scene);//�V�[���w��R���X�g���N�^;
	~gameManager();

	bool Awake() override;
	bool Update()override;
	void Print() override;

	bool SetNewScene(sceneManager* newScene);

	manager* GetManagerPtr(const char* managerName);

	inline void SetGameStatus(gameStatus gameS) { gs = gameS; };
	inline gameStatus GetGameStatus() const { return gs; };
};