// #include <PCA9685.h>

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm=Adafruit_PWMServoDriver();

void setup() {
  Serial.begin(9600);
  pwm.begin();
  pwm.setPWMFreq(51); //오작동 한다면 50Hz에서 조금씩 바꿔보기 
}

void loop() {
  int a = Serial.parseInt(); //시리얼 통신으로 값을 받아옴
  
  if (Serial.available()) {
    
    int ra = constrain(map(a, 0, 180, 150, 600), 150, 600); //받은 값의 범위 0~180을 펄스길이150~600으로 매핑해주고, ra의 최소,최대를 150,600을 넘지 않게 해준다.

    pwm.setPWM(1,0,5); //pca9685모듈의 0번 포트에 연결된 서보를 ra만큼 회전
    
    Serial.print('(');
    Serial.print(a);
    Serial.print(',');
    Serial.print(ra);
    Serial.println(')');
    delay(10);
  }
}