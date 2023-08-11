#define A_YL 34
#define source_yl 32

int percent;
int value_mos;
uint32_t real_value = 0;

void setup_YL100() {
  Serial.begin(115200);                         //Mở cổng Serial ở tốc độ 115200 
  pinMode(source_yl, OUTPUT);                                       
}
 
 // Tắt cảm biến
void OFF_YL100() {
    if(digitalRead(source_yl)){
        digitalWrite(source_yl, LOW);
        delay(200);
    }
}

// Bật cảm biến
void ON_YL100() {
    if(!digitalRead(source_yl)){
      digitalWrite(source_yl, HIGH);
    }
    // Chúng ta sẽ tạo một hàm for để đọc 100 lần giá trị cảm biến, sau đó lấy giá trị trung bình để được giá trị tốt nhất.
    for(int i = 0; i < 100; i++){
      real_value += analogRead(A_YL);
    }
    value_mos = real_value / 100;
    percent = map(value_mos, 1296, 4095, 0, 100);    // Set giá thang giá trị đầu và giá trị cuối để đưa giá trị về thang từ 0-100. 
                                                    // Cái này sẽ bằng thực nghiệm (đã test)
    percent=100-percent;                            // Tính giá trị phần trăm thực. Chuyển điện thế từ 3.3V ( khô ) thành 3.3V ( ẩm )
    Serial.print("Do am: ");
    Serial.print(percent);
    Serial.print("%, Analog: ");
    Serial.println(value_mos);
    real_value = 0;
    delay(1000);
  }