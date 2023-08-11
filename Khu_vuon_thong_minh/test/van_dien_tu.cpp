// Van A
#define van1 26

void setup_van() {
  // sets the pins as outputs:
  pinMode(van1, OUTPUT);  
  digitalWrite(van1, HIGH);  
  Serial.begin(115200);
}

// Tắt van
void OFF_van() {
  Serial.println("van stopped");
  if(!digitalRead(van1)){
    digitalWrite(van1, HIGH);  
    delay(200); 
  }
}

//Bật van
void ON_van() {
  Serial.println("Run DC van...");
  if(digitalRead(van1)){
    digitalWrite(van1, LOW);
    delay(5000);
  } 
}
