#pragma once

//リソースの種類
enum Asset_Category {
	IMAGE,								//イメージ
	BGM,								//バックグラウンドミュージック
	SE,									//サウンドエフェクト
};

//アセット管理用構造体
struct AssetData {
	const char* AliasName;				//エイリアス名
	const int	HandleID;				//ハンドル
	const int	Category;				//アセットの種別(Asset_Category列挙参照)
	const int	UseScene;				//アセットが使われる場面(-1の場合はシステム全体で利用している扱いになる)
};

//フォントアセット管理用
struct FontAsset {
	const char* AliasName;				//エイリアス名
	const int	HandleID;				//ハンドル
	const int	FontSize;				//フォントサイズ
	const int	UseScene;				//アセットが使われる場面(-1の場合はシステム全体で利用している扱いになる)
};
bool	LoadAsset			(const char* FilePath, int UseScene);
int		GetAsset			(const char* AliasName, int Category);
void	DeleteAsset_Scene	(int TargetScene);

bool	StringCheck			(const char* targetA, const char* targetB);
