#include "playerManager.h"
#include "gameCommon.h"
#include <string>
#include <DxLib.h>

//�v���C���[�̉摜�̃p�X;
const std::string PLAYER_HANDLE_PATH[] =
{
	"./resource/gameMainResource/playerResource/player01.png",
};

//�v���C���[�̉摜�̕\���n�_�̒��S���W;
const coordinate PLAYER_PRINT_POINT = {320,240};

playerManager::playerManager() {
	playerHandle = LoadGraph(PLAYER_HANDLE_PATH[0].c_str());
	if (playerHandle == -1) {
		exit(1);
	}
	GetGraphSize(playerHandle, &playerHandleWidth, &playerHandleHeight);
}
playerManager::~playerManager() {
	DeleteGraph(playerHandle);
}
bool playerManager::Awake() {
	return true;
}
bool playerManager::Update() {
	return true;

}

void playerManager::Print() {
	DrawGraph(PLAYER_PRINT_POINT.x - playerHandleWidth / 2,
		PLAYER_PRINT_POINT.y - playerHandleHeight / 2, playerHandle, true);
}
