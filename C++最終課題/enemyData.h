#pragma once
#include <string>
#include <DxLib.h>


/**
敵データのうち、一体ごと異なるもの;
*@param <float>	 moveSpeed	移動速度;
*@param <flaot>	 hp			Hp;
*@param <flaot>	 atk		攻撃力;
*@param <string> handlePath	画像のパス;
*@param <int>	 handle		画像ハンドル;
*@param <int>	 width		画像の縦幅;
*@param <int>	 height			  横幅;
*/
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
	bool Load(float ms , float hp,float atk,std::string* handleP) {
		if (ms < 0 || hp <= 0 || atk < 0||handleP->size() == 0) {//無効なデータが入ったら;
			return false;
		}
		moveSpeed = ms;
		enemyData::hp = hp;
		enemyData::atk = atk;
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