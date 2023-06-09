#pragma once
#include <list>
#include <memory>

using namespace std;

//�����^�Q�������W�̍\����
struct Vector2 {
	float x{ 0.0f };
	float y{ 0.0f };
};
//�V�[���p�̊��N���X
class SceneClass{
public :
	SceneClass()	{};					//�R���X�g���N�^
	~SceneClass()	{};					//�f�X�g���N�^

	virtual void Initialize()	= 0;	//�V�[���̏���������
	virtual void Main()			= 0;	//�V�[���̎�v����

	int SceneID{ 0 };					//�V�[��ID
};

//�I�u�W�F�N�g�p�̊��N���X
class ObjectClass {
public :
	ObjectClass() {};					//�R���X�g���N�^
	~ObjectClass() {};					//�f�X�g���N�^

	int		ObjectID{ 0 };				//�I�u�W�F�N�gID
	Vector2 pos{ 0.0f, 0.0f };			//���W
	Vector2 vec{ 0.0f, 0.0f };			//�x�N�g��

	virtual void Initialize() = 0;									//�I�u�W�F�N�g�̏�����
	virtual int Action(list<unique_ptr<ObjectClass>>& base) = 0;	//�I�u�W�F�N�g�̎�v����
};

