#pragma once
#include "Scene/SplashLogo/Section_ShowLogo.h"

ShowLogo::ShowLogo() {
	SceneID = Scene_Logo;
};

void ShowLogo::Initialize() {
	SequenceRandomize(); //ÉçÉSï\é¶èáÇÉâÉìÉ_ÉÄÇ…åàíË
	
	SeqStart = GetNowCount();
	LoadAsset("Scene/SplashLogo/image/LogoA.png", SceneID);
	LoadAsset("Scene/SplashLogo/image/LogoB.png", SceneID);

	drawbufferA = MakeScreen(1920,366, TRUE);

	BarLength[0] = Logodata[11][2];
	BarLength[1] = Logodata[12][3];
	BarLength[2] = Logodata[13][2];

	AllAlpha_int = 255;
};

void ShowLogo::Main() {
	SetDrawScreen(drawbufferA);
	/*ÉçÉSï∂éöï`âÊ-----------------------------------------------*/
	if (SeqTime > interval && Sequence < (LogoLength - 3)) {
		LogoPhase[Logo_Sequence[Sequence]] = 1;
		Sequence++;
		SeqStart = GetNowCount();
	}
	SeqTime = GetNowCount() - SeqStart;
	
	float Atotals = 0;
	for (int i = 0; i < LogoLength - 3; i++) {
		if (LogoPhase[i] == 1) {
			if (Logo_Alpha[i] < 255.0f) {
				Logo_Alpha[i] += fadespeed;
			}
			else if (Logo_Alpha[i] >= 255.0f) {
				//Logo_Alpha[i] = 255;
				LogoPhase[i] = 2;
			}
		}
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,Logo_Alpha[i]);
		DrawRectGraph(60 + Logodata[i][0], Logodata[i][1], //Dest
			Logodata[i][0], Logodata[i][1],
			Logodata[i][2], Logodata[i][3],
			GetAsset("LogoA",IMAGE), TRUE, FALSE, FALSE);

		Atotals += Logo_Alpha[i];
	}
	
	
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	
	/*-ÉçÉSÉoÅ[ï`âÊ-*/
	for (int i = 0; i < 3; i++) {
		if (BarLength[i] > 0 && ease[i] > 0) {
			BarLength[i] -= ease[i];
			ease[i]--;
		}
	}
	
	//-------------------------------------------------------------

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND,255);
	
	DrawRectGraph(BarLength[0]+60 + Logodata[11][0], Logodata[11][1],
		(Logodata[11][0]+ BarLength[0]), Logodata[11][1],
		Logodata[11][2], Logodata[11][3],
		GetAsset("LogoB",IMAGE), TRUE, FALSE, FALSE);
	
	DrawRectGraph(60 + Logodata[12][0], Logodata[12][1] + BarLength[1],
		Logodata[12][0], Logodata[12][1],
		Logodata[12][2], Logodata[12][3]-BarLength[1],
		GetAsset("LogoB",IMAGE), TRUE, FALSE, FALSE);
	
	DrawRectGraph(60 + Logodata[13][0], Logodata[13][1],
		Logodata[13][0], Logodata[13][1],
		Logodata[13][2]-BarLength[2], Logodata[13][3],
		GetAsset("LogoB", IMAGE), TRUE, FALSE, FALSE);

	if (phase == 0 && Sequence >= 11 && Atotals >= 2805) {
		msCount = GetNowCount();
		phase = 1;
	}else if (phase == 1) {
		if ((GetNowCount() - msCount) > 3000) {
			phase = 2;
		}
	}else if (phase == 2) {
		if (AllAlpha_int > 0) {
			AllAlpha_int -= 5;
		}else {
			phase = 3;
			SetScene(Scene_Title);
		}
	}

	/*ï`âÊ-------------------------------------------------------*/ 
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, AllAlpha_int);
	
	SetDrawScreen(DX_SCREEN_BACK);
	DrawFillBox(0, 0, Window_Width, Window_Height, GetColor(255, 255, 255));
	DrawExtendGraph(400, 312, 880, 404, drawbufferA, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, AllAlpha_int);
	//DrawStringCenter(419,"P R E S E N T S",0,0,0);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
};

void ShowLogo::Reset() {
	for (int i = 0; i < LogoLength; i++) {
		Logo_Alpha[i] = 0.0f;
		LogoPhase[i] = 0;
		Logo_Sequence[i] = 0;
	}

	for (int i = 0; i < 3; i++) {
		BarLength[i] = 0;
	}

	ease[0] = 48;
	ease[1] = 24;
	ease[2] = 56;

	Sequence = 0;
	SeqStart = 0;
	SeqTime  = 0;
	msCount = 0;
	phase = 0;


	SetDrawScreen(DX_SCREEN_BACK);
	DeleteGraph(drawbufferA);
};