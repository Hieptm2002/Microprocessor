#include <OneWire.h>
#include <DallasTemperature.h>
 
#define ONE_WIRE_BUS 0          // Cài đặt chân GPIO sử dụng đọc dữ dệu
#define source_DS 4 
int value_temp = 0;
/*
* Thiết đặt thư viện onewire
* Tạo thuộc tính sử dụng giao tiếp onewire ở chân GPIO số 0
*/
OneWire oneWire(ONE_WIRE_BUS);
/* Liên kết thuộc tính với thư viện DallasTemperature để sử dụng đọc cảm biến */
DallasTemperature sensors(&oneWire);

void setup_DS18B20() {
  pinMode(source_DS,OUTPUT); 
  digitalWrite(source_DS, HIGH);
  OneWire oneWire(ONE_WIRE_BUS);
  DallasTemperature sensors(&oneWire);
  Serial.begin(115200);
  sensors.begin(); // Bắt đầu đọc cảm biến
}

// Tắt cảm biến
void OFF_DS18B20() {
  if(digitalRead(source_DS)){
    digitalWrite(source_DS, LOW);
    delay(500);
  }
} 

// Bật cảm biến
void ON_DS18B20() {
  if(!digitalRead(source_DS)){
    digitalWrite(source_DS, HIGH);
  }
    // Yêu cầu thông tin từ cảm biến
    sensors.requestTemperatures(); 
    // Lấy giá trị nhiệt độ của cảm biến. 

    // Sửa lỗi trả về giá trị - 127 khi chạy cả hệ thống
    do {
      value_temp = sensors.getTempCByIndex(0);
    }
    while (value_temp < 0);
    Serial.print("Nhiet do: ");
    Serial.println(value_temp); 
    // thời gian lấy mẫu khoảng 750ms (datasheet)
    delay(750);
}