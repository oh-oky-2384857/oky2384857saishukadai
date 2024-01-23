#include <string>
#include <fstream>
#include <sstream>
#include <DxLib.h>
#include "player.h"
#include "gameCommon.h"

//プレイヤーの画像のパス;
const std::string PLAYER_HANDLE_PATH[] =
{
	"./resource/gameMainResource/playerResource/player01.png",
};

//プレイヤーのステータスのパス;
const std::string PLAYER_STATUS_PATH = { "./resource/gameMainResource/playerResource/playerStatus.txt" };

//プレイヤーの移動力を割る数;
const int DIVITION_PLAYER_MOVE_POWER = 10;

//プレイヤーの画像の表示地点の中心座標;
const coordinate PLAYER_PRINT_POINT = { 320,240 };

player::player() :position(0,0), coordFractionX(0.0f), coordFractionY(0.0f) {

}
player::player(coordinate coord) :position(coord), coordFractionX(0.0f), coordFractionY(0.0f) {

}
player::~player() {
	if (playerHandle != -1) {
		DeleteGraph(playerHandle);
	}
}

bool player::Awake() {
	return true;
}
bool player::Update() {
	if (std::abs((int)coordFractionX) > 1) {
		position.x += (int)coordFractionX;
		coordFractionX -= (int)coordFractionX;
	}
	if (std::abs((int)coordFractionY) > 1) {
		position.y += (int)coordFractionY;
		coordFractionY -= (int)coordFractionY;
	}
	return true;

}
void player::Print() {
	DrawGraph(PLAYER_PRINT_POINT.x - playerHandleWidth / 2,
		PLAYER_PRINT_POINT.y - playerHandleHeight / 2, playerHandle, true);
}

bool player::LoadPlayerHandle() {
	playerHandle = LoadGraph(PLAYER_HANDLE_PATH[0].c_str());
	if (playerHandle == -1) {
		return false;
	}
	GetGraphSize(playerHandle, &playerHandleWidth, &playerHandleHeight);
	return true;
}

bool player::LoadStatus() {
	std::ifstream ifs(PLAYER_STATUS_PATH.c_str());

	//ファイルがなければブルスク行き;
	if (ifs.fail()) {
		ifs.close();
		return false;
	}

	//読み込み;
	std::string s;
	std::getline(ifs, s);
	std::stringstream ss(s);
	ss >> playerMoveSpeed;
	
	ifs.close();

	return true;
}
void player::AddMovePower(int moveX, int moveY) {
	coordFractionX += moveX * playerMoveSpeed / DIVITION_PLAYER_MOVE_POWER;
	coordFractionY += moveY * playerMoveSpeed / DIVITION_PLAYER_MOVE_POWER;

}