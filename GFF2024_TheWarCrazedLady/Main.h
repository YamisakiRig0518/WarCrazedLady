//Main.h

#pragma once

#include "DxLib.h"

#include <list>
#include <memory>

#include <string>
#include <vector>

#include "TotalManager.h"
#include "SaveManager.h"
#include "AssetManager.h"

#include "Scene/TitleScene/TitleScene.h"

//���O��Ԃ̐錾
using namespace std;

//��ʊ֘A
constexpr auto Window_Width		= 1280;	//��ʂ̉���
constexpr auto Window_Height	= 720;	//��ʂ̏c��
constexpr auto Window_Color		= 32;	//�F�[�x
constexpr auto Window_FPS		= 60;	//FPS�ݒ�

//�w�肵��ID�ƊY������I�u�W�F�N�g�f�[�^�̎擾
ObjectClass* GetObj(list<unique_ptr<ObjectClass>>&, int ID);