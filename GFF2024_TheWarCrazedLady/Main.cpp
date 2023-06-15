#include "Main.h"

//�V�[���Ǘ��p
vector<SceneClass*> Scenes; int ActiveScene{ 0 };

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
	Scenes.emplace_back(new TitleScene());

	string Path = "ThisisFileName.";
	string Alias;

	int LastPeriod = Path.find(".");
	int LastSlash = Path.find("/");
	int Length = LastPeriod - LastSlash;

	Alias = Path.substr(LastSlash+1, Length-1);
	
	//���C�����[�v
	while (ProcessMessage() == 0) {
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