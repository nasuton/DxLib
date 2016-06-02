#pragma once

#define TASK_MAX (16)

 //基本情報
typedef struct _TaskBaseInfo
{
	//状態推移処理の実行優先順位
	int StepPriority;

	//描画処理の実行優先順位
	int RenderPriority;

	//状態推移処理
	bool(*Step)(struct _TaskInfo *taskinfo, float StepTime);

	//描画処理
	void(*Render)(struct _TaskInfo *taskinfo);

	//後始末処理
	void(*Terminate)(struct _TaskInfo *taskinfo);

}TaskBaseInfo;

//タスクの情報
typedef struct _TaskInfo
{
	TaskBaseInfo* Base;

	void* Data;

	struct _TaskInfo* StepNext;

	struct _TaskInfo* RenderNext;

	struct _TaskInfo* Add_or_DeletionNext;
}TaskInfo;

//タスクシステム情報
typedef struct _TaskSystemInfo
{
	bool Run;

	TaskInfo* StepTask[TASK_MAX];

	TaskInfo* RenderTask[TASK_MAX];

	TaskInfo* AddTaskList;

	TaskInfo* DeletionTaskList;
}TaskSystemInfo;

//状態推移処理を実行する
extern bool TaskSystem_Step(TaskSystemInfo *tasksysteminfo, float StepTime);

//描画処理を実行する
extern void TaskSystem_Render(TaskSystemInfo *tasksysteminfo);

//タスクを追加する
extern void TaskSystem_AddTask(TaskSystemInfo *tasksysteminfo, TaskInfo *taskinfo);

//タスクを削除する
extern void TaskSystem_DeletionTask(TaskSystemInfo *tasksysteminfo, TaskInfo *taskinfo);