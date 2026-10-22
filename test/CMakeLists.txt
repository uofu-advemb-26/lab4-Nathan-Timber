add_executable(testSignal ../src/signaling.c test_signal.c unity_config.c)

target_link_libraries(testSignal PRIVATE
  pico_stdlib
  pico_async_context_freertos
  FreeRTOS-Kernel-Heap4
  unity
)

# The CYW43 is the Wifi/Bluetooth module. If the board is set to pico_w, this
# variable will be set and the wireless libraries added.
if(PICO_CYW43_SUPPORTED)
    target_link_libraries(testSignal PRIVATE
        pico_cyw43_arch_none
    )
endif()

# Modify the below lines to enable/disable output over UART/USB.
# These are mutually exclusive, only set one.
pico_enable_stdio_uart(testSignal 1)
pico_enable_stdio_usb(testSignal 0)

add_executable(testFifo ../src/fifo.c test_fifo.c unity_config.c)

target_link_libraries(testFifo PRIVATE
  pico_stdlib
  pico_async_context_freertos
  FreeRTOS-Kernel-Heap4
  unity
)

# The CYW43 is the Wifi/Bluetooth module. If the board is set to pico_w, this
# variable will be set and the wireless libraries added.
if(PICO_CYW43_SUPPORTED)
    target_link_libraries(testFifo PRIVATE
        pico_cyw43_arch_none
    )
endif()

# Modify the below lines to enable/disable output over UART/USB.
# These are mutually exclusive, only set one.
pico_enable_stdio_uart(testFifo 1)
pico_enable_stdio_usb(testFifo 0)

find_program(OPENOCD openocd)
find_program(PICOTOOL picotool)

add_custom_target(flash_test_fifo ${PICOTOOL} load -f $<TARGET_FILE:testFifo> DEPENDS testFifo)
add_custom_target(openocd_test_fifo ${OPENOCD} -s ${OPENOCD_PATH} -f interface/cmsis-dap.cfg -f target/rp2040.cfg -c 'adapter speed 5000' -c 'program "$<TARGET_FILE:testFifo>" verify reset exit' DEPENDS testFifo)

add_custom_target(flash_test_signal ${PICOTOOL} load -f $<TARGET_FILE:testSignal> DEPENDS testSignal)
add_custom_target(openocd_test_signal ${OPENOCD} -s ${OPENOCD_PATH} -f interface/cmsis-dap.cfg -f target/rp2040.cfg -c 'adapter speed 5000' -c 'program "$<TARGET_FILE:testSignal>" verify reset exit' DEPENDS testSignal)

