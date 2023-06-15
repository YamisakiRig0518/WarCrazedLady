//Main.h

#pragma once

#include "DxLib.h"

#include <list>
#include <memory>

#include <string>
#include <vector>

#include "TotalManager.h"
#include "SaveManager.h"
#include "AssetManager.h"

#include "Scene/TitleScene/TitleScene.h"

//名前空間の宣言
using namespace std;

//画面関連
constexpr auto Window_Width		= 1280;	//画面の横幅
constexpr auto Window_Height	= 720;	//画面の縦幅
constexpr auto Window_Color		= 32;	//色深度
constexpr auto Window_FPS		= 60;	//FPS設定

//指定したIDと該当するオブジェクトデータの取得
ObjectClass* GetObj(list<unique_ptr<ObjectClass>>&, int ID);