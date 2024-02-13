#pragma once
#include "gameCommon.h"

//�e�̎��;
/**
*@param none	0 �Ȃ�
*@param normal	1 �ʏ�e
*/
enum class shotType {
	none,
	normal,	//�ʏ�e;
};

/**
�V���b�g�f�[�^�̂����e�̎�ނň�ӂɒ�܂����;
*@param <shotType>	type				�V���b�g�̎��;
*@param <int>		handle				�摜�n���h��;
*@param <flaot>		moveSpeed			�ړ����x;
*@param <flaot>		damageMultiplier	�_���[�W�{��;
*/
struct  shotPatternData {
	shotType type;
	int shotCoolTime;
	int handle;
	float moveSpeed;
	float damageMultiplier;//�_���[�W�{���A����Ɏ��@�̍U���͂������ă_���[�W���o��;
};

/**
�V���b�g�f�[�^�̂����ꔭ���ƂɈقȂ����;
*@param const	<shotPatternData*>	pData			�V���b�g�f�[�^�̋��^;
*@param			<coordinate>		position		���W;
*@param			<vector2>			positionFloat	���W��float��;
*@param			<vector2>			vec2			���̒e�̕����x�N�g��;
*@param			<float>				damage			�^����_���[�W;
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
