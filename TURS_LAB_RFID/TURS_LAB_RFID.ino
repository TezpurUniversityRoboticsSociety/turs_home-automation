// include the library code:
#include <LiquidCrystal.h>
#include <RFID.h>
#include <Servo.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 7, en = 6, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

Servo servo;
/*
* Read a card using a mfrc522 reader on your SPI interface
* Pin layout should be as follows (on Arduino Uno):
* MOSI: Pin 11 / ICSP-4
* MISO: Pin 12 / ICSP-1
* SCK: Pin 13 / ISCP-3
* SS/SDA: Pin 10
* RST: Pin 9
*/

#include <SPI.h>
#include <RFID.h>

#define SS_PIN 10
#define RST_PIN 9
#define BUTTON A0
#define DOOR A1

RFID rfid(SS_PIN,RST_PIN);


int serNum[5];
int cards[][5] = {
  {105,181,231,228,223} 
};

bool access = false;
int door;
int handle;
int o=1;
void setup(){
    Serial.begin(9600);
    Serial.print("started");
    SPI.begin();
    rfid.init(); 
    servo.attach(8);
    servo.write(3);
    pinMode(DOOR,INPUT);
    pinMode(BUTTON,INPUT);
    lcd.begin(16, 2);
    lcd.display();       
}

void loop(){
    door=digitalRead(DOOR);
    handle=digitalRead(BUTTON);
    lcd.setCursor(0,0);
    lcd.scrollDisplayLeft();
    delay(300);
    lcd.print("TEZPUR UNIVERSITY ROBOTICS SOCIETY LAB");

    if(rfid.isCard())
    {
    
        if(rfid.readCardSerial())
        {
              Serial.print(rfid.serNum[0]);
              Serial.print(" ");
              Serial.print(rfid.serNum[1]);
              Serial.print(" ");
              Serial.print(rfid.serNum[2]);
              Serial.print(" ");
              Serial.print(rfid.serNum[3]);
              Serial.print(" ");
              Serial.print(rfid.serNum[4]);
              Serial.println(" ");
              
              for(int x = 0; x < sizeof(cards); x++)
              {
                  for(int i = 0; i < sizeof(rfid.serNum); i++ )
                  {
                      if(rfid.serNum[i] != cards[x][i]) {
                          access = false;
                          break;
                      } 
                      else {
                          access = true;
                      }
                  }
                  if(access) 
                      break;
              } 
        }
        
        if(access==true){
            Serial.println("Welcome!");
            
            lcd.setCursor(0,1);
            lcd.print("Welcome");
            
            servo.write(150);
            delay(3000);
            o=1;
        }
    }
    if(door==1 && o==1) 
    {
         delay(500);
         door=digitalRead(DOOR);
         if(door==1)
         {
            Serial.println("Locked!");
            
            lcd.setCursor(0,1);
            lcd.print("Locked");
             
            servo.write(3);
            o=0;
         }
     }
     if(handle==1 && o==0)
     {
        Serial.println("Unlocked!");
        
        lcd.setCursor(0,1);
        lcd.print("Unlocked");
        
        servo.write(150);
        o=1;
        delay(3000);
     }
      rfid.halt();
      Serial.print(handle);        
      Serial.println(door);
      delay(100);

}



