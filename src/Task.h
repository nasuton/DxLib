#pragma once

#define TASK_MAX (16)

 //��{���
typedef struct _TaskBaseInfo
{
	//��Ԑ��ڏ����̎��s�D�揇��
	int StepPriority;

	//�`�揈���̎��s�D�揇��
	int RenderPriority;

	//��Ԑ��ڏ���
	bool(*Step)(struct _TaskInfo *taskinfo, float StepTime);

	//�`�揈��
	void(*Render)(struct _TaskInfo *taskinfo);

	//��n������
	void(*Terminate)(struct _TaskInfo *taskinfo);

}TaskBaseInfo;

//�^�X�N�̏��
typedef struct _TaskInfo
{
	TaskBaseInfo* Base;

	void* Data;

	struct _TaskInfo* StepNext;

	struct _TaskInfo* RenderNext;

	struct _TaskInfo* Add_or_DeletionNext;
}TaskInfo;

//�^�X�N�V�X�e�����
typedef struct _TaskSystemInfo
{
	bool Run;

	TaskInfo* StepTask[TASK_MAX];

	TaskInfo* RenderTask[TASK_MAX];

	TaskInfo* AddTaskList;

	TaskInfo* DeletionTaskList;
}TaskSystemInfo;

//��Ԑ��ڏ��������s����
extern bool TaskSystem_Step(TaskSystemInfo *tasksysteminfo, float StepTime);

//�`�揈�������s����
extern void TaskSystem_Render(TaskSystemInfo *tasksysteminfo);

//�^�X�N��ǉ�����
extern void TaskSystem_AddTask(TaskSystemInfo *tasksysteminfo, TaskInfo *taskinfo);

//�^�X�N���폜����
extern void TaskSystem_DeletionTask(TaskSystemInfo *tasksysteminfo, TaskInfo *taskinfo);