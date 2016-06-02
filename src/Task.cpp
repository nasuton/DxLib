#include "Task.h"
#include <string.h>
#include <malloc.h>

//�ǉ���폜�𔽉f����
static void TaskSystem_RefreshList(TaskSystemInfo *tasksysteminfo)
{
	TaskInfo *taskinfo;
	TaskInfo *nextinfo;
	TaskInfo *templateinfo;

	//�o�^����Ă�^�X�N���A�^�X�N���X�g�ɒǉ�����
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

	//�o�^����Ă���^�X�N���A�^�X�N���X�g����폜����
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

//��Ԑ��ڂ����s
bool TaskSystem_Step(TaskSystemInfo *tasksysteminfo, float StepTime)
{
	TaskInfo *taskinfo;
	
	//�������s�t���O���utrue�v��
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

	//�������s�t���O���ufalse�v��
	tasksysteminfo->Run = false;

	//�^�X�N�̓o�^��폜�����X�g�֔��f
	TaskSystem_RefreshList(tasksysteminfo);

	//����I��
	return true;
}

//�`�揈�������s
void TaskSystem_Render(TaskSystemInfo *tasksysteminfo)
{
	TaskInfo *taskinfo;

	//�������s�t���Oނ��utrue�v��
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

	//�������s�t���O���ufalse�v��
	tasksysteminfo->Run = false;

	//�^�X�N�̓o�^��폜�����X�g�֔��f
	TaskSystem_RefreshList(tasksysteminfo);

}

//�^�X�N��ǉ�����
void TaskSystem_AddTask(TaskSystemInfo *tasksysteminfo, TaskInfo *taskinfo)
{
	taskinfo->Add_or_DeletionNext = tasksysteminfo->AddTaskList;
	tasksysteminfo->AddTaskList = taskinfo;

	//�^�X�N�̏��������s���łȂ�������A�����ɔ��f
	if (!tasksysteminfo->Run)
	{
		TaskSystem_RefreshList(tasksysteminfo);
	}
}

//�^�X�N�̍폜
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