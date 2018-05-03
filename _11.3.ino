#define RS 10
#define R1 9
#define R2 8
#define L1 7
#define L2 6
#define LS 11
#define sensor1 A1
#define sensor2 A2
#define sensor3 A3
#define sensor4 A4
#define sensor5 A5
#define MAX_SPEED 255 //từ 0-255
#define MIN_SPEED 0
//float ls = 0, rs = 0;
float a = 2;
int b = 40;
float Kp = 9, Ki = 0.00072, Kd = 22.2;
float error = 0, P = 0, I = 0, D = 0, PID_value=0;
float previous_error = 0;
int sensor[5] = {0, 0, 0, 0, 0};
int ims =105; // initial motor speed
void setup() {
pinMode(LS, OUTPUT);
pinMode(L1, OUTPUT);
pinMode(L2, OUTPUT);
pinMode(R1, OUTPUT);
pinMode(R2, OUTPUT);
pinMode(RS, OUTPUT);
//pinMode(sensor1, INPUT);
//pinMode(sensor2, INPUT);
//pinMode(sensor3, INPUT);
//pinMode(sensor4, INPUT);
//pinMode(sensor5, INPUT);
//Serial.begin(9600);
}

void loop() {
  read_sensor_values();
  calculate_pid();
  motor_control();
  delay(14);
}

void read_sensor_values()
{
  sensor[0]=digitalRead(sensor1);
  sensor[1]=digitalRead(sensor2);
  sensor[2]=digitalRead(sensor3);
  sensor[3]=digitalRead(sensor4);
  sensor[4]=digitalRead(sensor5);
  
  if(((sensor[0]==0)&&(sensor[1]==0)&&(sensor[2]==0)&&(sensor[3]==0)&&(sensor[4]==1))) // 00001 
  error = 2*a;//4
  else if(((sensor[0]==0)&&(sensor[1]==0)&&(sensor[2]==0)&&(sensor[3]==1)&&(sensor[4]==1))) // 00011
   error = 1.5*a;//3
  else if((sensor[0]==0)&&(sensor[1]==0)&&(sensor[2]==1)&&(sensor[3]==1)&&(sensor[4]==1)) // 00111
  error=1*a;
   else if((sensor[0]==0)&&(sensor[1]==1)&&(sensor[2]==1)&&(sensor[3]==1)&&(sensor[4]==1)) // 01111
  error=0.5*a; 
  else if((sensor[0]==0)&&(sensor[1]==0)&&(sensor[2]==1)&&(sensor[3]==1)&&(sensor[4]==0)) // 00110
   error < 0 ? -5 : 0.3333333*a;
  else if((sensor[0]==0)&&(sensor[1]==0)&&(sensor[2]==0)&&(sensor[3]==1)&&(sensor[4]==0)) // 00010
   error = 0.25*a;
  else if(((sensor[0]==0)&&(sensor[1]==0)&&(sensor[2]==1)&&(sensor[3]==0)&&(sensor[4]==0)) // 00100 11111 01110
  ||((sensor[0]==1)&&(sensor[1]==1)&&(sensor[2]==1)&&(sensor[3]==1)&&(sensor[4]==1)))
//  ||((sensor[0]==0)&&(sensor[1]==1)&&(sensor[2]==1)&&(sensor[3]==1)&&(sensor[4]==0)))
  error=0;
  else if((sensor[0]==0)&&(sensor[1]==1)&&(sensor[2]==0)&&(sensor[3]==0)&&(sensor[4]==0)) // 01000
  error = -0.25*a;
  else if((sensor[0]==0)&&(sensor[1]==1)&&(sensor[2]==1)&&(sensor[3]==0)&&(sensor[4]==0)) // 01100
  error > 0 ? 5 : -0.3333333*a;
  else if((sensor[0]==1)&&(sensor[1]==1)&&(sensor[2]==1)&&(sensor[3]==1)&&(sensor[4]==0)) // 11110
  error=-0.5*a;
  else if((sensor[0]==1)&&(sensor[1]==1)&&(sensor[2]==1)&&(sensor[3]==0)&&(sensor[4]==0)) // 11100
  error=-1*a;
  else if(((sensor[0]==1)&&(sensor[1]==1)&&(sensor[2]==0)&&(sensor[3]==0)&&(sensor[4]==0))) // 11000
  error = -1.5*a;
  else if((sensor[0]==1)&&(sensor[1]==0)&&(sensor[2]==0)&&(sensor[3]==0)&&(sensor[4]==0)) // 10000
  error = -2*a;//2
  else if((sensor[0]==0)&&(sensor[1]==0)&&(sensor[2]==0)&&(sensor[3]==0)&&(sensor[4]==0)){
    if(error < 0) 
      error=-2.5*a;
    else if ( error > 0)
      error=2.5*a;
      else error = 0;
    }
//  Serial.println(error);
}

void calculate_pid()
{
    P = error;
    I += Ki*error;
    D = error-previous_error;
    
    PID_value = (Kp*P) + (Ki*I) + (Kd*D);
    
    previous_error=error;
    
//    Serial.println(PID_value);
}

void motor_control()
{  
   float ls, rs; 
   if(PID_value > ims) {PID_value = ims;}
   if(PID_value < (-ims)) {PID_value = (-ims);}

   if(PID_value < 0){ 
    ls = ims + abs(int(PID_value));
    rs = ims - abs(int(PID_value));
   }
   else {
    ls = ims - PID_value;
    rs = ims + PID_value;
   }
   
   if(error == 5 || error == 1 || error == 2 ){
     ls += b;
     rs -= b;
     digitalWrite(L1,LOW);
     digitalWrite(L2,HIGH);
     digitalWrite(R1,HIGH);
     digitalWrite(R2,LOW);
   }
   else if (error == -5 || error == -1 || error == -2){
     rs += b;
     ls -= b;
     digitalWrite(L1,HIGH);
     digitalWrite(L2,LOW);
     digitalWrite(R1,LOW);
     digitalWrite(R2,HIGH);
   } else{
//    ls += 80;
//    rs += 80;
     digitalWrite(L1,HIGH);
     digitalWrite(L2,LOW);
     digitalWrite(R1,HIGH);
     digitalWrite(R2,LOW);
   }
//   ls= ims - PID_value;
   if(ls<0) ls = 0 ;
//   if (ls > MAX_SPEED) ls = MAX_SPEED;
//   rs= ims + PID_value;
   if(rs<0) rs = 0;
//   if (rs > MAX_SPEED) rs = MAX_SPEED;
   rs += 5;
//   constrain(ls,MIN_SPEED, MAX_SPEED);
//   constrain(rs,MIN_SPEED, MAX_SPEED);
    if (ls > 255) ls = 255;
    if (rs > 255) rs = 255;
//    Serial.print("Motor speed left = :");
//    Serial.println(ls);
//    Serial.print("Motor speed right = :");
//    Serial.println(rs);
//    for(int i=0;i<10;i++) Serial.println();
   analogWrite(LS, ls);
   analogWrite(RS, rs);
  
//   digitalWrite(L1,HIGH);
//   digitalWrite(L2,LOW);
//   digitalWrite(R1,HIGH);
//   digitalWrite(R2,LOW);
}
