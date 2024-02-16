#pragma once
#include <string>
#include <DxLib.h>


/**
�G�f�[�^�̂����A��̂��ƈقȂ����;
*@param <float>	 moveSpeed	�ړ����x;
*@param <flaot>	 hp			Hp;
*@param <flaot>	 atk		�U����;
*@param <string> handlePath	�摜�̃p�X;
*@param <int>	 handle		�摜�n���h��;
*@param <int>	 width		�摜�̏c��;
*@param <int>	 height			  ����;
*/
struct enemyData
{
public:
	float moveSpeed;		//�ړ����x;
	float hp;				//Hp;
	float atk;				//�U����;
	std::string* handlePath;//�摜�̃p�X;
	int handle;				//�摜�n���h��;
	int width;				//�摜�̏c��;
	int height;				//      ����;

public :
	/**
	�R���X�g���N�^
	*@param <float>		ms		�ړ����x;
	*@param <flaot>		hp		Hp;
	*@param <flaot>		atk		�U����;
	*@param <string*>	handleP	�摜�̃p�X;
	*/
	bool Load(float ms , float hp,float atk,std::string* handleP) {
		if (ms < 0 || hp <= 0 || atk < 0||handleP->size() == 0) {//�����ȃf�[�^����������;
			return false;
		}
		moveSpeed = ms;
		enemyData::hp = hp;
		enemyData::atk = atk;
		handlePath = handleP;

		return true;
	}
	//�摜�ǂݍ���
	bool LoadImg() {
		handle = LoadGraph(handlePath->c_str());
		if (handle == -1) {
			return false;
		}
		GetGraphSize(handle, &width, &height);
		return true;
	}
	//�f�X�g���N�^
	~enemyData(){
		if (handle != -1) {
			DeleteGraph(handle);
			delete handlePath;
		}
	}
};