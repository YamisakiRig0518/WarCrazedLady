#include "Main.h"
#include "AssetManager.h"

constexpr int category_MAX = 3;

vector<AssetData*> Assets;	//�A�Z�b�g���Ǘ�����ϔz��
string Categories[category_MAX] = { ".png",".mp3",".wav" };

//LoadAsset�֐��F�摜�EBGM�E���ʉ���ǂݍ��ފ֐�
//�V�[�����ɃA�Z�b�g�̊Ǘ����s���ׂɎ���
//�g���q�Ŕ��ʂ��Ă��ꂼ��̃J�e�S���ɕ��ނ����
bool LoadAsset(const char* FilePath, int UseScene) {
	string	FilePath_STR	= FilePath;
	string	AliasName;
	int		File_Category	= -1;
	int		File_Handle		= 0;

	//�t�@�C���������o���ׂɍŌ���́u/�v�Ɓu.�v�̈ʒu���擾
	//��������t�@�C�����̈ʒu������o���āu�t�@�C�����v�̒��������߂Ă���
	int LastPeriod = FilePath_STR.find(".");
	int LastSlash = FilePath_STR.find("/");
	int FileLength = LastPeriod - LastSlash;

	//�J�e�S������
	for (int i = 0; i < category_MAX; i++) {
		if (FilePath_STR.find(Categories[i])) {
			File_Category = i;
			break;
		}
	}
	//�Ή�����g���q�ł͖��������ꍇ��false��Ԃ�
	if (File_Category == -1)return false;

	//�t�@�C���ǂݍ���
	switch (File_Category) {
	case IMAGE:	//�摜
		File_Handle = LoadGraph(FilePath);
		break;
	case BGM:	//���y
		File_Handle = LoadSoundMem(FilePath);
		break;
	case SE:	//���ʉ�
		File_Handle = LoadSoundMem(FilePath);
		break;
	default:	//�Ή����Ȃ��g���q�̏ꍇ
		return false;	//�Ή����Ă��Ȃ��t�@�C�����ǂݍ��܂ꂽ�ꍇ��false��Ԃ�
		break;
	}
	if (File_Handle == -1)return false;	//�t�@�C�������݂��Ȃ��ꍇ��false��Ԃ�

	//�t�@�C�������G�C���A�X�Ƃ��ēo�^
	AliasName = FilePath_STR.substr(LastSlash + 1, FileLength - 1);
	
	//string�^����char�^�z��ɕϊ�
	char* CharArray = new char[AliasName.size() + 1];
	memcpy(CharArray, AliasName.c_str(), AliasName.size() + 1);

	//�o�^���s��
	Assets.emplace_back(new AssetData{ CharArray, File_Handle, File_Category, UseScene });

	//����ɏ��������������̂�true��Ԃ�
	return true;
};