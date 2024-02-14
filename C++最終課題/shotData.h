#pragma once
#include "gameCommon.h"

/**
//弾の種類;
*@param none	0 なし
*@param normal	1 通常弾
*/
enum class shotType {
	none,
	normal,	//通常弾;
};

/**
ショットデータのうち弾の種類で一意に定まるもの;
*@param <shotType>	type				ショットの種類;
*@param <int>		handle				画像ハンドル;
*@param <flaot>		moveSpeed			移動速度;
*@param <flaot>		damageMultiplier	ダメージ倍率;
*/
struct  shotPatternData {
	shotType type;
	int shotCoolTime;
	int handle;
	float moveSpeed;
	float damageMultiplier;//ダメージ倍率、これに自機の攻撃力をかけてダメージを出す;
};

/**
ショットデータのうち一発ごとに異なるもの;
*@param const	<shotPatternData*>	pData			ショットデータの金型;
*@param			<coordinate>		position		座標;
*@param			<vector2>			positionFloat	座標のfloat番;
*@param			<vector2>			vec2			この弾の方向ベクトル;
*@param			<float>				damage			与えるダメージ;
*/
struct shotData {
public:
	const shotPatternData* pData;
	coordinate position;
	vector2 positionFloat;
	vector2 vec2;
	float damage;
public:
	shotData(coordinate pos, vector2 v2,float atk,const shotPatternData* pd) 
		:pData(pd), position(pos), vec2(v2),
		positionFloat(vector2{ position.x,position.y }){
		damage = atk * pData->damageMultiplier;
	}
	~shotData() {};
	shotData& operator=(const shotData& data) {
		pData = data.pData;
		position = data.position;
		vec2 = data.vec2;
		positionFloat = { position.x,position.y };
		damage = data.damage;
		return *this;
	}
};
