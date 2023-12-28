//constants
const int motor_pin_one = 13;
const int motor_pin_two = 12;
const int front_ultrasonic = 6;
const int back_ultrasonic = 7;
const int front_ultrasonic_echo = 5;
const int back_ultrasonic_echo = 4;
const int alert_pin = 3;
const int trig_delay = 5; //ms
const int light_pin_one = 11;
const int light_pin_two = 10;

void setup()
{
    Serial.begin(9600);
    Serial.println("Divice On");
    pinMode(motor_pin_one,OUTPUT);
    pinMode(motor_pin_two,OUTPUT);
    pinMode(alert_pin, OUTPUT);
    pinMode(light_pin_one, OUTPUT);
    pinMode(light_pin_two, OUTPUT);
}

void loop()
{
  long duration;
  float cm;
  
  // sensor sending out pulse
  pinMode(front_ultrasonic, OUTPUT); 
  digitalWrite(front_ultrasonic, LOW);
  delayMicroseconds(10);
  digitalWrite(front_ultrasonic, HIGH);
  delayMicroseconds(trig_delay);  
  digitalWrite(front_ultrasonic, LOW);
  
  //measure pulse time in PW mode
  pinMode(front_ultrasonic_echo, INPUT);
  duration = pulseIn(front_ultrasonic_echo, HIGH);
  
  //time to distance 
  cm = duration / 58.8;
  Serial.print(cm);
  Serial.println("cm");
  
  
  if (cm >= 50) {
  digitalWrite(motor_pin_one, LOW); //motor full speed
  digitalWrite(motor_pin_two, HIGH);
  digitalWrite(alert_pin,LOW);
  digitalWrite(light_pin_one, HIGH);
  digitalWrite(light_pin_two, HIGH);
  delay(500);
  digitalWrite(light_pin_one, LOW);
  digitalWrite(light_pin_two, LOW);
  delay(500);
  
  }
  if ((cm < 50)&&(cm > 15)) {
  digitalWrite(motor_pin_one, LOW); 
  digitalWrite(motor_pin_two, HIGH); // motor partial speed
  delay(40);
  digitalWrite(motor_pin_one, LOW); 
  digitalWrite(motor_pin_two, LOW);
  delay(1);
  digitalWrite(alert_pin,LOW);
  digitalWrite(light_pin_one, HIGH);
  digitalWrite(light_pin_two, HIGH);
  delay(500);
  digitalWrite(light_pin_one, LOW);
  digitalWrite(light_pin_two, LOW);
  delay(500);
  }
  
  if ((cm > 0)&&(cm <= 15)) {
    digitalWrite(motor_pin_one, LOW); 
    digitalWrite(motor_pin_two, LOW); // motor off
    digitalWrite(alert_pin,HIGH);
    digitalWrite(light_pin_one,HIGH);
    digitalWrite(light_pin_two,HIGH);
    Serial.print("Alert");
    delay(25000);
    digitalWrite(alert_pin,LOW);
    digitalWrite(light_pin_one,LOW);
    digitalWrite(light_pin_two,LOW);
    do{
      loop_two();
    } while ((cm > 0)&&(cm <= 15));
  }
} 

void loop_two()
{
    long duration;
  float cm_return;
  
  // sensor sending out pulse
  pinMode(back_ultrasonic, OUTPUT); 
  digitalWrite(back_ultrasonic, LOW);
  delayMicroseconds(10);
  digitalWrite(back_ultrasonic, HIGH);
  delayMicroseconds(trig_delay);  
  digitalWrite(back_ultrasonic, LOW);
  
  //measure pulse time in PW mode
  pinMode(back_ultrasonic_echo, INPUT);
  duration = pulseIn(back_ultrasonic_echo, HIGH);
  
  //time to distance 
  cm_return = duration / 58.8;
  Serial.print(cm_return);
  Serial.println("cm return");
  
  if (cm_return >= 50) {
  digitalWrite(motor_pin_one, HIGH); //motor full speed
  digitalWrite(motor_pin_two, LOW);
  digitalWrite(alert_pin,LOW);
  digitalWrite(light_pin_one, HIGH);
  digitalWrite(light_pin_two, HIGH);
  delay(500);
  digitalWrite(light_pin_one, LOW);
  digitalWrite(light_pin_two, LOW);
  delay(500);
  }
  
  if ((cm_return < 50)&&(cm_return > 15)) {
  digitalWrite(motor_pin_one, HIGH); 
  digitalWrite(motor_pin_two, LOW); // motor partial speed
  delay(40);
  digitalWrite(motor_pin_one, LOW); 
  digitalWrite(motor_pin_two, LOW);
  delay(1);
  digitalWrite(alert_pin,LOW);
  digitalWrite(light_pin_one, HIGH);
  digitalWrite(light_pin_two, HIGH);
  delay(500);
  digitalWrite(light_pin_one, LOW);
  digitalWrite(light_pin_two, LOW);
  delay(500);
  }

  if ((cm_return > 0)&&(cm_return <= 15)) {
    digitalWrite(motor_pin_one, LOW); 
    digitalWrite(motor_pin_two, LOW); // motor off
    digitalWrite(alert_pin,HIGH);
    digitalWrite(light_pin_one,HIGH);
    digitalWrite(light_pin_two,HIGH);
    Serial.print("Alert");
    delay(3000);
    digitalWrite(alert_pin,LOW);
    digitalWrite(light_pin_one,LOW);
    digitalWrite(light_pin_two,LOW);
    for(;;){/*empty*/}
    }
}
