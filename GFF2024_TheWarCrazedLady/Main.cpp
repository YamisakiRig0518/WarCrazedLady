#include "Main.h"

//�V�[���Ǘ��p
vector<SceneClass*> Scenes; int ActiveScene{ Start_Scene };

int _stdcall wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE, _In_ LPWSTR lpCmdline, _In_ int nShowCmd) {
	//�E�B���h�E���[�h�ɐݒ�
	ChangeWindowMode(TRUE);

	//��ʃT�C�Y�̐ݒ�
	SetGraphMode(Window_Width, Window_Height, Window_Color, Window_FPS);

	//��d�N���͂��Ȃ��悤�ɐݒ�
	SetDoubleStartValidFlag(FALSE);

	//�E�B���h�E����A�N�e�B�u�̎��������͑��s����
	SetAlwaysRunFlag(TRUE);

	//���O�o�͂𖳌���
	SetOutApplicationLogValidFlag(false);

	//�E�B���h�E�^�C�g��
	SetWindowText("");

	//�A�C�R���ύX(�����ōs��)
	//SetWindowIconID(104);

	//�����������Ƃ�(�t���[�����[�g�������|����)
	SetWaitVSyncFlag(TRUE);
	
	//���C�u�����̏������i�G���[�����������ꍇ�͂������ɃA�v���I���j
	if (DxLib_Init() != 0) return -1;

	//�`�����o�b�t�@�ɕύX
	SetDrawScreen(DX_SCREEN_BACK);

	//�g���A�Z�b�g���ꊇ���[�h
	//�����Ɏ���֐���ǉ�

	//�V�[���Ǘ��̑O����
	Scenes.emplace_back(new ShowLogo());
	Scenes.emplace_back(new TitleScene());

	Scenes[ActiveScene]->Initialize();
	 
	//���C�����[�v
	while (ProcessMessage() == 0) {
		//�u�����h���[�h��`��P�x�̐ݒ���ꉞ�߂��Ă���
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		SetDrawBright(255, 255, 255);

		//�o�b�t�@�̕`����e���폜
		ClearDrawScreen();

		//�V�[���̎�v����
		Scenes[ActiveScene]->Main();
		
		//�`����e��\���E�B���h�E�ɕ`��
		ScreenFlip();
	}

	//�����Ń��\�[�X�̉�����s��

	//DX���C�u�����̌�n��
	DxLib_End();

	//�A�v���P�[�V�����̏I��
	return 1;
};

//�w��ID�ƊY������I�u�W�F�N�g�f�[�^�̎擾
ObjectClass* GetObj(list<unique_ptr<ObjectClass>>& base, int ID) {
	for (auto i = base.begin(); i != base.end(); i++) {
		if ((*i)->ObjectID == ID) {
			return (*i).get();
		}

		return nullptr;
	}
};

//�V�[���؂�ւ��i�Y������V�[����������ΐ؂�ւ��Ȃ��j
void SetScene(int SceneID) {
	bool isComplete = false;
	
	for (auto i = Scenes.begin(); i != Scenes.end(); i++) {
		if (SceneID == (*i)->SceneID) {
			//�V�[���̏I������
			Scenes[ActiveScene]->Reset();

			//�V�[���Ŏg�����A�Z�b�g�̃A�����[�h
			DeleteAsset_Scene(ActiveScene);

			//�ړ���̃V�[���̏���������
			(*i)->Initialize();

			//���s���V�[����ID��ύX���ăV�[���ύX����
			ActiveScene = (*i)->SceneID;

			break;
		}
	}
};

