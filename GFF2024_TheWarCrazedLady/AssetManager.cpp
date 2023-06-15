#include "Main.h"
#include "AssetManager.h"

constexpr int category_MAX = 3;

vector<AssetData*> Assets;	//アセットを管理する可変配列
string Categories[category_MAX] = { ".png",".mp3",".wav" };

//LoadAsset関数：画像・BGM・効果音を読み込む関数
//シーン毎にアセットの管理を行う為に自作
//拡張子で判別してそれぞれのカテゴリに分類される
bool LoadAsset(const char* FilePath, int UseScene) {
	string	FilePath_STR	= FilePath;
	string	AliasName;
	int		File_Category	= -1;
	int		File_Handle		= 0;

	//ファイル名を取り出す為に最後尾の「/」と「.」の位置を取得
	//そこからファイル名の位置を割り出して「ファイル名」の長さを求めている
	int LastPeriod = FilePath_STR.find(".");
	int LastSlash = FilePath_STR.find("/");
	int FileLength = LastPeriod - LastSlash;

	//カテゴリ判別
	for (int i = 0; i < category_MAX; i++) {
		if (FilePath_STR.find(Categories[i])) {
			File_Category = i;
			break;
		}
	}
	//対応する拡張子では無かった場合はfalseを返す
	if (File_Category == -1)return false;

	//ファイル読み込み
	switch (File_Category) {
	case IMAGE:	//画像
		File_Handle = LoadGraph(FilePath);
		break;
	case BGM:	//音楽
		File_Handle = LoadSoundMem(FilePath);
		break;
	case SE:	//効果音
		File_Handle = LoadSoundMem(FilePath);
		break;
	default:	//対応しない拡張子の場合
		return false;	//対応していないファイルが読み込まれた場合はfalseを返す
		break;
	}
	if (File_Handle == -1)return false;	//ファイルが存在しない場合はfalseを返す

	//ファイル名をエイリアスとして登録
	AliasName = FilePath_STR.substr(LastSlash + 1, FileLength - 1);
	
	//string型からchar型配列に変換
	char* CharArray = new char[AliasName.size() + 1];
	memcpy(CharArray, AliasName.c_str(), AliasName.size() + 1);

	//登録を行う
	Assets.emplace_back(new AssetData{ CharArray, File_Handle, File_Category, UseScene });

	//正常に処理が完了したのでtrueを返す
	return true;
};

//GetAsset関数：LoadAssetで読み込んだアセットのハンドルを返す
//見つからなかった場合はfalseを返す
bool GetAsset(const char* AliasName, int Category) {
	return false;
}

//StringCheck関数：文字が一致しているか判別する
//(GetAsset関数等で仕様)
bool StringCheck(const char* targetA, const char* targetB) {
	string TargetA = targetA;
	string TargetB = targetB;

	int charsize	= 0;
	int seekA		= 0;
	int seekB		= 0;
	while (seekA < TargetA.size()) {
		string compareA, compareB;

		if (IsDBCSLeadByte(TargetA[seekA]) == 0) {
			charsize = 1;
			seekA++;
		}else {
			charsize = 2;
			seekA += 2;
		}
		compareA = TargetA.substr(seekA - charsize, charsize);

		if (seekB >= TargetB.size())return false;

		if (IsDBCSLeadByte(TargetB[seekB]) == 0) {
			charsize = 1;
			seekB++;
		}
		else {
			charsize = 2;
			seekB += 2;
		}

		compareB = TargetB.substr(seekB - charsize, charsize);

		if (compareA.compare(compareB) != 0)return false;
	}



	return true;
};