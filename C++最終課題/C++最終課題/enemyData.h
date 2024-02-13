#pragma once
#include <string>
#include <DxLib.h>

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
	bool Load(float ms , float hp,std::string* handleP) {
		if (ms < 0 || hp <= 0 || handleP->empty()) {//�����ȃf�[�^����������;
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