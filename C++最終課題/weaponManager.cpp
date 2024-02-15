#include <fstream>
#include "weaponManager.h"
#include "weapon.h"
#include "weaponData.h"
#include "gameMainManager.h"
#include "playerManager.h"

#include "errorCode.h"

using namespace std;

//weaponの画像パスが書かれているtxtファイルのパス;
const string WEAPON_HANDLE_DATA_PATH = { "./resource/gameMainResource/weaponResource/weaponData.txt" };



weaponManager::weaponManager(gameMainManager* ptrGM) 
:ptrGameMain(ptrGM){
	weapons.clear();
	manager::SetManagerName("weaponManager");
}
weaponManager::~weaponManager() {
	for (weapon* w : weapons) {
		delete w;
	}
	weapons.clear();
}
errorData* weaponManager::Awake() {
	//プレイヤーマネージャー取得;
	ptrPlayerManager = (playerManager*)ptrGameMain->GetManagerPtr("playerManager");
	if (ptrPlayerManager == nullptr) {
		errorData* data = new errorData{ errorCode::objectNotFound,errorSource::weaponManager ,"playerManagerがない" };
		return data;
	}
	ifstream ifs(WEAPON_HANDLE_DATA_PATH.c_str());
}
bool weaponManager::Update(){
	return true;
}
void weaponManager::Print() {

}

bool weaponManager::Add(coordinate pos, weaponData* d) {
	weapon* newW = new weapon(ptrPlayerManager, pos, d);
	ifstream ifs();
	return true;
}