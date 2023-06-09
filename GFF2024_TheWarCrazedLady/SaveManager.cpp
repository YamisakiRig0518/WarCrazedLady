#include "SaveManager.h"

MetaData MetaParam[SAVEDATA_INDEX];
int ReadIndexes = 0;

bool LoadParameter() { return false; };	//�Z�[�u�f�[�^�̓ǂݍ��݂��s��
bool SaveParameter() { return false; };	//�Z�[�u�f�[�^�̏������݂��s��

bool LoadMetaParameter() {
	FILE* file;

	//���^�t�@�C����ǂݍ���
	fopen_s(&file, "MetaParameter.txt", "r+");

	//�t�@�C�����̂��Ȃ��ꍇ��false��Ԃ�
	if (file == NULL)return false;

	//���^�t�@�C���̓��e��ǂݍ���
	int reading_cur = 0;	//�z��̓[������
	ReadIndexes = 0;		//�ǂݍ��݃J�E���g���Z�b�g
	while (fscanf_s(file, "%d, %d, %d, %d, %d\n",
		&MetaParam[reading_cur].PlayTime_Second,	//���v���C����
		&MetaParam[reading_cur].PlayingMode,		//�v���C���[�h�i��Փx�j
		&MetaParam[reading_cur].SavedChapter,		//�Z�[�u�������_�ł̃`���v�^�[
		&MetaParam[reading_cur].SavedObjective,		//�Z�[�u�������_�Ő��s���̃N�G�X�g
		&MetaParam[reading_cur].SavedPlace)			//�Z�[�u�����n�_
		
		//�I�_�����ɓ��B���Ă��炸
		!= EOF && ReadIndexes < SAVEDATA_INDEX) {

		reading_cur++;	//���̔z��Ƀ`�F���W
		ReadIndexes++;	//�ǂݍ��߂��J�E���g�𑝂₷
	};

	//�t�@�C�������
	fclose(file);

	//�t�@�C����ǂݍ��߂��ꍇ��true��Ԃ�
	return true;
};

void SaveMetaParameter() {
	FILE* file;

	//���^�t�@�C����ǂݍ���
	fopen_s(&file, "MetaParameter.txt", "w+");

	//�������ޓ��e�̏���
	for (int cnt = 0; cnt < SAVEDATA_INDEX; cnt++) {
		char WriteData[128];

		sprintf_s(WriteData, "%d, %d, %d, %d, %d\n",
			MetaParam[cnt].PlayTime_Second,	//���v���C����
			MetaParam[cnt].PlayingMode,		//�v���C���[�h�i��Փx�j
			MetaParam[cnt].SavedChapter,	//�Z�[�u�������_�ł̃`���v�^�[
			MetaParam[cnt].SavedObjective,	//�Z�[�u�������_�Ő��s���̃N�G�X�g
			MetaParam[cnt].SavedPlace);		//�Z�[�u�����n�_
	}

	//�t�@�C�������
	fclose(file);
};


void GetMetaData(MetaData* Dest) {
	memcpy_s(Dest, sizeof(MetaParam), MetaParam, sizeof(MetaParam));
};