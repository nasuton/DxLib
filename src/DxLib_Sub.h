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

	//情報のアップデート
	void Update_Status();
	//該当するキーが押された瞬間
	bool Push_Key(const int KEY_CODE);
	//該当するキーが押され続けているか
	bool Press_Key(const int KEY_CODE);
	//該当するキーが離された瞬間
	bool Pull_Key(const int KEY__CODE);

private:
	AllStatus Now_Status;
	AllStatus Previous_Status;
};