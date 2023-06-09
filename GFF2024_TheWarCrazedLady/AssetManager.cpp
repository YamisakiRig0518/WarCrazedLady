#include "Main.h"
#include "AssetManager.h"

constexpr int category_MAX = 3;

vector<AssetData*> Assets;	//アセットを管理する可変配列
const char* Categories[category_MAX] = { ".png",".mp3",".wav" };

bool LoadAsset(const char* FilePath, int UseScene) {
	string	FilePath_STR	= FilePath;
	int		File_Category	= 0;

	for (int i = 0; i < category_MAX; i++) {
		if (FilePath_STR.find(Categories)
	}
};