#include "ControlManager.h"

KeyStat KeyStatus[CMng_ControlKeys] = {
	{KEY_INPUT_LEFT	, 0 , CMK_LEFT		},
	{KEY_INPUT_RIGHT, 0 , CMK_RIGHT		},
	{KEY_INPUT_UP	, 0 , CMK_UP		},
	{KEY_INPUT_DOWN	, 0 , CMK_DOWN		},

	{KEY_INPUT_F	, 0 , CMK_DECIDE	},
	{KEY_INPUT_D    , 0 , CMK_CANCEL	},
	{KEY_INPUT_E	, 0 , CMK_INVENTORY	}
};

ButtonStat BtnStatus[CMng_ControlKeys] = {
	{PAD_INPUT_LEFT		, 0 , CMG_LEFT		},
	{PAD_INPUT_RIGHT	, 0 , CMG_RIGHT		},
	{PAD_INPUT_UP		, 0 , CMG_UP		},
	{PAD_INPUT_DOWN		, 0 , CMG_DOWN		},

	{PAD_INPUT_2		, 0 , CMG_DECIDE	},
	{PAD_INPUT_1		, 0 , CMG_CANCEL	},
	{PAD_INPUT_3		, 0 , CMG_INVENTORY	}
};

//�L�[�{�[�h���͔���p
int cm_count	= 0;
int cm_wait1	= 0;
int cm_wait2	= 0;

//�Q�[���p�b�g���͔���p
int cm_Gcount = 0;
int cm_Gwait1 = 0;
int cm_Gwait2 = 0;

//Hitkey�֐��FDxlib�W����CheckHitKey�ɃL�[���[�v�@�\����ꂽ�֐�
//�y��1�����z	Keycode(int)		Regist��(CMK_�ɑ����񋓖�����́j
//�y��2�����z	KeyLoop(bool)		�L�[���������������A�A���œ��͂��邩�ǂ���
//�y��3�����z	KeyLoop_Start(int)	�L�[�̘A�����͂����b��ɊJ�n���邩
//�y��4�����z	KeyLoop_Speed(int)	�L�[�̘A�����͂̊Ԋu(1000 = 1�b)
bool HitKey(int Keycode, bool ButtonLoop, int ButtonLoop_Start, int ButtonLoop_Speed) {

	for (int i = 0; i < CMng_ControlKeys; i++) {
		//�����Ŏw�肳�ꂽ�L�[�R�[�h�Ɠo�^���ꂽ�L�[�R�[�h�����v���Ă��邩
		if (Keycode == KeyStatus[i].RegistID) {
			//���͂���Ă��邩����
			if (CheckHitKey(KeyStatus[i].KeyCode)) {
				//�L�[�������ꂽ�ꍇ�A�P�x�������͂��郂�[�h�̏ꍇ
				if (!ButtonLoop && !KeyStatus[i].isHitKey) {
					KeyStatus[i].isHitKey = true;
					return true;
				//�L�[�������ꂽ�ꍇ�A���������Ă���ԓ��͂��郂�[�h�̏ꍇ
				}else if(ButtonLoop){
					if (!KeyStatus[i].isHitKey) {
						KeyStatus[i].StartTime = GetNowCount();
						KeyStatus[i].isHitKey = true;
					}else {
						//�L�[�̘A�����̓��[�h�̏ꍇ
						//�L�[��������Ă���w�肳�ꂽ���Ԃ��o�߂����ꍇ�͘A�����͊J�n
						if (KeyStatus[i].CM_count > ButtonLoop_Start && KeyStatus[i].isHitKey) {
							//�L�[��A�����͂���Ԋu
							//�w�肳�ꂽ���Ԃ��o�߂����ꍇ��true��Ԃ�
							KeyStatus[i].CM_wait2 = GetNowCount() - KeyStatus[i].CM_wait1;
							if (KeyStatus[i].CM_wait2 > ButtonLoop_Speed) {
								KeyStatus[i].CM_wait1 = GetNowCount();
								return true;
							}else {
								return false;
							}
						}else {
							//�L�[��������Ă���̎��Ԃ��v��
							KeyStatus[i].CM_count = GetNowCount() - KeyStatus[i].StartTime;
							KeyStatus[i].CM_wait1 = GetNowCount();
							return false;
						}
					}
				//�u�P�x�������͂��郂�[�h�v�œ��̓t���O�����ɗ����Ă���ꍇ
				}else if(!ButtonLoop && KeyStatus[i].isHitKey) {
					return false;
				}
			//�L�[��������Ă��Ȃ��ꍇ�͓��̓t���O�����낷
			}else {
				KeyStatus[i].isHitKey	= false;
				KeyStatus[i].StartTime	= 0;
				KeyStatus[i].CM_count = 0;
				KeyStatus[i].CM_wait1 = 0;
				KeyStatus[i].CM_wait2 = 0;
				return false;
			}
		}
	}
};

//HitButton�֐��FHitKey�֐��̃Q�[���p�b�h��
//�y��1�����z	ButtonCode(int)			Regist��(CMG_�ɑ����񋓖�����́j
//�y��2�����z	ButtonLoop(bool)		�{�^�����������������A�A���œ��͂��邩�ǂ���
//�y��3�����z	ButtonLoop_Start(int)	�{�^���̘A�����͂����b��ɊJ�n���邩
//�y��4�����z	ButtonLoop_Speed(int)	�{�^���̘A�����͂̊Ԋu(1000 = 1�b)
bool HitButton(int ButtonCode, bool ButtonLoop, int ButtonLoop_Start, int ButtonLoop_Speed) {

	for (int i = 0; i < CMng_ControlKeys; i++) {
		//�����Ŏw�肳�ꂽ�L�[�R�[�h�Ɠo�^���ꂽ�L�[�R�[�h�����v���Ă��邩
		if (ButtonCode == BtnStatus[i].RegistID) {
			//���͂���Ă��邩����
			if ((GetJoypadInputState(DX_INPUT_PAD1) & BtnStatus[i].KeyCode)) {
				//�L�[�������ꂽ�ꍇ�A�P�x�������͂��郂�[�h�̏ꍇ
				if (!ButtonLoop && !BtnStatus[i].isHitKey) {
					BtnStatus[i].isHitKey = true;
					return true;
					//�L�[�������ꂽ�ꍇ�A���������Ă���ԓ��͂��郂�[�h�̏ꍇ
				}else if (ButtonLoop) {
					if (!BtnStatus[i].isHitKey) {
						BtnStatus[i].StartTime = GetNowCount();
						BtnStatus[i].isHitKey = true;
					}else {
						//�L�[�̘A�����̓��[�h�̏ꍇ
						//�L�[��������Ă���w�肳�ꂽ���Ԃ��o�߂����ꍇ�͘A�����͊J�n
						if (BtnStatus[i].CM_count > ButtonLoop_Start && BtnStatus[i].isHitKey) {
							//�L�[��A�����͂���Ԋu
							//�w�肳�ꂽ���Ԃ��o�߂����ꍇ��true��Ԃ�
							BtnStatus[i].CM_wait2 = GetNowCount() - BtnStatus[i].CM_wait1;
							if (BtnStatus[i].CM_wait2 > ButtonLoop_Speed) {
								BtnStatus[i].CM_wait1 = GetNowCount();
								return true;
							}else {
								return false;
							}
						}else {
							//�L�[��������Ă���̎��Ԃ��v��
							BtnStatus[i].CM_count = GetNowCount() - BtnStatus[i].StartTime;
							BtnStatus[i].CM_wait1 = GetNowCount();
							return false;
						}
					}
					//�u�P�x�������͂��郂�[�h�v�œ��̓t���O�����ɗ����Ă���ꍇ
				}else if (!ButtonLoop && BtnStatus[i].isHitKey) {
					return false;
				}
				//�L�[��������Ă��Ȃ��ꍇ�͓��̓t���O�����낷
			}else {
				BtnStatus[i].isHitKey = false;
				BtnStatus[i].StartTime = 0;
				BtnStatus[i].CM_count = 0;
				BtnStatus[i].CM_wait1 = 0;
				BtnStatus[i].CM_wait2 = 0;
				return false;
			}
		}
	}
};