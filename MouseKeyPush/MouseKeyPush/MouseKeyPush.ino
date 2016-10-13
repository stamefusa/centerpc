#include <Servo.h>

#define MOUSE 1
#define KEY 2
#define FRONT 3
#define BACK 4
#define STOP 9

int val1 = 0, pre1 = 0, diff1 = 0, pdiff1 = 0;
int val2 = 0, pre2 = 0, diff2 = 0, pdiff2 = 0;
boolean switch1 = false, switch2 = false;
boolean rotate = true; // true:正転 false:逆転
int threshold = 800;
int gyaku_start = 0, jun_start = 0, start_time = 0;
int mode = STOP;
 
char str;

Servo servo;

void setup() {
  servo.attach(7);
  servo.write(90);

  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  Serial.begin(9600);
  
}

void loop() {
  if(Serial.available() > 0){
    //データの読み込み
    //str = Serial.readStringUntil('\r');
    str = Serial.read();
    Serial.println(str);
    if (str == 'a') {
      mode = KEY;  
      jun_start = millis();
    } else if (str == 'b') {
      mode = MOUSE;
    } else if (str == 'c') {
      mode = STOP;
    } else if (str == 'w') {
      mode = FRONT;
    } else if (str == 'e') {
      mode = BACK;
    }
    start_time = millis();
  }

  if (mode == KEY) {
    switch1 = isSwitch1();
    switch2 = isSwitch2();
    Serial.println(rotate);

    // モータ駆動
    driveMotor(rotate);

    // 一定時間正転したら逆転
    //if (rotate == true && millis() - jun_start > 1000) {
    if (rotate == true && switch1 == true) {
      rotate = false;
      gyaku_start = millis();
      Serial.println("Reverse.");
    // スイッチがオンになったら停止
    //} else if (rotate == false && millis() - gyaku_start > 1000) {
    } else if (rotate == false && switch2 == true) {
      rotate = true;
      jun_start = millis();
      Serial.println("Seiten.");
    }

    
  } else if (mode == MOUSE) {
    stopMotor();
    driveServo();
    
  } else if (mode == FRONT) {
    driveMotor(true);
    
  } else if (mode == BACK) {
    driveMotor(false);
    
  } else {
    stopMotor();
    stopServo();
  }

  delay(100);

  if (millis() - start_time > 3000) {
    Serial.println("auto stop.");
    mode = STOP;
  }
}

void driveServo()
{
  servo.write(80);
  delay(500);
  servo.write(100);
  delay(500);
}

void stopServo()
{
  servo.write(90);
}

void stopMotor()
{
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    analogWrite(6, 0);
    rotate = true;
}

void driveMotor(boolean flag)
{
  if(flag == true) {
    digitalWrite(4, HIGH);
    digitalWrite(5, LOW);
  } 
  else {
    digitalWrite(4, LOW);
    digitalWrite(5, HIGH);
  }

  analogWrite(6, 200);
}

boolean isSwitch1()
{ 
  boolean dst = false;

  val1 = analogRead(0);

  /*
  diff1 = val1 - pre1;
  if (diff1 > threshold && pdiff1 < threshold) {
    Serial.println("switch1 on!!");
    dst = true;
  }
  pre1 = val1;
  pdiff1 = diff1;
  */
  if (val1 > threshold) {
    Serial.println("switch1 on!!");
    dst = true;
  }

  return dst;
}

boolean isSwitch2()
{
  boolean dst = false;
  
  val2 = analogRead(1);
  /*
  diff2 = val2 - pre2;
  if (diff2 > threshold && pdiff2 < threshold) {
    Serial.println("switch2 on!!");
    dst = true;
  }
  pre2 = val2;
  pdiff2 = diff2;
  */
  
  if (val2 > threshold) {
    Serial.println("switch1 on!!");
    dst = true;
  }

  return dst;
}
