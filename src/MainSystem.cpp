#include "Title_Task.h"
#include "MainSystem.h"

//システム情報
typedef struct _SystemInfo 
{
	//推移する時間
	float StepTime;

	//処理を行う回数
	int StepNum;

	//終了フラグ
	bool ExitGame;

	//ゲーム開始時のステージ
	int StartStage;

	//タスクシステム情報
	TaskSystemInfo _TaskSysteminfo;

}SystemInfo;

static SystemInfo _SystemInfo;

bool System_StartTitle()
{
	if (!Title_Task_Start())
	{
		return false;
	}

	return true;
}

//タスクシステム情報構造体のアドレスを取得
TaskSystemInfo *System_GetTaskSystemInfo()
{
	return &_SystemInfo._TaskSysteminfo;
}