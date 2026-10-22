#pragma once
#include <FreeRTOS.h>
#include <semphr.h>
#include <signaling.h>

BaseType_t signal_request_calculate(SemaphoreHandle_t request,
                                    SemaphoreHandle_t response,
                                    struct signal_data *data) {

  xSemaphoreGive(request);
  return xSemaphoreTake(response, 100);
}

void signal_handle_calculation(SemaphoreHandle_t request,
                               SemaphoreHandle_t response,
                               struct signal_data *data) {

  xSemaphoreTake(request, portMAX_DELAY);
  data->output = data->input + 5;
  xSemaphoreGive(response);
}
