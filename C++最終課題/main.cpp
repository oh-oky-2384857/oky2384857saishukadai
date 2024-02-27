#include <DxLib.h>
#include <algorithm>
#include "gameManager.h"
#include "colorSample.h"
#include "stringHandle.h"

#include "errorCode.h"
#include "blueScreen.h"
#include "errorManager.h"

#include <crtdbg.h>

//デバッグ版の場合、メモリリーク場所を特定するマクロ;
#ifdef _DEBUG
#define	new	new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif

using namespace std;

const int REFRESH_RATE = 17;

const string ERROR_LOG_FILE_PATH = "./resource/errorResource/errorLog.txt";//エラーログのパス;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR IpCmdLine, int nCmdShow)
{
	//メモリリークを管理する関数;
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// ＤＸライブラリ初期化処理
	if (DxLib_Init() == -1)
	{
		return -1;        // エラーが起きたら直ちに終了
	}

	//windowModeに変更;
	ChangeWindowMode(true);
	//描画先画面を裏にする;
	SetDrawScreen(DX_SCREEN_BACK);

	//gameManager生成;
	gameManager* gm = new gameManager;

	//エラーメッセージ出力用;
	errorManager* em = new errorManager;
	
	//初期設定失敗で強制終了;
	if(!em->Awake()) {

		delete gm, em;
		DxLib_End();
		return -1;

	}

	//エラーログ可読性向上のため処理ブロック終了時,開始時にログを出す;
	em->AddErrorLog("errorManagerAwakeSuccess");
	em->AddErrorLog("gameManagerAwake");

	//起動時処理;
	try {
		gm->Awake();

	//自前のエラー発生時;
	}catch (errorData* d) {

		//エラーログに書く;
		em->AddErrorLog(d);
		
		//いったん削除;
		delete gm;
		
		//titleマネージャが原因ならブルースクリーンに直結;
		if (d->source == errorSource::titleManager) {

			sceneManager* newScene = new blueScreenManager(gm, d);

			//シーン指定コンストラクタを利用して直接ブルスクに;
			gm = new gameManager(newScene);

			//もう一度試す;
			try {
				gm->Awake();

			//ダメだったら
			}catch (errorData* d) {

				//メッセージを出力して終了;
				em->AddErrorLog("復帰失敗");

				delete gm, em;
				DxLib_End();
				return -1;
			}

			//メッセージを出力して続行;
			em->AddErrorLog("復帰完了");


		}else {
			//titleマネージャが原因でないなら終了;
			delete gm, em;
			DxLib_End();
			return -1;
		}

		return -1;

	//自作のエラー以外が発生時;
	}catch (exception e) {

		//エラーログに書く;
		em->AddErrorLog(e.what());

		delete gm, em;
		DxLib_End();

		return -1;

	//その他エラー;
	}catch (...) {
		//エラーログに書く;
		em->AddErrorLog("不明なエラー");

		delete gm, em;
		DxLib_End();

		return -1;
	}

	//エラーログ出力;
	em->AddErrorLog("gameManagerAwakeSuccess");

	// 下準備,色作ったり文字作ったり;
	colorSample::MakeColors();
	stringHandle::MakeHandles();

	int refreshTime;

	//エラーログ出力;
	em->AddErrorLog("gameRoop");

	//ゲームループ;
	try {

		//エラー発生または状態が終了になったら;
		while ((ProcessMessage() == 0) && (gm->GetGameStatus() != gameStatus::end)) {
			//画面リセット
			ClearDrawScreen();

			//リフレッシュタイムに現在時間を代入;
			refreshTime = GetNowCount();

			gm->Update();//更新処理;
			gm->Print();//表示処理;

			//裏画面の内容を表画面に反映;
			ScreenFlip();
			int timeDist = GetNowCount() - refreshTime;//処理の経過時間;
			//リフレッシュレートから経過時間を引いて処理間隔を一定に;
			WaitTimer((std::max)(REFRESH_RATE - timeDist, 0));
		}
	//自前のエラー発生時;
	}catch (errorData* d) {

		//エラーログに書く;
		em->AddErrorLog(d);

		//ブルスクにシーン偏移;
		sceneManager* newScene = new blueScreenManager(gm, d);

		gm->SetNewScene(newScene);
		//ブルスクを出すためのループ;
		while ((ProcessMessage() == 0) && (gm->GetGameStatus() != gameStatus::end)) {
			//画面リセット
			ClearDrawScreen();

			//リフレッシュタイムに現在時間を代入;
			refreshTime = GetNowCount();

			gm->Update();//更新処理;
			gm->Print();//表示処理;

			//裏画面の内容を表画面に反映;
			ScreenFlip();
			int timeDist = GetNowCount() - refreshTime;//処理の経過時間;
			//リフレッシュレートから経過時間を引いて処理間隔を一定に;
			WaitTimer((std::max)(REFRESH_RATE - timeDist, 0));
		}


	//自作のエラー以外が発生時;
	}catch (exception e) {

		//エラーログに書く;
		em->AddErrorLog(e.what());

		delete gm, em;
		DxLib_End();

		return -1;

	//その他エラー;
	}catch (...) {

		//エラーログに書く;
		em->AddErrorLog("不明なエラー");

		delete gm, em;
		DxLib_End();

		return -1;

	}


	//後始末;
	delete gm, em;

	DxLib_End();

	return 0;
}