#pragma once
#include "DxLib.h"

struct AllStatus
{
	bool key[256];
};

class DxLib_Sub 
{
public:
	DxLib_Sub();

	//���̃A�b�v�f�[�g
	void Update_Status();
	//�Y������L�[�������ꂽ�u��
	bool Push_Key(const int KEY_CODE);
	//�Y������L�[�������ꑱ���Ă��邩
	bool Press_Key(const int KEY_CODE);
	//�Y������L�[�������ꂽ�u��
	bool Pull_Key(const int KEY__CODE);

private:
	AllStatus Now_Status;
	AllStatus Previous_Status;
};