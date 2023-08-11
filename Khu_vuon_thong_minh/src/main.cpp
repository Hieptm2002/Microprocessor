#include<Arduino.h>
#include"D:\Khu_vuon_thong_minh\test\test_YL100.cpp"
#include"D:\Khu_vuon_thong_minh\test\NTPServer.cpp"
#include"D:\Khu_vuon_thong_minh\test\van_dien_tu.cpp"
#include"D:\Khu_vuon_thong_minh\test\test_DS18B20.cpp"
#include"D:\Khu_vuon_thong_minh\test\motor.cpp"

#define LED_BLUE 17
#define LED_RED 16

// Ngưỡng thời gian theo lịch trình có sẵn
RTC_DATA_ATTR int time_threshold[4] =  {6, 17, 9, 21};

// deep sleep
#define uS_TO_S_FACTOR ((uint64_t) 1000000)

hw_timer_t * timer = NULL;

//count second
RTC_DATA_ATTR int count_second = 0;

bool start_deep_sleep = false;

void onTimer() {
  count_second ++;
}

void setup() {
  Serial.begin(115200);

  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BLUE, OUTPUT);
  pinMode(LED_RED, OUTPUT);

  // setup mode
  setup_NTP();
  setup_YL100();
  setup_van();
  setup_DS18B20();
  setup_motor();

  // setup timer
  timer = timerBegin(0, 80, true);
  timerAttachInterrupt(timer, &onTimer, true);
  timerAlarmWrite(timer, 1000000, true);
  timerAlarmEnable(timer);
  Serial.println("start count second:");
}

// the loop function runs over and over again forever
void loop() {

  // delay sau khi đánh thức esp32 khỏi chế độ deep sleep
  delay(200);

  // đếm thời gian lấy mẫu ổn định (được đánh giá sau khi test)
  if (count_second < 34){
    Serial.print("Thoi gian lay mau chinh xac: ");
    Serial.println(count_second);
  }
  else {timerAlarmDisable(timer);}

  getTime();

  // Chế độ tưới tự động
  if (Hour == time_threshold[0] || Hour == time_threshold[1]) {
    if (count_second < 31) {
      ON_YL100();
    } else {
      ON_YL100();
      if (percent > 80) {
        start_deep_sleep = true;
        if(digitalRead(LED_RED)){
          getTime();
          OFF_van();
          digitalWrite(LED_RED, LOW);
          OFF_YL100();
        }
      } else {
        if(!digitalRead(LED_RED)){
          getTime();
          ON_van();
          digitalWrite(LED_RED, HIGH);
        }
      }
    }
  } else {
      if(digitalRead(LED_RED)){
        getTime();
        OFF_van();
        digitalWrite(LED_RED, LOW);
        OFF_YL100();
      } else {Serial.println("He thong tuoi tat.");}
    }
  delay(200);

  // Chế độ phun sương tự động
  if (Hour > time_threshold[2] && Hour < time_threshold[3]) {
    if (count_second < 5) {
    ON_DS18B20();
    } else {
      ON_DS18B20();
      if (value_temp > 25) {
        if(count_second > 30){
          start_deep_sleep = true;
        }
        if(!digitalRead(LED_BLUE)){
          getTime();
          ON_motor();
          digitalWrite(LED_BLUE, HIGH);
        }
      } else {
        if(digitalRead(LED_BLUE)){
          getTime();
          OFF_motor();
          digitalWrite(LED_BLUE, LOW);
          OFF_DS18B20();
        }
      }
    }
  } else {
      if(digitalRead(LED_BLUE)){
          getTime();
          OFF_motor();
          digitalWrite(LED_BLUE, LOW);
          OFF_DS18B20();
      } else {Serial.println("He thong phun suong tat.");}
    }
  delay(200);

    //chế độ deep sleep
  bool check1 = (Hour == time_threshold[0]);
  bool check2 = (Hour > time_threshold[2] && Hour < time_threshold[3]);

  if (check1 || check2){
    if(start_deep_sleep == true) {
      if(digitalRead(LED_RED) == 0 && digitalRead(LED_BLUE) == 0){
        timerWrite(timer, 0);
        count_second = 0;
        Serial.println("Start deep sleep mode.");
        // GPIO High value during deep sleep mode (van hoạt động ở mức High là đóng van)
        digitalWrite(van1, HIGH);
        gpio_hold_en(GPIO_NUM_26);
        // Lấy giá trị 62 vì sai số sau lần thức dậy đầu khỏi chế độ deep sleep của esp32 khoảng 2 phút
        esp_sleep_enable_timer_wakeup(uint64_t (uint64_t((62 - Minute) * 60) * uS_TO_S_FACTOR)); /* * 60 */
        esp_deep_sleep_start();
      }
    }
  } else {
    timerWrite(timer, 0);
    count_second = 0;
    Serial.println("Start deep sleep mode.");
    // GPIO High value during deep sleep mode
    digitalWrite(van1, HIGH);
    gpio_hold_en(GPIO_NUM_26);

    esp_sleep_enable_timer_wakeup(uint64_t (uint64_t((62 - Minute) * 60) * uS_TO_S_FACTOR));
    esp_deep_sleep_start();
  }
}

