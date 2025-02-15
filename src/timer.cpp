#include "timer.h"

int iteration_1_sec = 0;
int iteration_100_ms = 0;
int iteration_1_ms = 0;

int iteration_1000_ms_core1 = 0;
int iteration_1_ms_core1 = 0;

TaskHandle_t Task1, Task2;
hw_timer_t *timerCore0 = NULL;
hw_timer_t *timerCore1 = NULL;

void IRAM_ATTR onTimerCore0() {
  iteration_1_ms = 1;
}

void IRAM_ATTR onTimerCore1() {
  iteration_1_ms_core1 = 1;
}

void init_dualcore(){
    

    xTaskCreatePinnedToCore(
    Core0,
    "TaskCore0",
    10000,
    NULL,
    1,
    &Task1,
    0);
  delay(500);

  xTaskCreatePinnedToCore(
    Core1,
    "TaskCore1",
    10000,
    NULL,
    1,
    &Task2,
    1);
}


void init_timer0(){
    timerCore0 = timerBegin(0, 80, true); // Timer 0, Prescaler 80, Auto Reload true, freq = 80MHz
    timerAttachInterrupt(timerCore0, &onTimerCore0, true);
    timerAlarmWrite(timerCore0, 1000, true); // Atur alarm ke 1 ms 
    timerAlarmEnable(timerCore0); // Enable timer
}

void init_timer1(){
    timerCore1 = timerBegin(1, 80, true); // Timer 1, Prescaler 80, Auto Reload true
    timerAttachInterrupt(timerCore1, &onTimerCore1, true);
    timerAlarmWrite(timerCore1, 1000, true); // Atur alarm ke 1 ms
    timerAlarmEnable(timerCore1); // Enable timer
}


