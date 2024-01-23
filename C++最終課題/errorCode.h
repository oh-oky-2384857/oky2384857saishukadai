#pragma once

enum class errorCode //�G���[�̎��;
{
	none,				//�G���[�Ȃ�;
	fileNotFound,		//�t�@�C����������Ȃ�;
	handleRoadFail,		//�n���h���ǂݍ��ݎ��s;
	processingFailure,	//�������s;
	objectNotFound,		//�I�u�W�F�N�g��������Ȃ�;
	others,				//���̑�;
};
enum class errorSource //�G���[�����ꏊ;
{
	none,				//�G���[�Ȃ�;
	gameManager,
	titleManager,
	gameMainManager,
	mapManager,
	playerManager
};

struct errorData {
public:
	errorData(errorCode code,errorSource source) {
		this->code = code;
		this->source = source;
	}
	errorCode code;
	errorSource source;
};