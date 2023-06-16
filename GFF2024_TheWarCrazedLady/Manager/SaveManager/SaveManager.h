//�Z�[�u�}�l�[�W���[
#pragma once
#include "Main.h"

//�Z�[�u�f�[�^�̍ő�X���b�g��
constexpr auto SAVEDATA_INDEX = 16;

//�Z�[�u�f�[�^�̊�{�I�ȏ��ƂȂ�\����
struct MetaData {
	int PlayTime_Second = 0;		//�v���C����
	int PlayingMode		= 0;		//�v���C���̃��[�h
	int SavedChapter	= 0;		//�Z�[�u�������
	int SavedObjective	= 0;		//�Z�[�u�������_�Ő��s���̃N�G�X�g
	int SavedPlace		= 0;		//�Z�[�u�����ꏊ
};

//�L�����f�[�^�Ȃ�

//�Z�[�u�f�[�^�̖{�̂ƂȂ�\����
struct PlayData {
	//������
};

bool LoadParameter();				//�Z�[�u�f�[�^�̓ǂݍ��݂��s��
void GetMetaData(MetaData* Dest);	//���^�f�[�^���擾����
bool LoadMetaParameter();			//���^�f�[�^��ǂݍ���
void SaveMetaParameter();			//���^�f�[�^�̏�������
bool SaveParameter();				//�Z�[�u�f�[�^�̏������݂��s��