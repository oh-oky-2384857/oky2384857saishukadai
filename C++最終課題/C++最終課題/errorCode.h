#pragma once

enum class errorCode //�G���[�̎��;
{
	none,				//�G���[�Ȃ�;
	fileNotFound,		//�t�@�C����������Ȃ�;
	handleRoadFail,		//�n���h���ǂݍ��ݎ��s;
	processingFailure,	//�������s;
	others,				//���̑�;
};
enum class errorSource //�G���[�����ꏊ;
{
	none,				//�G���[�Ȃ�;
	gameManager,
	gameMainManager,
	titleManager
};

struct errorData {
	errorCode code;
	errorSource source;
};