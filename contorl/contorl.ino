// include the library code:
#include <LiquidCrystal.h>
#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>
#include<Servo.h>


// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
SoftwareSerial mySerial(2, 3);
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

///////////////////////////////////////////
uint8_t id;
uint8_t getFingerprintEnroll();           //등록
//////////////////////////////////////////////

//---------------------------모터
Servo myservo;
int pos = 165;
//------------------------------

int key = 0;


//------------------------------------등록
uint8_t readnumber(void) {
  uint8_t num = 0;
  boolean validnum = false; 
  while (1) {
    while (! Serial.available());
    char c = Serial.read();
    if (isdigit(c)) {
       num *= 10;
       num += c - '0';
       validnum = true;
    } else if (validnum) {
      return num;
    }
  }
}
////////////////////////////////////////////


int getFingerprintIDez();                 //아이디 가져오기





void setup() {
  myservo.attach(13);           //열림 100  닫힘  165
 while (!Serial);  // For Yun/Leo/Micro/Zero/...
  Serial.begin(9600);
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.setCursor(0,0);
  lcd.print("Default - Box");
  lcd.setCursor(0,1);
  lcd.print(" Wait for moment ");

  pinMode(11,OUTPUT); // LED green
  pinMode(12,OUTPUT); // LED red

  lcd.clear();
  
  finger.begin(57600);
   if (finger.verifyPassword()) {
    lcd.setCursor(0,0);
    lcd.print("Default - Box");
    lcd.setCursor(0,1);
    lcd.print("Found F.P sensor");
    delay(1000);
  } else {
    lcd.setCursor(0,0);
    lcd.print("Default - Box");
    lcd.setCursor(0,1);
    delay(2000);
    lcd.print("no F.P sensor");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("please connect");
    lcd.setCursor(0,1);
    lcd.print("finger sensor");
    while (1);
  }
 // Serial.println("Waiting for valid finger...");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Default - Box");
    lcd.setCursor(0,1);
    lcd.print("Put valid finger");
    
}
//----------------------------------------------------------------------------------------
void loop() {
  while(key==0 && pos >=100)
  {
  getFingerprintIDez();
  
  digitalWrite(11,HIGH);   //green
  digitalWrite(12,LOW);    //red
  
  //if(key==1 && pos > 160)
   // break;
  }
  pos = pos +6;
  //key = 1;
  while(key==1 && pos >= 165)
  {
  getFingerprintIDez();
  
   digitalWrite(12,HIGH);   //green
   digitalWrite(11,LOW);    //red
   //if(key==0)
    //break;
  }
  //key=0;  
/*
  if(key == 0 && pos ==100 && finger.confidence<100 )
  {
  getFingerprintIDez();
  digitalWrite(11,HIGH);   //green
  digitalWrite(12,LOW);    //red
  }// 닫힘

  key
  if(key == 1 && pos ==165 && finger.confidence>100)
  {
     getFingerprintIDez();
     digitalWrite(11,LOW);   //green
     digitalWrite(12,HIGH);    //red
  }//열림
  */
 
}
//---------------------------------------------------------------------------------------

//----------------------------- 지문 센서 (아래)--------------------------------------
uint8_t getFingerprintID() {
  uint8_t p = finger.getImage();
  switch (p) {
    case FINGERPRINT_OK:
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Default - Box");
    lcd.setCursor(0,1);
    lcd.print("Image taken");
      //Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
       lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("Default - Box");
       lcd.setCursor(0,1);
       lcd.print("No finger exist");
   //   Serial.println("No finger exist");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
       lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("Default - Box");
       lcd.setCursor(0,1);
       lcd.print("communi err");
    //  Serial.println("Communication error");
      return p;
    case FINGERPRINT_IMAGEFAIL:
       lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("Default - Box");
       lcd.setCursor(0,1);
       lcd.print("imaging error");
   //   Serial.println("Imaging error");
      return p;
    default:
       lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("Default - Box");
       lcd.setCursor(0,1);
       lcd.print("unknown error");
     // Serial.println("Unknown error");
      return p;
  }

  // OK success!

  p = finger.image2Tz();
  switch (p) {
    case FINGERPRINT_OK:
       lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("Default - Box");
       lcd.setCursor(0,1);
       lcd.print("imag converted");
     // Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
       lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("Default - Box");
       lcd.setCursor(0,1);
       lcd.print("imag too messy");
      //Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
       lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("Default - Box");
       lcd.setCursor(0,1);
       lcd.print("communi err");
     // Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
       lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("could not find");
       lcd.setCursor(0,1);
       lcd.print("fingerprint feat");
    //  Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
       lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("could not find");
       lcd.setCursor(0,1);
       lcd.print("fingerprint feat");
     // Serial.println("Could not find fingerprint features");
      return p;
    default:
       lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("Default - Box");
       lcd.setCursor(0,1);
       lcd.print("Unknown error");
    //  Serial.println("Unknown error");
      return p;
  }
  
  // OK converted!
  p = finger.fingerFastSearch();
  if (p == FINGERPRINT_OK) {
       lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("Found a print");
       lcd.setCursor(0,1);
       lcd.print("Match !");
    //Serial.println("Found a print match!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
       lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("Communication");
       lcd.setCursor(0,1);
       lcd.print("error");
    //Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_NOTFOUND) {
       lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("Did not find ");
       lcd.setCursor(0,1);
       lcd.print("a match");
    //Serial.println("Did not find a match");
    return p;
  } else {
       lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("Unknown");
       lcd.setCursor(0,1);
       lcd.print("error");
   // Serial.println("Unknown error");
    return p;
  }   
  
  // found a match!
       lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("Found ID # "); 
       lcd.setCursor(12,0);
       lcd.print(finger.fingerID);
       lcd.setCursor(0,1);
       lcd.print("confi = ");
       lcd.setCursor(9,1);
       lcd.print(finger.confidence);
       
 // Serial.print("Found ID #"); Serial.print(finger.fingerID); 
 // Serial.print(" with confidence of "); Serial.println(finger.confidence); 
}

// returns -1 if failed, otherwise returns ID #
int getFingerprintIDez() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  return -1;

  digitalWrite(12,LOW);
  digitalWrite(11,HIGH);
  delay(1000);
  digitalWrite(11,LOW);
  delay(1000);
  digitalWrite(12,HIGH);
  
  
  // found a match!
       lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("Found ID # "); 
       lcd.setCursor(12,0);
       lcd.print(finger.fingerID);
       lcd.setCursor(0,1);
       lcd.print("confi = ");
       lcd.setCursor(9,1);
       lcd.print(finger.confidence);
  //Serial.print("Found ID #"); Serial.print(finger.fingerID); 
  //Serial.print(" with confidence of "); Serial.println(finger.confidence);
  if(finger.confidence > 70 && pos>=100 && key==0  )
  { 
   for(pos=100;pos<=165;pos+=1)
   {
    myservo.write(pos);
       delay(15);
   }
       lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("Default - box ");
       lcd.setCursor(0,1);
       lcd.print("close...");
   key=1;
   
  }
  pos = pos -3;
 // finger.confidence =0;
  if(finger.confidence > 70 && pos >=165)
  { 
   for(pos=165;pos>=100;pos-=1)
   {
    myservo.write(pos);
       delay(15);
   }
       lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("Default - box ");
       lcd.setCursor(0,1);
       lcd.print("open...");
  key=0;
  pos = 100;
  }
  
  
  //digitalWrite(12,LOW);
  //digitalWrite(11,HIGH);
  
  
  return finger.fingerID; 
}
//----------------------------- 지문 센서 (위) --------------------------------------



/*
//------------------------------ 등록 ( 아래) --------------------------------------
 uint8_t getFingerprintEnroll() {

  int p = -1;
  int x = 0;
  Serial.print("Waiting for valid finger to enroll as #"); Serial.println(id);
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    switch (p) {
    case FINGERPRINT_OK:
       lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("Default "); 
       lcd.setCursor(0,1);
       lcd.print("image taken ");
      //Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
       x ++;
       lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("Default "); 
       lcd.setCursor(x,1);
       lcd.print(". ");
      //Serial.println(".");
      break;
    case FINGERPRINT_PACKETRECIEVEERR:
       lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("Default "); 
       lcd.setCursor(0,1);
       lcd.print("Communi err ");
     // Serial.println("Communication error");
      break;
    case FINGERPRINT_IMAGEFAIL:
       lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("Default "); 
       lcd.setCursor(0,1);
       lcd.print("imaging err ");
     // Serial.println("Imaging error");
      break;
    default:
       lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("Default "); 
       lcd.setCursor(0,1);
       lcd.print("unknown err ");
     //Serial.println("Unknown error");
      break;
    }
  }

  // OK success!

  p = finger.image2Tz(1);
 
   
  switch (p) {
    case FINGERPRINT_OK:
       lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("Default "); 
       lcd.setCursor(0,1);
       lcd.print("img converted");
     // Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
       lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("Default "); 
       lcd.setCursor(0,1);
       lcd.print("img too messy");
 //     Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
       lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("Default "); 
       lcd.setCursor(0,1);
       lcd.print("commnica err");
    // Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
       lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("Default "); 
       lcd.setCursor(0,1);
       lcd.print("could not find ft");
     // Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
       lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("Default "); 
       lcd.setCursor(0,1);
       lcd.print("could not find ft");
      //Serial.println("Could not find fingerprint features");
      return p;
    default:
      lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("Default "); 
       lcd.setCursor(0,1);
       lcd.print("inknown err");
    //  Serial.println("Unknown error");
      return p;
  }

       lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("Default "); 
       lcd.setCursor(0,1);
       lcd.print("remove finger");
  //Serial.println("Remove finger");
  delay(2000);
  p = 0;
  while (p != FINGERPRINT_NOFINGER) {
    p = finger.getImage();
  }
       lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("Default "); 
       lcd.setCursor(10,0);
       lcd.print("ID ");
       lcd.setCursor(13,0);
       lcd.print(id);
       
  //Serial.print("ID "); Serial.println(id);
  p = -1;
       lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("Default "); 
       lcd.setCursor(0,1);
       lcd.print("put same finger");
 // Serial.println("Place same finger again");
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    switch (p) {
    case FINGERPRINT_OK:
       lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("Default "); 
       lcd.setCursor(0,1);
       lcd.print("img taken");
     // Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
       lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("Default "); 
       lcd.setCursor(0,1);
       lcd.print(".");
      //Serial.print(".");
      break;
    case FINGERPRINT_PACKETRECIEVEERR:
       lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("Default "); 
       lcd.setCursor(0,1);
       lcd.print("communic err");
     // Serial.println("Communication error");
      break;
    case FINGERPRINT_IMAGEFAIL:
           lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("Default "); 
       lcd.setCursor(0,1);
       lcd.print("img err");
      //Serial.println("Imaging error");
      break;
    default:
           lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("Default "); 
       lcd.setCursor(0,1);
       lcd.print("unknown err");
      //Serial.println("Unknown error");
      break;
    }
  }

  // OK success!

  p = finger.image2Tz(2);
  switch (p) {
    case FINGERPRINT_OK:
           lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("Default "); 
       lcd.setCursor(0,1);
       lcd.print("img converted");
    //  Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
           lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("Default "); 
       lcd.setCursor(0,1);
       lcd.print("img too messy");
   //   Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
           lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("Default "); 
       lcd.setCursor(0,1);
       lcd.print("communi err");
   //   Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
           lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("Default "); 
       lcd.setCursor(0,1);
       lcd.print("no finger feat");
    //  Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
           lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("Default "); 
       lcd.setCursor(0,1);
       lcd.print("no finger feat");
   //   Serial.println("Could not find fingerprint features");
      return p;
    default:
           lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("Default "); 
       lcd.setCursor(0,1);
       lcd.print("Unknown err");
      //Serial.println("Unknown error");
      return p;
  }
  
  // OK converted!
         lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("Creat mod "); 
       lcd.setCursor(0,1);
       lcd.print("for #");
       lcd.setCursor(7,1);
       lcd.print(id);
//  Serial.print("Creating model for #");  Serial.println(id);
  
  p = finger.createModel();
  
  //Serial.print("finger.createModel() = ");
  //Serial.println(p);
  
  if (p == FINGERPRINT_OK) {

      // OK converted!
                 lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("Default "); 
       lcd.setCursor(0,1);
       lcd.print("Prints match");
 //   Serial.println("Prints matched!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
                   lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("Default "); 
       lcd.setCursor(0,1);
       lcd.print("communi err");
    //Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_ENROLLMISMATCH) {
                   lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("Default "); 
       lcd.setCursor(0,1);
       lcd.print("not match");
    //Serial.println("Fingerprints did not match");
    return p;
  } else {
                   lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("Default "); 
       lcd.setCursor(0,1);
       lcd.print("Unknown err");
    
  //  Serial.println("Unknown error");
    return p;
  }   
                 lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("Default "); 
       lcd.setCursor(0,1);
       lcd.print("ID");
       lcd.setCursor(4,1);
       lcd.print(id);
       delay(3000);
  
//  Serial.print("ID "); Serial.println(id);
  p = finger.storeModel(id);
  if (p == FINGERPRINT_OK) {
                   lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("Default "); 
       lcd.setCursor(0,1);
       lcd.print("Stored");
   // Serial.println("Stored!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
                       lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("Default "); 
       lcd.setCursor(0,1);
       lcd.print("Communi err");

   // Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_BADLOCATION) {
                       lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("Default "); 
       lcd.setCursor(0,1);
       lcd.print("try to find pla");
  //  Serial.println("Could not store in that location");
    return p;
  } else if (p == FINGERPRINT_FLASHERR) {
                       lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("Default "); 
       lcd.setCursor(0,1);
       lcd.print("err to flash");
 //   Serial.println("Error writing to flash");
    return p;
  } else {
                       lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("Default "); 
       lcd.setCursor(0,1);
       lcd.print("Unknown err");
  //  Serial.println("Unknown error");
    return p;
  }   
}

//--------------------------- 등록 (위) -------------------------

*/





 /*
  int x;
  x = analogRead (0); // 버튼 아날로그 0번.
  lcd.setCursor(10,1);
  if (x < 60) {
    lcd.print ("Right ");
  }
  else if (x < 200) {
    lcd.print ("Up    ");
  }
  else if (x < 400){
    lcd.print ("Down  ");
  }
  else if (x < 600){
    lcd.print ("Left  ");
  }
  else if (x < 800){
    lcd.print ("Select");
  }*/
