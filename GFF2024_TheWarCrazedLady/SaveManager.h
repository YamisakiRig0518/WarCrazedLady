//セーブマネージャー
#pragma once
#include "Main.h"

//セーブデータの最大スロット数
constexpr auto SAVEDATA_INDEX = 16;

//セーブデータの基本的な情報となる構造体
struct MetaData {
	int PlayTime_Second = 0;		//プレイ時間
	int PlayingMode		= 0;		//プレイ中のモード
	int SavedChapter	= 0;		//セーブした場面
	int SavedObjective	= 0;		//セーブした時点で遂行中のクエスト
	int SavedPlace		= 0;		//セーブした場所
};

//キャラデータなど

//セーブデータの本体となる構造体
struct PlayData {
	//準備中
};

bool LoadParameter();				//セーブデータの読み込みを行う
void GetMetaData(MetaData* Dest);	//メタデータを取得する
bool LoadMetaParameter();			//メタデータを読み込む
void SaveMetaParameter();			//メタデータの書き込み
bool SaveParameter();				//セーブデータの書き込みを行う