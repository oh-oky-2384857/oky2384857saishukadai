#pragma once
#include <list>
#include "manager.h"

// 前方宣言;
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

	//関数呼び出し用;
	pauseManager* ptrPauseManager;

	gameStatus gs;
public:
	gameManager();
	gameManager(sceneManager* scene);//シーン指定コンストラクタ;
	~gameManager();

	bool Awake() override;
	bool Update()override;
	void Print() override;

	bool SetNewScene(sceneManager* newScene);

	manager* GetManagerPtr(const char* managerName);

	inline void SetGameStatus(gameStatus gameS) { gs = gameS; };
	inline gameStatus GetGameStatus() const { return gs; };
};