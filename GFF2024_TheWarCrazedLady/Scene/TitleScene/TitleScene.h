#pragma once
#include "Main.h"

class TitleScene : public SceneClass{
public:
	TitleScene();
	~TitleScene() {};

	void Initialize();	//�^�C�g���V�[���̏���������
	void Main();		//�^�C�g���V�[���̎�v����
	void Reset();		//�^�C�g���V�[���̏I������
};