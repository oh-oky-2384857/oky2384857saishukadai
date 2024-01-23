#include "blueScreen.h"
#include "gameCommon.h"
#include "colorSample.h"
#include "errorCode.h"
#include <DxLib.h>
#include <fstream>

using namespace std;

const string ERROR_MASSAGE_CODE_PATH ={"./resource/errorResource/errorCode.txt"};
const string ERROR_MASSAGE_SOURCE_PATH = { "./resource/errorResource/errorSource.txt" };


blueScreenManager::blueScreenManager(gameManager* ptrGameManager, errorData* data) {
	colorS = nullptr;

	ifstream reading_file;
	reading_file.open(ERROR_MASSAGE_CODE_PATH, ios::in);
	if (!reading_file) {
		exit(1);
	}

	string buffer;
	int cnt = 0;

	while (getline(reading_file, buffer))
	{
		cnt++;
		if ((int)data->code == cnt) {
			*errorCodeMassage = buffer;
			break;
		}else if (reading_file.eof()) {
			*errorCodeMassage = "error massage error";
		}
	}

	reading_file.close();
	reading_file.open(ERROR_MASSAGE_SOURCE_PATH, ios::in);
	if (!reading_file) {
		exit(1);
	}
	cnt = 0;
	while (getline(reading_file, buffer))
	{
		cnt++;
		if ((int)data->source == cnt) {
			*errorSourceMassage = buffer;
			break;
		}
		else if (reading_file.eof()) {
			*errorSourceMassage = "error massage error";
		}
	}
}
blueScreenManager::~blueScreenManager() {
	delete errorCodeMassage;;
	delete errorSourceMassage;
}
bool blueScreenManager::Awake(){
	return true;
}
bool blueScreenManager::Update() {

	return true;
}
void blueScreenManager::Print() {
	DrawBox(0,0,SCREEN_WIDTH,SCREEN_HEIGHT,colorS->white,true);
	DrawFormatString(0, 0, colorS->blue,"エラー要因 %s", errorCodeMassage->c_str());
	DrawFormatString(0, 0, colorS->blue,"エラー発生場所 %s", errorSourceMassage->c_str());
}