#include "TitleScene.h"

//�R���X�g���N�^
TitleScene::TitleScene() {
	SceneID = Scene_Title;
}

//����������
void TitleScene::Initialize() {

};

//��v����
void TitleScene::Main() {
	DrawString(0, 0, "This is Title Scene", GetColor(255, 255, 255));
};

//�I������
void TitleScene::Reset() {

};