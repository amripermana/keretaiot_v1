#include <esp32-hal-timer.h>
#include <Arduino.h>

extern TaskHandle_t Task1, Task2;
extern hw_timer_t *timerCore0;
extern hw_timer_t *timerCore1;
extern int iteration_1_sec;
extern int iteration_1_ms;
extern int iteration_1000_ms_core1;
extern int iteration_1_ms_core1;
extern int iteration_100_ms;

void init_timer0();
void init_timer1();
void init_dualcore();
void Core0(void * parameter);
void Core1(void * parameter);
void onTimerCore0();
void onTimerCore1();