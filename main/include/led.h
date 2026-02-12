//
// Created by Kok on 2/12/26.
//

#ifndef ESP32S3_LED_H
#define ESP32S3_LED_H

#define LED_PIN                 (GPIO_NUM_48)

#include "esp_err.h"

esp_err_t LED_Config();
void LED_StartTask();

#endif //ESP32S3_LED_H