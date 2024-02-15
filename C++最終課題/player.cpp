#include <string>
#include <fstream>
#include <sstream>
#include <DxLib.h>
#include "player.h"
#include "gameCommon.h"
#include "colorSample.h"


//�萔;

//�v���C���[�̉摜�̃p�X;
const std::string PLAYER_HANDLE_PATH[] =
{
	"./resource/gameMainResource/playerResource/player01.png",
};

//Hp�o�[�`��̍���;
const coordinate HP_BAR_PRINT_POINT = {295,200};

//�v���C���[�̃X�e�[�^�X�̃p�X;
const std::string PLAYER_STATUS_PATH = { "./resource/gameMainResource/playerResource/playerStatus.txt" };

//�v���C���[�̈ړ��͂����鐔;
const int DIVITION_PLAYER_MOVE_POWER = 10;

//�v���C���[�̉摜�̕\���n�_�̒��S���W;
const coordinate PLAYER_PRINT_POINT = { 320,240 };

const int HP_BAR_WIDTH = 50; //HP�o�[�̕�;
const int HP_BAR_HEIGHT = 10;//HP�o�[�̍���;

//�萔;



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

errorData* player::Awake() {
	return nullptr;
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
	if (playerHpNow < 0) {
		return false;
	}
	return true;
}
void player::Print() {
	DrawGraph(PLAYER_PRINT_POINT.x - playerHandleWidth / 2,
		PLAYER_PRINT_POINT.y - playerHandleHeight / 2, playerHandle, true);
	
	PrintHpBar();

	//�f�o�b�O�p,�v���C���[�̍��W;
	DrawFormatString(0, 0, GetColor(0, 0, 255), "x:%d,y:%d", position.x, position.y);
}

bool player::LoadPlayerHandle() {
	//�v���C���[�摜�ǂݍ���;
	playerHandle = LoadGraph(PLAYER_HANDLE_PATH[0].c_str());
	if (playerHandle == -1) {
		return false;
	}
	GetGraphSize(playerHandle, &playerHandleWidth, &playerHandleHeight);
	
	return true;
}

bool player::LoadStatus() {
	std::ifstream ifs(PLAYER_STATUS_PATH.c_str());

	//�t�@�C�����Ȃ���΃u���X�N�s��;
	if (ifs.fail()) {
		ifs.close();
		return false;
	}

	//�ǂݍ���;
	std::string s;

	//�f�[�^�ǂݍ���;
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
	//�ő�l;
	DrawBox(HP_BAR_PRINT_POINT.x, HP_BAR_PRINT_POINT.y,
		HP_BAR_PRINT_POINT.x + HP_BAR_WIDTH, HP_BAR_PRINT_POINT.y + HP_BAR_HEIGHT, colorSample::fireBrick, true);
	//�O�g;
	DrawBox(HP_BAR_PRINT_POINT.x - 1 , HP_BAR_PRINT_POINT.y - 1,
		HP_BAR_PRINT_POINT.x + HP_BAR_WIDTH + 1, HP_BAR_PRINT_POINT.y + HP_BAR_HEIGHT + 1, colorSample::black, false);
	//����Hp;
	DrawBox(HP_BAR_PRINT_POINT.x, HP_BAR_PRINT_POINT.y,
		HP_BAR_PRINT_POINT.x + (HP_BAR_WIDTH * playerHpNow / playerHpMax), HP_BAR_PRINT_POINT.y + HP_BAR_HEIGHT, colorSample::lawngreen, true);
}

bool player::AddDamage(int damage) {
	if (invincibilityTimeCnt > 0) {//���G���Ԓ��Ȃ�;
		return true;
	}
	playerHpNow -= damage;
	invincibilityTimeCnt = invincibilityTime;
	if ( playerHpNow <= 0 ) {
		return false;
	}
	return true;
}