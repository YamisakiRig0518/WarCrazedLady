#pragma once
#include "Main.h"
#include "TotalManager.h"
constexpr int LogoLength = 14;
constexpr int interval = 30; //100frame
constexpr float fadespeed = 6.5f; // 0.25/f
class ShowLogo : public SceneClass{
public:
	ShowLogo() ;
	~ShowLogo() {};
	//������
	void Initialize();
	//���C���̃��C�����[�v
	void Main();
	//������Ԃ֖߂��֐�
	void Reset();

	//���S�\�����������_���ɐݒ肷��
	void SequenceRandomize() {
		for (int Pseq = 0; Pseq < (LogoLength - 3);) {
			int randomNum = (rand() % (LogoLength-3));
			int result = 0;
			for (int seq = 0; seq <(LogoLength - 3); seq++) {
				if (Pseq != seq && Logo_Sequence[seq] == randomNum) {
					result = 1;
					break;
				}
			}
			if (result == 1) {
				continue;
			}
			else if (result == 0) {
				Logo_Sequence[Pseq] = randomNum;
				Pseq++;
				
			}
		}
		
		for (int i = 0; i < 5; i++) {

		}
	};
private:
	//���S�̕������W�ƃT�C�Y�f�[�^
	float Logodata[LogoLength][4] = {
		//�n�_�Ɣ͈�(�I�_��[�n�_+�͈�]�̍��v����Z�o)
		{  33, 18,  158,252}, //Y(1)
		{ 201, 91,  135,179}, //a(2)
		{ 374, 91,  208,179}, //m(3)
		{ 633, 18,   45,252}, //i(4)
		{ 693, 91,  146,179}, //s(5)
		{ 866, 91,  135,179}, //a(6)
		{1040, 18,  146,252}, //k(7)
		{1202, 18,   45,252}, //i(8)

		{1370, 18,  163,252}, //R(9)
		{1560, 18,   45,252}, //i(10)
		{1610,141,  158,202}, //g(11)

		{ 212, 18, 1142, 37}, //Bar1
		{  16, 43,   40,300}, //Bar2 (16,303 40x40)
		{  56,303, 1554, 40}  //Bar3 (1571,303 40x40)
	};

	/*���S�\���p�ϐ�*/ 
		int   Logo_Sequence[LogoLength]{ 0 }; //�����\���̏�����
		float Logo_Alpha[LogoLength]{ 0 };//�e���S�����̓����x
		int   LogoPhase[LogoLength]{ 0 };
		int   Sequence = 0;
		int   SeqStart = 0;
		int   SeqTime = 0;

		int   BarLength[3];

		int   drawbufferA;

		int   ease[3] = { 48,24,56 };
		
		float AllAlpha = 1.0f;
		int   AllAlpha_int = 255;
		int   phase = 0;

		int   msCount = 0;
};