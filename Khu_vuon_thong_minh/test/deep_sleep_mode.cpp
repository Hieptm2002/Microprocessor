#define uS_TO_S_FACTOR ((uint64_t) 1000000)  /* Conversion factor for micro seconds to seconds */
#define TIME_TO_SLEEP  ((uint64_t) 3600)       /* Time ESP32 will go to sleep (in seconds) */

// hw_timer_t * timer = NULL;
// volatile byte state = LOW;

void IRAM_ATTR onTimer(){ } 

void setup_deep_sleep() {  
    // /* 1 tick take 1/(80MHZ/80) = 1us so we set divider 80 and count up */
    // Serial.begin(115200);
    // timer = timerBegin(0, 80, true);

    // /* Attach onTimer function to our timer */
    // timerAttachInterrupt(timer, &onTimer, true);
    
    //Run this only the first time
    // Serial.print("So gio da ngu: ");
    // Serial.println(gio);
    esp_sleep_enable_timer_wakeup(uint64_t (TIME_TO_SLEEP * uS_TO_S_FACTOR));
    esp_deep_sleep_start();
}