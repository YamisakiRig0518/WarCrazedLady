#include "SaveManager.h"

MetaData MetaParam[SAVEDATA_INDEX];
int ReadIndexes = 0;

bool LoadParameter() { return false; };	//セーブデータの読み込みを行う
bool SaveParameter() { return false; };	//セーブデータの書き込みを行う

bool LoadMetaParameter() {
	FILE* file;

	//メタファイルを読み込む
	fopen_s(&file, "MetaParameter.txt", "r+");

	//ファイル自体がない場合はfalseを返す
	if (file == NULL)return false;

	//メタファイルの内容を読み込む
	int reading_cur = 0;	//配列はゼロから
	ReadIndexes = 0;		//読み込みカウントリセット
	while (fscanf_s(file, "%d, %d, %d, %d, %d\n",
		&MetaParam[reading_cur].PlayTime_Second,	//総プレイ時間
		&MetaParam[reading_cur].PlayingMode,		//プレイモード（難易度）
		&MetaParam[reading_cur].SavedChapter,		//セーブした時点でのチャプター
		&MetaParam[reading_cur].SavedObjective,		//セーブした時点で遂行中のクエスト
		&MetaParam[reading_cur].SavedPlace)			//セーブした地点
		
		//終点文字に到達しておらず
		!= EOF && ReadIndexes < SAVEDATA_INDEX) {

		reading_cur++;	//次の配列にチェンジ
		ReadIndexes++;	//読み込めたカウントを増やす
	};

	//ファイルを閉じる
	fclose(file);

	//ファイルを読み込めた場合はtrueを返す
	return true;
};

void SaveMetaParameter() {
	FILE* file;

	//メタファイルを読み込み
	fopen_s(&file, "MetaParameter.txt", "w+");

	//書き込む内容の準備
	for (int cnt = 0; cnt < SAVEDATA_INDEX; cnt++) {
		char WriteData[128];

		sprintf_s(WriteData, "%d, %d, %d, %d, %d\n",
			MetaParam[cnt].PlayTime_Second,	//総プレイ時間
			MetaParam[cnt].PlayingMode,		//プレイモード（難易度）
			MetaParam[cnt].SavedChapter,	//セーブした時点でのチャプター
			MetaParam[cnt].SavedObjective,	//セーブした時点で遂行中のクエスト
			MetaParam[cnt].SavedPlace);		//セーブした地点
	}

	//ファイルを閉じる
	fclose(file);
};


void GetMetaData(MetaData* Dest) {
	memcpy_s(Dest, sizeof(MetaParam), MetaParam, sizeof(MetaParam));
};