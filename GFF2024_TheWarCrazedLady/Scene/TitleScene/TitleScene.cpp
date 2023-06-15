#include "TitleScene.h"

//コンストラクタ
TitleScene::TitleScene() {
	SceneID = Scene_Title;
}

//初期化処理
void TitleScene::Initialize() {

};

//主要処理
void TitleScene::Main() {
	DrawString(0, 0, "This is Title Scene", GetColor(255, 255, 255));
};

//終了処理
void TitleScene::Reset() {

};