#include "GameMain_Task.h" 
#include "DxLib.h"
#include "MainSystem.h"

typedef enum _Task_GameMainState
{
	Task_GameMainState_StageStart_Wait,		//ステージ開始待ち中
	Task_GameMainState_InGame,				//ゲーム中
	Task_GameMainState_End					//終了状態
}Task_GameMainState;


