#pragma once
#include "Main.h"

constexpr auto CMng_ControlKeys = 7;

typedef struct KeyStat {
	int		KeyCode		{ -1 };
	bool	isHitKey	{ 0 };
	int		RegistID	{ 0 };
	int		StartTime	{ 0 };

	int		CM_count{ 0 };
	int		CM_wait1{ 0 };
	int		CM_wait2{ 0 };
}ButtonStat;

enum Regist_Keyboard {
	NEUTRAL,
	CMK_LEFT,
	CMK_RIGHT,
	CMK_UP,
	CMK_DOWN,
	CMK_DECIDE,
	CMK_CANCEL,
	CMK_INVENTORY,
	CMK_SUB_KEY,
};
enum Regist_GamePad {
	CMG_NEUTRAL,
	CMG_LEFT,
	CMG_RIGHT,
	CMG_UP,
	CMG_DOWN,
	CMG_DECIDE,
	CMG_CANCEL,
	CMG_INVENTORY,
	CMG_SUB_KEY,
};

bool HitKey		(int Keycode,		bool KeyLoop,		int KeyLoop_Start,		int KeyLoop_Speed);
bool HitButton	(int ButtonCode,	bool ButtonLoop,	int ButtonLoop_Start,	int ButtonLoop_Speed);