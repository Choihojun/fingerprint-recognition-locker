#include<Servo.h>
#include <SoftwareSerial.h>

Servo myservo;
int pos =100;
void setup() {

  Serial.begin(9600);
    Serial.println("servo test");
  myservo.attach(13);
  
  // put your setup code here, to run once:

}

void loop() {
  for(pos=100;pos<165;pos +=1)
    {    
        myservo.write(pos);
      Serial.println(pos);
       delay(30);
    }
   for(pos=165;pos>=100;pos-=1)
   {
    myservo.write(pos);
    Serial.println(pos);
       delay(30);
   }
  // put your main code here, to run repeatedly:

}
