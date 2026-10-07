#pragma once
#include <FreeRTOS.h>
#include <semphr.h>
#include <signaling.h>

void signal_handle_calculation(SemaphoreHandle_t request,
                               SemaphoreHandle_t response,
                               struct signal_data *data) {
}
