#include <DxLib.h>
#include <sstream>
#include "weapon.h"
#include "weaponData.h"
#include "playerManager.h"
#include "player.h"

using namespace std;

//weapon�̉摜�p�X��������Ă���txt�t�@�C���̃p�X;
const string WEAPON_HANDLE_DATA_PATH = {"./resource/gameMainResource/weaponResource/weaponData.txt"};

//weapon
weapon::weapon(playerManager* ptrPM, coordinate pos, weaponData* d) 
:ptrPlayerManager(ptrPM),data(d){
	position = pos;
}
weapon::~weapon() {
	if (data->handle != -1) {
		DeleteGraph(data->handle);
	}
}
bool weapon::Awake(std::ifstream ifs) {
	//�摜�̃p�X�ǂݍ���;
	//ifs�̓t�@�C�����J������Ԃŗ���;
	stringstream inputSt;
	string input;

	for (int i = 0; i < (int)data->type - 1; i++) {
		inputSt.clear(); inputSt.str("");//������;

		std::getline(ifs,input);
		inputSt << input;
	}

	string path;
	inputSt >> path;

	//�摜�ǂݍ���;
	data->handle = LoadGraph(path.c_str());
	if (data->handle == -1) {
		return false;
	}else {
		return true;
	}
}
void weapon::Print() {
	coordinate printPoint = coordinate{320,240} + data->relative;
	DrawGraph(printPoint.x - data->handleWidth / 2, printPoint.y - data->handleHeight / 2, data->handle, true);
}
//weapon
