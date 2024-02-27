#include "errorManager.h"

#include <string.h>
const std::string ERROR_LOG_FILE_PATH = "./resource/errorResource/errorLog.txt";//�G���[���O�̃p�X;

using namespace std;

errorManager::errorManager() {
	SetManagerName("errorManager");
}
errorManager::~errorManager() {
	if (errorLogFile.is_open()) {
		errorLogFile.close();
	}
}
bool errorManager::Awake() {

	errorLogFile.open(ERROR_LOG_FILE_PATH.c_str());

	if (!errorLogFile) {
		errorData* data = new errorData{errorCode::fileNotFound,errorSource::errorManager,(string*) nullptr};
		throw data;
	}
	return true;
}

void errorManager::AddErrorLog(const char* newlog) {
	//�t�@�C��������ɊJ���Ă���Ȃ�;
	if (errorLogFile) {

		errorLogFile << newlog << endl;

	}
}

void errorManager::AddErrorLog(const errorData* newlog) {
	//�t�@�C��������ɊJ���Ă���Ȃ�;
	if (errorLogFile) {

		errorLogFile << newlog << endl;

	}
}
