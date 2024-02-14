#include <DxLib.h>
#include <sstream>
#include "weapon.h"
#include "weaponData.h"
#include "playerManager.h"
#include "player.h"

using namespace std;

//weaponの画像パスが書かれているtxtファイルのパス;
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
	//画像のパス読み込み;
	//ifsはファイルが開いた状態で来る;
	stringstream inputSt;
	string input;

	for (int i = 0; i < (int)data->type - 1; i++) {
		inputSt.clear(); inputSt.str("");//初期化;

		std::getline(ifs,input);
		inputSt << input;
	}

	string path;
	inputSt >> path;

	//画像読み込み;
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
