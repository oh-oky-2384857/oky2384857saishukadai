#include <DxLib.h>
#include <fstream>
#include "blueScreen.h"
#include "colorSample.h"
#include "errorCode.h"

using namespace std;

const string ERROR_MASSAGE_CODE_PATH ={"./resource/errorResource/errorCode.txt"};
const string ERROR_MASSAGE_SOURCE_PATH = { "./resource/errorResource/errorSource.txt" };


blueScreenManager::blueScreenManager(gameManager* ptrGameManager, errorData* data) {

	ifstream reading_file;
	reading_file.open(ERROR_MASSAGE_CODE_PATH, ios::in);
	if (!reading_file) {
		exit(1);
	}
	errorCodeMassage = new string;
	
	string buffer;
	int cnt = 0;

	while (getline(reading_file, buffer))
	{
		cnt++;
		if ((int)data->code == cnt) {
			*errorCodeMassage = buffer.c_str();
			break;
		}else if (reading_file.eof()) {
			*errorCodeMassage = "error massage error";
			break;
		}
		buffer.clear();
	}


	reading_file.close();
	reading_file.open(ERROR_MASSAGE_SOURCE_PATH, ios::in);
	if (!reading_file) {
		delete errorCodeMassage;
		exit(1);
	}
	errorSourceMassage = new string;

	cnt = 0;
	buffer.clear();
	while (getline(reading_file, buffer))
	{
		cnt++;
		if ((int)data->source == cnt) {
			*errorSourceMassage = buffer.c_str();
			break;
		}
		else if (reading_file.eof()) {
			*errorSourceMassage = "error massage error";
		}
		buffer.clear();
	}
}
blueScreenManager::blueScreenManager(gameManager* ptrGameManager, errorData* data, std::string* note) {
	blueScreenManager::blueScreenManager(ptrGameManager, data);
	this->note = note;
}
blueScreenManager::~blueScreenManager() {
	delete errorCodeMassage;;
	delete errorSourceMassage;
	delete note;
}
bool blueScreenManager::Awake(){
	return true;
}
bool blueScreenManager::Update() {

	return true;
}
void blueScreenManager::Print() {
	colorSample* colorS = nullptr;
	DrawBox(0,0,SCREEN_WIDTH,SCREEN_HEIGHT,colorS->blue,true);
	DrawFormatString(0, 0, colorS->white,"エラー要因 %s", errorCodeMassage->c_str());
	DrawFormatString(0, 20, colorS->white,"エラー発生場所 %s", errorSourceMassage->c_str());
	if (!note->empty()) {
		DrawFormatString(0, 40, colorS->white, "エラー発生場所 %s", note->c_str());
	}
}