//
// Created by Kok on 2/12/26.
//

#include "task_scheduler.h"

void SCHEDULER_Create(SCHEDULER_TaskTypeDef *Task) {
    xTaskCreatePinnedToCore(
        Task->Function,
        Task->Name,
        Task->StackDepth,
        Task->Args,
        Task->Priority,
        &Task->OsTask,
        Task->CoreID
    );
}