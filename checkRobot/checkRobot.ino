#define RS 10
#define R1 9
#define R2 8
#define L1 7
#define L2 6
#define LS 5
#define sensor1 A1
#define sensor2 A2
#define sensor3 A3
#define sensor4 A4
#define sensor5 A5
#define MAX__speed 255 //từ 0-255
#define MIN__speed 0

void setup() {
pinMode(LS, OUTPUT);
pinMode(L1, OUTPUT);
pinMode(L2, OUTPUT);
pinMode(R1, OUTPUT);
pinMode(R2, OUTPUT);
pinMode(RS, OUTPUT);
pinMode(sensor1, INPUT);
pinMode(sensor2, INPUT);
pinMode(sensor3, INPUT);
pinMode(sensor4, INPUT);
pinMode(sensor5, INPUT);
Serial.begin(9600);
}

void loop(){
forwards(100);

} 
 
void forwards(int _speed){
   _speed = constrain(_speed, MIN__speed, MAX__speed);
   analogWrite(LS, _speed+5);
   digitalWrite(L1,HIGH);
   digitalWrite(L2,LOW);
   analogWrite(RS,_speed);
   digitalWrite(R1,HIGH);
   digitalWrite(R2,LOW);
}

void backwards(int _speed){
  _speed = constrain(_speed, MIN__speed, MAX__speed);
  analogWrite(LS, _speed);
  digitalWrite(L1,LOW);
  digitalWrite(L2,HIGH);
  analogWrite(RS,_speed);
  digitalWrite(R1,LOW);
  digitalWrite(R2,HIGH);
  delay(5000);
}

void left(int _speed){
  _speed = constrain(_speed, MIN__speed, MAX__speed);
  analogWrite(LS, _speed);
  digitalWrite(L1,LOW);
  digitalWrite(L2,LOW);
  analogWrite(RS,_speed);
  digitalWrite(R1,HIGH);
  digitalWrite(R2,LOW);
  delay(5000);
}

void right(int _speed){
  _speed = constrain(_speed, MIN__speed, MAX__speed);
  analogWrite(LS, _speed);
  digitalWrite(L1,HIGH);
  digitalWrite(L2,LOW);
  analogWrite(RS,_speed);
  digitalWrite(R1,LOW);
  digitalWrite(R2,LOW);
  delay(10000);
}
