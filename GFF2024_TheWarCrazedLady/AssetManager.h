#pragma once

//���\�[�X�̎��
enum Asset_Category {
	IMAGE,								//�C���[�W
	BGM,								//�o�b�N�O���E���h�~���[�W�b�N
	SE,									//�T�E���h�G�t�F�N�g
};

//�A�Z�b�g�Ǘ��p�\����
struct AssetData {
	const char* AliasName;				//�G�C���A�X��
	const int	HandleID;				//�n���h��
	const int	Category;				//�A�Z�b�g�̎��(Asset_Category�񋓎Q��)
	const int	UseScene;				//�A�Z�b�g���g������(-1�̏ꍇ�̓V�X�e���S�̂ŗ��p���Ă��鈵���ɂȂ�)
};

//�t�H���g�A�Z�b�g�Ǘ��p
struct FontAsset {
	const char* AliasName;				//�G�C���A�X��
	const int	HandleID;				//�n���h��
	const int	FontSize;				//�t�H���g�T�C�Y
	const int	UseScene;				//�A�Z�b�g���g������(-1�̏ꍇ�̓V�X�e���S�̂ŗ��p���Ă��鈵���ɂȂ�)
};

//������ƍ�

bool LoadAsset(const char* FilePath, int UseScene);

bool GetAsset(const char* AliasName, int Category);

bool StringCheck(const char* targetA, const char* targetB);