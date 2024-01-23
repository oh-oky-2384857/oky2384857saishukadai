#pragma once

enum class errorCode //エラーの種類;
{
	none,				//エラーなし;
	fileNotFound,		//ファイルが見つからない;
	handleRoadFail,		//ハンドル読み込み失敗;
	processingFailure,	//処理失敗;
	others,				//その他;
};
enum class errorSource //エラー発生場所;
{
	none,				//エラーなし;
	gameManager,
	gameMainManager,
	titleManager
};

struct errorData {
	errorCode code;
	errorSource source;
};