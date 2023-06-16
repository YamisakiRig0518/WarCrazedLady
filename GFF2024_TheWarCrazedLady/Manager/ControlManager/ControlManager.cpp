#include "ControlManager.h"

KeyStat KeyStatus[CMng_ControlKeys] = {
	{KEY_INPUT_LEFT	, 0 , CMK_LEFT		},
	{KEY_INPUT_RIGHT, 0 , CMK_RIGHT		},
	{KEY_INPUT_UP	, 0 , CMK_UP		},
	{KEY_INPUT_DOWN	, 0 , CMK_DOWN		},

	{KEY_INPUT_F	, 0 , CMK_DECIDE	},
	{KEY_INPUT_D    , 0 , CMK_CANCEL	},
	{KEY_INPUT_E	, 0 , CMK_INVENTORY	}
};

ButtonStat BtnStatus[CMng_ControlKeys] = {
	{PAD_INPUT_LEFT		, 0 , CMG_LEFT		},
	{PAD_INPUT_RIGHT	, 0 , CMG_RIGHT		},
	{PAD_INPUT_UP		, 0 , CMG_UP		},
	{PAD_INPUT_DOWN		, 0 , CMG_DOWN		},

	{PAD_INPUT_2		, 0 , CMG_DECIDE	},
	{PAD_INPUT_1		, 0 , CMG_CANCEL	},
	{PAD_INPUT_3		, 0 , CMG_INVENTORY	}
};

//キーボード入力判定用
int cm_count	= 0;
int cm_wait1	= 0;
int cm_wait2	= 0;

//ゲームパット入力判定用
int cm_Gcount = 0;
int cm_Gwait1 = 0;
int cm_Gwait2 = 0;

//Hitkey関数：Dxlib標準のCheckHitKeyにキーループ機能を入れた関数
//【第1引数】	Keycode(int)		Regist列挙(CMK_に続く列挙名を入力）
//【第2引数】	KeyLoop(bool)		キーを押し続けた時、連続で入力するかどうか
//【第3引数】	KeyLoop_Start(int)	キーの連続入力を何秒後に開始するか
//【第4引数】	KeyLoop_Speed(int)	キーの連続入力の間隔(1000 = 1秒)
bool HitKey(int Keycode, bool ButtonLoop, int ButtonLoop_Start, int ButtonLoop_Speed) {

	for (int i = 0; i < CMng_ControlKeys; i++) {
		//引数で指定されたキーコードと登録されたキーコードが合致しているか
		if (Keycode == KeyStatus[i].RegistID) {
			//入力されているか判定
			if (CheckHitKey(KeyStatus[i].KeyCode)) {
				//キーが押された場合、１度だけ入力するモードの場合
				if (!ButtonLoop && !KeyStatus[i].isHitKey) {
					KeyStatus[i].isHitKey = true;
					return true;
				//キーが押された場合、押し続けている間入力するモードの場合
				}else if(ButtonLoop){
					if (!KeyStatus[i].isHitKey) {
						KeyStatus[i].StartTime = GetNowCount();
						KeyStatus[i].isHitKey = true;
					}else {
						//キーの連続入力モードの場合
						//キーが押されてから指定された時間が経過した場合は連続入力開始
						if (KeyStatus[i].CM_count > ButtonLoop_Start && KeyStatus[i].isHitKey) {
							//キーを連続入力する間隔
							//指定された時間が経過した場合はtrueを返す
							KeyStatus[i].CM_wait2 = GetNowCount() - KeyStatus[i].CM_wait1;
							if (KeyStatus[i].CM_wait2 > ButtonLoop_Speed) {
								KeyStatus[i].CM_wait1 = GetNowCount();
								return true;
							}else {
								return false;
							}
						}else {
							//キーが押されてからの時間を計測
							KeyStatus[i].CM_count = GetNowCount() - KeyStatus[i].StartTime;
							KeyStatus[i].CM_wait1 = GetNowCount();
							return false;
						}
					}
				//「１度だけ入力するモード」で入力フラグが既に立っている場合
				}else if(!ButtonLoop && KeyStatus[i].isHitKey) {
					return false;
				}
			//キーが押されていない場合は入力フラグを下ろす
			}else {
				KeyStatus[i].isHitKey	= false;
				KeyStatus[i].StartTime	= 0;
				KeyStatus[i].CM_count = 0;
				KeyStatus[i].CM_wait1 = 0;
				KeyStatus[i].CM_wait2 = 0;
				return false;
			}
		}
	}
};

//HitButton関数：HitKey関数のゲームパッド版
//【第1引数】	ButtonCode(int)			Regist列挙(CMG_に続く列挙名を入力）
//【第2引数】	ButtonLoop(bool)		ボタンを押し続けた時、連続で入力するかどうか
//【第3引数】	ButtonLoop_Start(int)	ボタンの連続入力を何秒後に開始するか
//【第4引数】	ButtonLoop_Speed(int)	ボタンの連続入力の間隔(1000 = 1秒)
bool HitButton(int ButtonCode, bool ButtonLoop, int ButtonLoop_Start, int ButtonLoop_Speed) {

	for (int i = 0; i < CMng_ControlKeys; i++) {
		//引数で指定されたキーコードと登録されたキーコードが合致しているか
		if (ButtonCode == BtnStatus[i].RegistID) {
			//入力されているか判定
			if ((GetJoypadInputState(DX_INPUT_PAD1) & BtnStatus[i].KeyCode)) {
				//キーが押された場合、１度だけ入力するモードの場合
				if (!ButtonLoop && !BtnStatus[i].isHitKey) {
					BtnStatus[i].isHitKey = true;
					return true;
					//キーが押された場合、押し続けている間入力するモードの場合
				}else if (ButtonLoop) {
					if (!BtnStatus[i].isHitKey) {
						BtnStatus[i].StartTime = GetNowCount();
						BtnStatus[i].isHitKey = true;
					}else {
						//キーの連続入力モードの場合
						//キーが押されてから指定された時間が経過した場合は連続入力開始
						if (BtnStatus[i].CM_count > ButtonLoop_Start && BtnStatus[i].isHitKey) {
							//キーを連続入力する間隔
							//指定された時間が経過した場合はtrueを返す
							BtnStatus[i].CM_wait2 = GetNowCount() - BtnStatus[i].CM_wait1;
							if (BtnStatus[i].CM_wait2 > ButtonLoop_Speed) {
								BtnStatus[i].CM_wait1 = GetNowCount();
								return true;
							}else {
								return false;
							}
						}else {
							//キーが押されてからの時間を計測
							BtnStatus[i].CM_count = GetNowCount() - BtnStatus[i].StartTime;
							BtnStatus[i].CM_wait1 = GetNowCount();
							return false;
						}
					}
					//「１度だけ入力するモード」で入力フラグが既に立っている場合
				}else if (!ButtonLoop && BtnStatus[i].isHitKey) {
					return false;
				}
				//キーが押されていない場合は入力フラグを下ろす
			}else {
				BtnStatus[i].isHitKey = false;
				BtnStatus[i].StartTime = 0;
				BtnStatus[i].CM_count = 0;
				BtnStatus[i].CM_wait1 = 0;
				BtnStatus[i].CM_wait2 = 0;
				return false;
			}
		}
	}
};