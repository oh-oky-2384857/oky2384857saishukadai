#pragma once
#include "entity.h"

//�O���錾;
class enemyManager;
struct enemyData;

//���ԃN���X;
class enemy : public entity {
protected:
	bool isEnemy;	//�����Ă��邩;
	float nowHp;	//����Hp;

	vector2 floatPos;
	//�֐��Ăяo���p;
	enemyManager* ptrEnemyManager;

	//��{�f�[�^;
	const enemyData* data;
	
	//�R���X�g���N�^;
	enemy(const enemyData* edata);
	//�f�t�H���g�̈ړ��A�v���C���[�ɋ߂Â�;
	virtual bool Move();
public:
	virtual bool Awake() { return true; };
	virtual bool Update() { return true; };
	virtual void Print() {};

	/**
	�������Ă��邩
	*@returns bool true:�ڐG,false:��ڐG;
	*/
	bool CheckHit(coordinate coord, int radius);

	/**
	�����Ă��邩 
	*@returns bool true:��,false:��;
	*/
	inline bool GetIsEnemy() { return isEnemy; };

	/**
	�_���[�W��^����
	*@returns bool true:��,false:��;
	*/
	virtual bool AddDamage(float damage);
};


class enemy001 : public enemy {
private:
public:
	/**
	�R���X�g���N�^
	*@param	<coordinate>	coord	���W;
	*@param <enemyManager*>	ptrEM	�֐��Ăяo���p;
	*@param <const enemyData*>	edata	��{�f�[�^;
	*/
	enemy001(coordinate coord, enemyManager* ptrEM,const enemyData* edata);
	~enemy001();

	bool Awake();
	bool Update();
	void Print();
};

class enemy002 : public enemy {
private:
public:
	enemy002(coordinate coord, enemyManager* ptrEM, const enemyData* edata);
	~enemy002();

	bool Awake();
	bool Update();
	void Print();
};