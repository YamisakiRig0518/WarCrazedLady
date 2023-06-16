//Main.h

#pragma once

#include "DxLib.h"

#include <list>
#include <memory>

#include <string>
#include <vector>

#include "Manager/TotalManager.h"
#include "Manager/AssetManager/AssetManager.h"
#include "Manager/SaveManager/SaveManager.h"
#include "Manager/ControlManager/ControlManager.h"

#include "Scene/SplashLogo/Section_ShowLogo.h"
#include "Scene/TitleScene/TitleScene.h"


//���O��Ԃ̐錾
using namespace std;

//��ʊ֘A
constexpr auto Window_Width		= 1280;	//��ʂ̉���
constexpr auto Window_Height	= 720;	//��ʂ̏c��
constexpr auto Window_Color		= 32;	//�F�[�x
constexpr auto Window_FPS		= 60;	//FPS�ݒ�

//�V�X�e���֘A
constexpr auto Start_Scene		= Scene_Logo;

//�w�肵��ID�ƊY������I�u�W�F�N�g�f�[�^�̎擾
ObjectClass* GetObj(list<unique_ptr<ObjectClass>>&, int ID);

//�V�[���؂�ւ�
void SetScene(int SceneID);

