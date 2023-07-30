#include <SoftwareSerial.h>
#include <SPI.h> 
#include <MFRC522.h>

SoftwareSerial bluetooth(2, 3);
const byte kirmizi=A3,yesil=A4,mavi=A5; //RGB PİNLERİ
const byte tus1=4,tus2=5,tus3=6,tus4=7;
MFRC522 rfid(10, 9);//RFID Chip Select ve Reset pinlerinin ayarlarını yapıyoruz. 
byte Kart[4] = {179,147,101,166}; // {53, 122, 201, 226} buraya kendi okuttuğunuz kartın ID numarasını yazmalısınız. 
char sifre[4] = {0,0,0,0};
int c=0;
boolean Yetki;


void rgbled(int r){
  switch(r)
  {
  case 1:
    analogWrite(kirmizi,255);
    analogWrite(mavi,0);
    analogWrite(yesil,0);
    break; 
  case 2:
    analogWrite(kirmizi,0);
    analogWrite(mavi,255);
    analogWrite(yesil,0);
    break;
  case 3:
    analogWrite(kirmizi,0);
    analogWrite(mavi,0);
    analogWrite(yesil,255);
    break;
  case 4:
    analogWrite(kirmizi,0);
    analogWrite(mavi,0);
    analogWrite(yesil,0);
    break;
  default:
    analogWrite(kirmizi,0);
    analogWrite(mavi,0);
    analogWrite(yesil,0);
    break;
  }
}

void setup() {
  pinMode(kirmizi, OUTPUT);
  pinMode(yesil, OUTPUT);
  pinMode(mavi, OUTPUT);
  pinMode(tus1, INPUT_PULLUP);
  pinMode(tus2, INPUT_PULLUP);
  pinMode(tus3, INPUT_PULLUP);
  pinMode(tus4, INPUT_PULLUP);
  Serial.begin(9600);
  bluetooth.begin(9600);
  SPI.begin();
  rfid.PCD_Init();
  rgbled(1);
}

void checkPassword() 
{
  if(digitalRead(tus1)||digitalRead(tus2)||digitalRead(tus3)||digitalRead(tus4))
  {
    if(digitalRead(tus1)){Serial.println("1");sifre[c]=1;c++;ledblink();delay(250);if(c>=4){c=0;checkPassword2(sifre);}}
    if(digitalRead(tus2)){Serial.println("2");sifre[c]=2;c++;ledblink();delay(250);if(c>=4){c=0;checkPassword2(sifre);}}
    if(digitalRead(tus3)){Serial.println("3");sifre[c]=3;c++;ledblink();delay(250);if(c>=4){c=0;checkPassword2(sifre);}}
    if(digitalRead(tus4)){Serial.println("4");sifre[c]=4;c++;ledblink();delay(250);if(c>=4){c=0;checkPassword2(sifre);}}
}

}
void checkPassword2(char s[4]) 
{
  if(s[0]==3&&s[1]==2&&s[2]==1&&s[3]==4){Serial.println("Şifre Doğru");led5sn();}
  else{Serial.println("Şifre Yanlış");ledblink();ledblink();}
}


void loop() {
  blu();
  readCard();
  checkPassword(); 
}

void blu(){
 if (bluetooth.available()) 
 {
    char input = bluetooth.read();
    if (input=='a') {
      led5sn();
      Serial.print(input); 
    }
    
  }
}

void readCard() {
   Yetki = true;
   if ( rfid.PICC_IsNewCardPresent())
  {
    if ( rfid.PICC_ReadCardSerial())
      { Serial.print("Okunan Kart ID: ");
        Serial.print(rfid.uid.uidByte[0]); 
        Serial.print(",");
        Serial.print(rfid.uid.uidByte[1]); 
        Serial.print(","); 
        Serial.print(rfid.uid.uidByte[2]); 
        Serial.print(","); 
        Serial.println(rfid.uid.uidByte[3]);
      }  
      for (int i = 0; i < 4; i++) 
      {
        if (rfid.uid.uidByte[i] != Kart[i])
        {
          Yetki = false;
        }
      } 
      if (Yetki == true) 
      { 
        Serial.println("Yetki Onaylandi…");
        bluetooth.println("Yetki Onaylandi…");
        led3sn();
      } 
      else 
      {
        Serial.println("Yetki Onaylanmadi…");
        bluetooth.println("Yetki Onaylanmadi…");
        ledblink();
        
      } 
      rfid.PICC_HaltA(); 
  }
}
void led3sn(){
        rgbled(2);
        delay(1000);
        Serial.println("Kilit Açık 1...");
        bluetooth.println("Kilit Açık 1...");
        delay(1000);
        Serial.println("Kilit Açık 2...");
        bluetooth.println("Kilit Açık 2...");
        delay(1000);
        Serial.println("Kilit Kapalı 3...");
        bluetooth.println("Kilit Kapalı 3...");
        rgbled(1); 
}
void led5sn(){
    rgbled(3);
    Serial.println("Şifre Doğru");
    delay(1000);
    Serial.println("Kilit Açık 1...");
    bluetooth.println("Kilit Açık 1...");
    delay(1000);
    Serial.println("Kilit Açık 2...");
    bluetooth.println("Kilit Açık 2...");
    delay(1000);
    Serial.println("Kilit Açık 3...");
    bluetooth.println("Kilit Açık 3...");
    delay(1000);
    Serial.println("Kilit Açık 4...");
    bluetooth.println("Kilit Açık 4...");
    delay(1000);
    Serial.println("Kilit Kapalı 5...");
    bluetooth.println("Kilit Kapalı 5...");
    rgbled(1);
}
void ledblink(){
  rgbled(1);
  delay(100);
  rgbled(4);
  delay(100);
  rgbled(1);
}