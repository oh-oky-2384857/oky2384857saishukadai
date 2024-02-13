#include <string>
#include <fstream>
#include <sstream>
#include <DxLib.h>
#include "player.h"
#include "gameCommon.h"
#include "colorSample.h"


//定数;

//プレイヤーの画像のパス;
const std::string PLAYER_HANDLE_PATH[] =
{
	"./resource/gameMainResource/playerResource/player01.png",
};

//Hpバー描画の左上;
const coordinate HP_BAR_PRINT_POINT = {295,200};

//プレイヤーのステータスのパス;
const std::string PLAYER_STATUS_PATH = { "./resource/gameMainResource/playerResource/playerStatus.txt" };

//プレイヤーの移動力を割る数;
const int DIVITION_PLAYER_MOVE_POWER = 10;

//プレイヤーの画像の表示地点の中心座標;
const coordinate PLAYER_PRINT_POINT = { 320,240 };

const int HP_BAR_WIDTH = 50; //HPバーの幅;
const int HP_BAR_HEIGHT = 10;//HPバーの高さ;

//定数;



player::player() : coordFractionX(0.0f), coordFractionY(0.0f) , invincibilityTimeCnt(0){
	position = coordinate{ 0,0 };
}
player::player(coordinate coord) : coordFractionX(0.0f), coordFractionY(0.0f) {
	position = coord;
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
	invincibilityTimeCnt--;
	return true;
}
void player::Print() {
	DrawGraph(PLAYER_PRINT_POINT.x - playerHandleWidth / 2,
		PLAYER_PRINT_POINT.y - playerHandleHeight / 2, playerHandle, true);
	
	PrintHpBar();

	//デバッグ用,プレイヤーの座標;
	DrawFormatString(0, 0, GetColor(0, 0, 255), "x:%d,y:%d", position.x, position.y);
}

bool player::LoadPlayerHandle() {
	//プレイヤー画像読み込み;
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

	//データ読み込み;
	std::getline(ifs, s);
	std::stringstream ss(s);
	
	ss >> playerMoveSpeed >> playerHpMax >> playerAtk >> invincibilityTime;
	
	playerHpNow = playerHpMax;

	ifs.close();

	return true;
}
void player::AddMovePower(int moveX, int moveY) {
	coordFractionX += moveX * playerMoveSpeed / DIVITION_PLAYER_MOVE_POWER;
	coordFractionY += moveY * playerMoveSpeed / DIVITION_PLAYER_MOVE_POWER;

}

void player::PrintHpBar() {
	if (playerHpNow < 0) {
		return;
	}
	//最大値;
	DrawBox(HP_BAR_PRINT_POINT.x, HP_BAR_PRINT_POINT.y,
		HP_BAR_PRINT_POINT.x + HP_BAR_WIDTH, HP_BAR_PRINT_POINT.y + HP_BAR_HEIGHT, colorSample::fireBrick, true);
	//外枠;
	DrawBox(HP_BAR_PRINT_POINT.x - 1 , HP_BAR_PRINT_POINT.y - 1,
		HP_BAR_PRINT_POINT.x + HP_BAR_WIDTH + 1, HP_BAR_PRINT_POINT.y + HP_BAR_HEIGHT + 1, colorSample::black, false);
	//現在Hp;
	DrawBox(HP_BAR_PRINT_POINT.x, HP_BAR_PRINT_POINT.y,
		HP_BAR_PRINT_POINT.x + (HP_BAR_WIDTH * playerHpNow / playerHpMax), HP_BAR_PRINT_POINT.y + HP_BAR_HEIGHT, colorSample::lawngreen, true);
}

bool player::AddDamage(int damage) {
	if (invincibilityTimeCnt > 0) {//無敵時間中なら;
		return true;
	}
	playerHpNow -= damage;
	invincibilityTimeCnt = invincibilityTime;
	if ( playerHpNow <= 0 ) {
		return false;
	}
	return true;
}