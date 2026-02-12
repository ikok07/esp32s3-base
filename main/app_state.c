//
// Created by Kok on 2/12/26.
//

#include "app_state.h"

TIMER_HandleTypeDef htim;
APP_Tasks tasks;

APP_State gAppState = {
    .htim = &htim,
    .Tasks = &tasks
};