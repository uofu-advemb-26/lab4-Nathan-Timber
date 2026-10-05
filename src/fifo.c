#pragma once
#include <FreeRTOS.h>
#include <queue.h>

void fifo_worker_handler(QueueHandle_t requests, QueueHandle_t results,
                         int id) {
}