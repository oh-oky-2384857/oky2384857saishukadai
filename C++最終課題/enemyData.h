#pragma once
#include <string>
#include <DxLib.h>

struct enemyData
{
public:
	float moveSpeed;		//移動速度;
	float hp;				//Hp;
	float atk;				//攻撃力;
	std::string* handlePath;//画像のパス;
	int handle;				//画像ハンドル;
	int width;				//画像の縦幅;
	int height;				//      横幅;

public :
	bool Load(float ms , float hp,std::string* handleP) {
		if (ms < 0 || hp <= 0 || handleP->empty()) {//無効なデータが入ったら;
			return false;
		}
		moveSpeed = ms;
		hp = hp;
		handlePath = handleP;

		return true;
	}
	bool LoadImg() {
		handle = LoadGraph(handlePath->c_str());
		if (handle == -1) {
			return false;
		}
		GetGraphSize(handle, &width, &height);
		return true;
	}
	~enemyData(){
		if (handle != -1) {
			DeleteGraph(handle);
			delete handlePath;
		}
	}
};