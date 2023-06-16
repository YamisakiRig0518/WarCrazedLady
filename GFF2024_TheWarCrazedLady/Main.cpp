#include "Main.h"

//シーン管理用
vector<SceneClass*> Scenes; int ActiveScene{ Start_Scene };

int _stdcall wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE, _In_ LPWSTR lpCmdline, _In_ int nShowCmd) {
	//ウィンドウモードに設定
	ChangeWindowMode(TRUE);

	//画面サイズの設定
	SetGraphMode(Window_Width, Window_Height, Window_Color, Window_FPS);

	//二重起動はしないように設定
	SetDoubleStartValidFlag(FALSE);

	//ウィンドウが非アクティブの時も処理は続行する
	SetAlwaysRunFlag(TRUE);

	//ログ出力を無効に
	SetOutApplicationLogValidFlag(false);

	//ウィンドウタイトル
	SetWindowText("");

	//アイコン変更(ここで行う)
	//SetWindowIconID(104);

	//垂直同期をとる(フレームレート制限も掛かる)
	SetWaitVSyncFlag(TRUE);
	
	//ライブラリの初期化（エラーが発生した場合はただちにアプリ終了）
	if (DxLib_Init() != 0) return -1;

	//描画先をバッファに変更
	SetDrawScreen(DX_SCREEN_BACK);

	//使うアセットを一括ロード
	//ここに自作関数を追加

	//シーン管理の前準備
	Scenes.emplace_back(new ShowLogo());
	Scenes.emplace_back(new TitleScene());

	Scenes[ActiveScene]->Initialize();
	 
	//メインループ
	while (ProcessMessage() == 0) {
		//ブレンドモードや描画輝度の設定を一応戻しておく
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		SetDrawBright(255, 255, 255);

		//バッファの描画内容を削除
		ClearDrawScreen();

		//シーンの主要処理
		Scenes[ActiveScene]->Main();
		
		//描画内容を表示ウィンドウに描画
		ScreenFlip();
	}

	//ここでリソースの解放を行う

	//DXライブラリの後始末
	DxLib_End();

	//アプリケーションの終了
	return 1;
};

//指定IDと該当するオブジェクトデータの取得
ObjectClass* GetObj(list<unique_ptr<ObjectClass>>& base, int ID) {
	for (auto i = base.begin(); i != base.end(); i++) {
		if ((*i)->ObjectID == ID) {
			return (*i).get();
		}

		return nullptr;
	}
};

//シーン切り替え（該当するシーンが無ければ切り替わらない）
void SetScene(int SceneID) {
	bool isComplete = false;
	
	for (auto i = Scenes.begin(); i != Scenes.end(); i++) {
		if (SceneID == (*i)->SceneID) {
			//シーンの終了処理
			Scenes[ActiveScene]->Reset();

			//シーンで使ったアセットのアンロード
			DeleteAsset_Scene(ActiveScene);

			//移動先のシーンの初期化処理
			(*i)->Initialize();

			//実行中シーンのIDを変更してシーン変更完了
			ActiveScene = (*i)->SceneID;

			break;
		}
	}
};

