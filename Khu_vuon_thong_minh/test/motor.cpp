// Motor A
#define motor1 27 

void setup_motor() {
  // sets the pins as outputs:
  pinMode(motor1, OUTPUT);    
  Serial.begin(115200);
}
 // Tắt motor
void OFF_motor() {
  if(digitalRead(motor1)){
    Serial.println("Motor stopped");
    digitalWrite(motor1, LOW); 
    delay(200);
  }
}
 
// Bật motor
void ON_motor() {
  // Move the DC motor forward at maximum speed
  if(!digitalRead(motor1)){
    Serial.println("Run DC Motor...");
    digitalWrite(motor1, HIGH); 
    delay(200);
  }
}
