#include "Task.h"
#include <string.h>
#include <malloc.h>

//追加や削除を反映する
static void TaskSystem_RefreshList(TaskSystemInfo *tasksysteminfo)
{
	TaskInfo *taskinfo;
	TaskInfo *nextinfo;
	TaskInfo *templateinfo;

	//登録されてるタスクを、タスクリストに追加する
	if (tasksysteminfo->AddTaskList != NULL)
	{
		for (taskinfo = tasksysteminfo->AddTaskList; taskinfo != NULL; taskinfo = nextinfo)
		{
			nextinfo = taskinfo->Add_or_DeletionNext;

			taskinfo->StepNext = tasksysteminfo->StepTask[taskinfo->Base->StepPriority];
			tasksysteminfo->StepTask[taskinfo->Base->StepPriority] = taskinfo;

			taskinfo->RenderNext = tasksysteminfo->RenderTask[taskinfo->Base->RenderPriority];
			tasksysteminfo->RenderTask[taskinfo->Base->RenderPriority] = taskinfo;

			taskinfo->Add_or_DeletionNext = NULL;

		}

		tasksysteminfo->AddTaskList = NULL;
	}

	//登録されているタスクを、タスクリストから削除する
	if (tasksysteminfo->DeletionTaskList != NULL)
	{
		for (taskinfo = tasksysteminfo->DeletionTaskList; taskinfo != NULL; taskinfo = nextinfo)
		{
			nextinfo = taskinfo->Add_or_DeletionNext;

			if (tasksysteminfo->StepTask[taskinfo->Base->StepPriority] == taskinfo)
			{
				tasksysteminfo->StepTask[taskinfo->Base->StepPriority] = taskinfo->StepNext;
			}
			else
			{
				templateinfo = tasksysteminfo->StepTask[taskinfo->Base->StepPriority];
				while (true)
				{
					if (templateinfo->StepNext == NULL)
					{
						break;
					}

					if (templateinfo->StepNext == taskinfo)
					{
						templateinfo->StepNext = taskinfo->StepNext;
						break;
					}

					templateinfo = templateinfo->StepNext;
				}
			}

			if (tasksysteminfo->RenderTask[taskinfo->Base->RenderPriority] == taskinfo)
			{
				tasksysteminfo->RenderTask[taskinfo->Base->RenderPriority] = taskinfo->RenderNext;
			}
			else
			{
				templateinfo = tasksysteminfo->RenderTask[taskinfo->Base->RenderPriority];
				for (;;) 
				{
					if (templateinfo->RenderNext == NULL)
					{
						break;
					}

					if (templateinfo->RenderNext == taskinfo)
					{
						templateinfo->RenderNext = taskinfo->RenderNext;
						break;
					}

					templateinfo = templateinfo->RenderNext;
				}
			}

			if (taskinfo->Base->Terminate != NULL)
			{
				taskinfo->Base->Terminate(taskinfo);
			}

			taskinfo->Add_or_DeletionNext = NULL;
			taskinfo->StepNext = NULL;
			taskinfo->RenderNext = NULL;

			if (taskinfo->Data != NULL)
			{
				free(taskinfo->Data);
			}
		}

		tasksysteminfo->DeletionTaskList = NULL;

	}

}

//状態推移を実行
bool TaskSystem_Step(TaskSystemInfo *tasksysteminfo, float StepTime)
{
	TaskInfo *taskinfo;
	
	//処理実行フラグを「true」へ
	tasksysteminfo->Run = true;

	for (int i = 0; i < TASK_MAX; i++)
	{
		for (taskinfo = tasksysteminfo->StepTask[i]; taskinfo != NULL; taskinfo = taskinfo->StepNext)
		{
			if (!taskinfo->Base->Step(taskinfo, StepTime))
			{
				return false;
			}
		}
	}

	//処理実行フラグを「false」へ
	tasksysteminfo->Run = false;

	//タスクの登録や削除をリストへ反映
	TaskSystem_RefreshList(tasksysteminfo);

	//正常終了
	return true;
}

//描画処理を実行
void TaskSystem_Render(TaskSystemInfo *tasksysteminfo)
{
	TaskInfo *taskinfo;

	//処理実行フラグﾞを「true」へ
	tasksysteminfo->Run = true;

	for (int i = 0; i < TASK_MAX; i++)
	{
		for (taskinfo = tasksysteminfo->RenderTask[i]; taskinfo != NULL; taskinfo = taskinfo->RenderNext)
		{
			if (taskinfo->Add_or_DeletionNext != NULL)
			{
				continue;
			}

			taskinfo->Base->Render(taskinfo);

		}
	}

	//処理実行フラグを「false」へ
	tasksysteminfo->Run = false;

	//タスクの登録や削除をリストへ反映
	TaskSystem_RefreshList(tasksysteminfo);

}

//タスクを追加する
void TaskSystem_AddTask(TaskSystemInfo *tasksysteminfo, TaskInfo *taskinfo)
{
	taskinfo->Add_or_DeletionNext = tasksysteminfo->AddTaskList;
	tasksysteminfo->AddTaskList = taskinfo;

	//タスクの処理が実行中でなかったら、直ちに反映
	if (!tasksysteminfo->Run)
	{
		TaskSystem_RefreshList(tasksysteminfo);
	}
}

//タスクの削除
void TaskSystem_DeletionTask(TaskSystemInfo *tasksysteminfo, TaskInfo *taskinfo)
{
	TaskInfo *templateinfo;

	if (taskinfo->Add_or_DeletionNext != NULL)
	{
		if (tasksysteminfo->AddTaskList == taskinfo)
		{
			tasksysteminfo->AddTaskList = taskinfo->Add_or_DeletionNext;
		}
		else
		{
			templateinfo = tasksysteminfo->AddTaskList;
			while (true)
			{
				if (templateinfo->Add_or_DeletionNext == NULL)
				{
					return;
				}

				if (templateinfo->Add_or_DeletionNext == taskinfo)
				{
					templateinfo->Add_or_DeletionNext = taskinfo->Add_or_DeletionNext;
					break;
				}

				templateinfo = templateinfo->Add_or_DeletionNext;
			}
		}

		if (taskinfo->Base->Terminate != NULL)
		{
			taskinfo->Base->Terminate(taskinfo);
		}

		taskinfo->Add_or_DeletionNext = NULL;

		if (taskinfo->Data != NULL)
		{
			free(taskinfo->Data);
		}
	}
	else
	{
		taskinfo->Add_or_DeletionNext = tasksysteminfo->DeletionTaskList;
		tasksysteminfo->DeletionTaskList = taskinfo;

		if (!tasksysteminfo->Run)
		{
			TaskSystem_RefreshList(tasksysteminfo);
		}
	}

}