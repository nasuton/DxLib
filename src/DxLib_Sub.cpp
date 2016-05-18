#include "DxLib_Sub.h"

DxLib_Sub::DxLib_Sub():
	Now_Status(),
	Previous_Status()
{

}

void DxLib_Sub::Update_Status()
{
	//�ꎞ�ۊǕϐ�
	char TempKey[256];
	//�S�ẴL�[�̓��͏������
	GetHitKeyStateAll(TempKey);
	//���݂̃L�[�����L�^
	Previous_Status = Now_Status;

	//�����ꂽ�L�[
	for (int i = 0; i < 256; i++)
	{
		if (TempKey[i] != 0)
		{
			Now_Status.key[i] = true;
		}
		else
		{
			Now_Status.key[i] = false;
		}
	}
}

bool DxLib_Sub::Push_Key(const int KEY_CODE) 
{
	return !Previous_Status.key[KEY_CODE] &&
		   Now_Status.key[KEY_CODE];
}

bool DxLib_Sub::Press_Key(const int KEY_CODE)
{
	return Now_Status.key[KEY_CODE];
}

bool DxLib_Sub::Pull_Key(const int KEY_CODE)
{
	return Previous_Status.key[KEY_CODE] &&
		   !Now_Status.key[KEY_CODE];
}