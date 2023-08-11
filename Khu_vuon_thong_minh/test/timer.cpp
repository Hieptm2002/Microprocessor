#include<Arduino.h>

hw_timer_t * timer = NULL;

//count second
RTC_DATA_ATTR int count_second = 0;


void IRAM_ATTR onTimer(){​​​​​​​
  count_second += 1;
}​​​​​​​ 


void setup() {​​​​​​​
  Serial.begin(115200);

  /* Use 1st timer of 4 */
  /* 1 tick take 1/(80MHZ/80) = 1us so we set divider 80 and count up */
  timer = timerBegin(0, 80, true);

  /* Attach onTimer function to our timer */
  timerAttachInterrupt(timer, &onTimer, true);

  /* Set alarm to call onTimer function every second 1 tick is 1us
  => 1 second is 1000000us */
  /* Repeat the alarm (third parameter) */
  timerAlarmWrite(timer, 1000000, true);

  /* Start an alarm */
  timerAlarmEnable(timer);
  Serial.println("start count second:");
}​​​​​​​


void loop() {
    Serial.print("Thoi gian lay mau: ");
    Serial.print(count_second);​​​​​​​
}​​​​​​​
