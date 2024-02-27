#pragma once
#include <string>

enum class errorCode //エラーの種類;
{
	none,				//エラーなし;
	fileNotFound,		//ファイルが見つからない;
	handleRoadFail,		//ハンドル読み込み失敗;
	processingFailure,	//処理失敗;
	objectNotFound,		//オブジェクトが見つからない;
	improperData,		//不正なデータ;
	others				//その他;

};



enum class errorSource //エラー発生場所;
{
	none,				//エラーなし;
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
	*@param {errorCode}		code	どんなエラーか;
	*@param {errorSource}	source	どこで発生したか;
	*@param {string*}		note	メモ;
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

