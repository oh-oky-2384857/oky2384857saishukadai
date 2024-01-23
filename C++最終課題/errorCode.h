#pragma once

enum class errorCode //エラーの種類;
{
	none,				//エラーなし;
	fileNotFound,		//ファイルが見つからない;
	handleRoadFail,		//ハンドル読み込み失敗;
	processingFailure,	//処理失敗;
	objectNotFound,		//オブジェクトが見つからない;
	others,				//その他;
};
enum class errorSource //エラー発生場所;
{
	none,				//エラーなし;
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