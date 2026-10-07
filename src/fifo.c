#pragma once
#include <FreeRTOS.h>
#include <fifo.h>

void fifo_worker_handler(QueueHandle_t requests, QueueHandle_t results,
                         int id) {
  struct request_msg msg;

  while (1) {
    xQueueReceive(requests, (void *)(&msg), portMAX_DELAY);

    msg.output = msg.input + 5;
    msg.handled_by = id;

    xQueueSend(results, &msg, portMAX_DELAY);
  }
}