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
	int LastSlash = FilePath_STR.find_last_of("/");
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

//GetAsset�֐��FLoadAsset�œǂݍ��񂾃A�Z�b�g�̃n���h����Ԃ�
//������Ȃ������ꍇ��false��Ԃ�
int GetAsset(const char* AliasName, int Category) {
	
	//���O�����S�Ɉ�v�����J�e�S���������̏ꍇ�̓n���h����Ԃ�
	for (int i = 0; i < Assets.size(); i++) {
		if (StringCheck(AliasName, Assets[i]->AliasName) &&
			Category == Assets[i]->Category) {
			return Assets[i]->HandleID;
		}
	}

	return -1;
}

//StringCheck�֐��F��������v���Ă��邩���ʂ���
//(GetAsset�֐����Ŏd�l)
bool StringCheck(const char* targetA, const char* targetB) {
	string TargetA = targetA;
	string TargetB = targetB;

	int charsize	= 0;
	int seekA		= 0;
	int seekB		= 0;
	while (seekA < TargetA.size()) {
		string compareA, compareB;

		if (IsDBCSLeadByte(TargetA[seekA]) == 0) {
			charsize = 1;
			seekA++;
		}else {
			charsize = 2;
			seekA += 2;
		}
		compareA = TargetA.substr(seekA - charsize, charsize);

		if (seekB >= TargetB.size())return false;

		if (IsDBCSLeadByte(TargetB[seekB]) == 0) {
			charsize = 1;
			seekB++;
		}
		else {
			charsize = 2;
			seekB += 2;
		}

		compareB = TargetB.substr(seekB - charsize, charsize);

		if (compareA.compare(compareB) != 0)return false;
	}



	return true;
};

//DeleteAsset_Scene�֐��F�w�肵���V�[���Ŏg���Ă���A�Z�b�g��S�ăA�����[�h
//�i�V�[���`�F���W���Ɏ��s�����j
void DeleteAsset_Scene(int TargetScene) {
	auto iterator = Assets.begin();

	while (iterator != Assets.end()) {
		int AssetCat = (*iterator)->Category;
		int AssetScn = (*iterator)->UseScene;
		int AssetHnd = (*iterator)->HandleID;

		if (AssetScn == TargetScene) {
			switch (AssetCat) {
			case IMAGE:
				DeleteGraph(AssetHnd);
				break;

			case BGM:
			case SE:
				DeleteSoundMem(AssetHnd);
				break;
			}
			iterator = Assets.erase(iterator);
		}else {
			iterator++;
		}
	}
};
