#pragma once
#include <list>
#include <memory>

using namespace std;

//実数型２次元座標の構造体
struct Vector2 {
	float x{ 0.0f };
	float y{ 0.0f };
};
//シーン用の基底クラス
class SceneClass{
public :
	SceneClass()	{};					//コンストラクタ
	~SceneClass()	{};					//デストラクタ

	virtual void Initialize()	= 0;	//シーンの初期化処理
	virtual void Main()			= 0;	//シーンの主要処理

	int SceneID{ 0 };					//シーンID
};

//オブジェクト用の基底クラス
class ObjectClass {
public :
	ObjectClass() {};					//コンストラクタ
	~ObjectClass() {};					//デストラクタ

	int		ObjectID{ 0 };				//オブジェクトID
	Vector2 pos{ 0.0f, 0.0f };			//座標
	Vector2 vec{ 0.0f, 0.0f };			//ベクトル

	virtual void Initialize() = 0;									//オブジェクトの初期化
	virtual int Action(list<unique_ptr<ObjectClass>>& base) = 0;	//オブジェクトの主要処理
};

