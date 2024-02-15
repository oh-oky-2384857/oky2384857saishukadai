#pragma once
#include "manager.h"

// �O���錾
class gameMainManager;
class player;
class playerShotManager;
struct coordinate;
struct moveInputData;
struct shotInputData;
struct shotPatternData;

class playerManager : public manager {
private:	
	player* oplayer;//�v���C���[�̎���;

	gameMainManager* ptrGameMain;
	playerShotManager* ptrPlayerShotManager;

	//shot�֘A;
	int shotCoolTimeCnt;//�e���˂̗�p���Ԃ̃J�E���^;
	shotPatternData* nowShotData;//���ݔ��˂���e�f�[�^;

	//���͎󂯎��;
	moveInputData* moveInput;
	shotInputData* shotInput;
public:
	playerManager(gameMainManager* ptrGM);
	~playerManager();
	errorData* Awake() override;
	errorData* Start() override;
	bool Update()override;
	void Print() override;

	const player* GetPlayerPtr() const { return oplayer; }

	void AddDamage(int damage);
};