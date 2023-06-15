#pragma once
#include "Main.h"

class TitleScene : public SceneClass{
public:
	TitleScene();
	~TitleScene() {};

	void Initialize();	//タイトルシーンの初期化処理
	void Main();		//タイトルシーンの主要処理
	void Reset();		//タイトルシーンの終了処理
};