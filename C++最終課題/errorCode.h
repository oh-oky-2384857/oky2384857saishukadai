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
	others,				//その他;
};
enum class errorSource //エラー発生場所;
{
	none,				//エラーなし;
	gameManager,
	titleManager,
	gameMainManager,
	mapManager,
	playerManager,
	enemyManager
};

struct errorData {
public:
	errorData(errorCode code,errorSource source,std::string* note) {
		this->code = code;
		this->source = source;
		this->note = note;
	}
	errorCode code;
	errorSource source;
	std::string* note;
};