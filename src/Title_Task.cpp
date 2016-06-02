#include "Title_Task.h"
#include "Task.h"
#include "DxLib.h"
#include "MainSystem.h"
#include <math.h>

#define TITLEDATA_FIREPATH  "res/TitleData"

#define FADE_OUT_TIME		(1.0f)

typedef enum _Task_TitleState
{
	Task_TitleState_FadeOut,
	Task_TitleState_End
}Task_TitleState;

//タイトル用データ
typedef struct _Task_TitleData
{
	TaskInfo _TaskInfo;

	Task_TitleState State;

	int Counter;

	int BackGraphHandle;

	int TitleFontHandle;
}Task_TitleData;


static bool Title_Task_Step(TaskInfo *taskinfo, float StepTime);

static void Title_Task_Render(TaskInfo *taskinfo);

static void Title_Task_Terminate(TaskInfo *taskinfo);

//タイトルタスクの基本情報
static TaskBaseInfo TitelTaskBaseInfo =
{
	8,
	8,
	Title_Task_Step,
	Title_Task_Render,
	Title_Task_Terminate
};

//画面推移処理を行う
static bool Title_Task_Step(TaskInfo *taskinfo, float StepTime)
{
	Task_TitleData *tasktitledata = (Task_TitleData *)taskinfo->Data;

	//タイトル状態によって処理を分岐
	switch (tasktitledata->State)
	{
	case Task_TitleState_FadeOut:
		tasktitledata->Counter += StepTime;
		if (tasktitledata->Counter > FADE_OUT_TIME)
		{
			tasktitledata->State = Task_TitleState_End;

			TaskSystem_DeletionTask(System_GetTaskSystemInfo(), &tasktitledata->_TaskInfo);
		}

		break;

	case Task_TitleState_End:
		break;

	default:
		break;
	}


	return true;
}

//描画処理を行う
static void Title_Task_Render(TaskInfo *taskinfo)
{
	Task_TitleData *tasktitledata = (Task_TitleData*)taskinfo->Data;

	DrawGraph(0, 0, tasktitledata->BackGraphHandle, FALSE);
}

//
static void Title_Task_Terminate(TaskInfo *taskinfo)
{
	Task_TitleData *tasktitledata = (Task_TitleData*)taskinfo->Data;

	//タイトルで使用した画像の削除
	DeleteGraph(tasktitledata->BackGraphHandle);

	DeleteFontToHandle(tasktitledata->TitleFontHandle);

}


bool Title_Task_Start()
{
	Task_TitleData *tasktitledata;

	//使用するメモリの確保
	tasktitledata = (Task_TitleData*)calloc(1, sizeof(Task_TitleData));
	if (tasktitledata == NULL)
	{
		return false;
	}


	//タイトル画像の読み込み
	tasktitledata->BackGraphHandle = LoadGraph(TITLEDATA_FIREPATH"");
	if (tasktitledata->BackGraphHandle == -1)
	{
		return false;
	}

	//使用するフォント
	tasktitledata->TitleFontHandle = CreateFontToHandle(NULL, 40, 8, DX_FONTTYPE_ANTIALIASING_8X8);
	if (tasktitledata->TitleFontHandle == -1)
	{
		return false;
	}

	//タスクを登録する
	tasktitledata->_TaskInfo.Base = &TitelTaskBaseInfo;
	tasktitledata->_TaskInfo.Data = tasktitledata;
	TaskSystem_AddTask(System_GetTaskSystemInfo(), &tasktitledata->_TaskInfo);

	return true;
}

