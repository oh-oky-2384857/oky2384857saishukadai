#pragma once
#include <string>

enum class errorCode //�G���[�̎��;
{
	none,				//�G���[�Ȃ�;
	fileNotFound,		//�t�@�C����������Ȃ�;
	handleRoadFail,		//�n���h���ǂݍ��ݎ��s;
	processingFailure,	//�������s;
	objectNotFound,		//�I�u�W�F�N�g��������Ȃ�;
	improperData,		//�s���ȃf�[�^;
	others				//���̑�;

};



enum class errorSource //�G���[�����ꏊ;
{
	none,				//�G���[�Ȃ�;
	errorManager,
	gameManager,
	cursorManager,
	pauseManager,
	titleManager,
	gameMainManager,
	mapManager,
	playerManager,
	enemyManager,
	playerShotManager,
	weaponManager
};


struct errorData {
public:
	errorCode code;
	errorSource source;
	std::string* note;
	/**
	*@param {errorCode}		code	�ǂ�ȃG���[��;
	*@param {errorSource}	source	�ǂ��Ŕ���������;
	*@param {string*}		note	����;
	*/
	errorData(errorCode code,errorSource source,std::string* note) {
		this->code = code;
		this->source = source;
		this->note = note;
	}

	errorData(errorCode code, errorSource source,const char* note) {
		this->code = code;
		this->source = source;
		this->note = new std::string(note);
	}
};

