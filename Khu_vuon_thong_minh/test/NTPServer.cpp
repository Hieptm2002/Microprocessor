#include <WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

// Replace with your network credentials
// RTC_DATA_ATTR const char* ssid     = "Tang 3";
// RTC_DATA_ATTR const char* password = "khongcho6666";

RTC_DATA_ATTR const char* ssid     = "kvtm23";
RTC_DATA_ATTR const char* password = "11111111";

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

// Variables to save time
String formattedTime;
int pre_hour = 0;
int Hour;
int Minute;
int Second;

void setup_NTP() {
  // Initialize Serial Monitor
  Serial.begin(115200);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  // Initialize a NTPClient to get time
  timeClient.begin();
  timeClient.setTimeOffset(+7*60*60);
}

void getTime() {

  if (!timeClient.update()) {
    timeClient.forceUpdate();
  }
  // The formattedTime comes with the following format:
  // 16:00:13
  // We need to extract time
  formattedTime = timeClient.getFormattedTime();

  Hour = (formattedTime.substring(0, 2)).toInt();
  Minute = (formattedTime.substring(3, 5)).toInt();
  Second = (formattedTime.substring(6)).toInt();
  // in ra serial để kiểm tra
  if (Hour != pre_hour) {
  Serial.print("Thoi gian hien tai: ");
  Serial.print(Hour) ;
  Serial.print(":");
  Serial.print(Minute);
  Serial.print(":");
  Serial.println(Second);
  pre_hour = Hour;
  }
  delay(200);
}