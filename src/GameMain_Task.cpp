#include "GameMain_Task.h" 
#include "DxLib.h"
#include "MainSystem.h"

typedef enum _Task_GameMainState
{
	Task_GameMainState_StageStart_Wait,		//�X�e�[�W�J�n�҂���
	Task_GameMainState_InGame,				//�Q�[����
	Task_GameMainState_End					//�I�����
}Task_GameMainState;


