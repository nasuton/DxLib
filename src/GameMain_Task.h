#pragma once
#include "Task.h"

extern TaskInfo *Task_GameMain_Start();

//ゲームメインに敵を倒したことを伝える
extern void Task_GameMain_AddKillEnemy(TaskInfo *taskinfo, int CharaNo);