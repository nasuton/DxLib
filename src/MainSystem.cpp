#include "Title_Task.h"
#include "MainSystem.h"

//�V�X�e�����
typedef struct _SystemInfo 
{
	//���ڂ��鎞��
	float StepTime;

	//�������s����
	int StepNum;

	//�I���t���O
	bool ExitGame;

	//�Q�[���J�n���̃X�e�[�W
	int StartStage;

	//�^�X�N�V�X�e�����
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

//�^�X�N�V�X�e�����\���̂̃A�h���X���擾
TaskSystemInfo *System_GetTaskSystemInfo()
{
	return &_SystemInfo._TaskSysteminfo;
}