#include "DxLib_Sub.h"

DxLib_Sub::DxLib_Sub():
	Now_Status(),
	Previous_Status()
{

}

void DxLib_Sub::Update_Status()
{
	//一時保管変数
	char TempKey[256];
	//全てのキーの入力情報を入手
	GetHitKeyStateAll(TempKey);
	//現在のキー情報を記録
	Previous_Status = Now_Status;

	//押されたキー
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