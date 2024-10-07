#include <Servo.h>

int pos = 0;  //변수 pos를 정수로 선언

Servo myservo;  //서보모터의 이름을 'myservo'로 지정

void setup()
{
  myservo.attach(9);  //9번 핀으로 서보모터 지정
}

void loop()
{
  for (pos = 0; pos <= 180; pos += 5) {  //pos변수 호출, 조건만큼 반속 실행 
    myservo.write(pos);  //반복하는 값을 서보모터의 각도로 입력

    delay(30); 
  }
  for (pos = 180; pos >= 0; pos -= 5) {  //pos변수 호출, 조건만큼 반속 실행 
    myservo.write(pos);  //반복하는 값을 서보모터의 각도로 입력
   
    delay(30); 
  }
}