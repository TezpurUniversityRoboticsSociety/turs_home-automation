/*
* Bluetooh Basic: LED ON OFF - Avishkar
* Coder - Mayoogh Girish
* Website - http://bit.do/Avishkar
* Download the App : https://github.com/Mayoogh/Arduino-Bluetooth-Basic
* This program lets you to control a LED on pin 13 of arduino using a bluetooth module
*/
#define LIGHT1 2
#define LIGHT2 4
#define FAN1 3
#define FAN2 5
#define LDR A0
#define TEMP A1

char data;            //Variable for storing received data
int tempval,lightval;
int x=0;
void setup()
{
    Serial.begin(9600);   //Sets the baud for serial data transmission                               
    pinMode(LIGHT1, OUTPUT);  //Relay1-light
    pinMode(FAN1, OUTPUT);//Relay2-fan
    pinMode(LIGHT2, OUTPUT);//Relay3-light
    pinMode(FAN2, OUTPUT);//Relay4-fan
    digitalWrite(LIGHT1,HIGH);
    digitalWrite(FAN1,HIGH);
    digitalWrite(LIGHT2,HIGH);
    digitalWrite(FAN2,HIGH);
}
void loop()
{
    tempval = analogRead(TEMP);
    lightval= analogRead(LDR);
    float mv = ( tempval/1024.0)*4720; 
    float cel = mv/10;

     if(Serial.available() > 0)      // Send data only when you receive data:
     {
        data = Serial.read();        //Read the incoming data & store into data
        Serial.print(data);          //Print Value inside data in Serial monitor
        Serial.print("\n");        
        if(data == 'a')              
           digitalWrite(LIGHT1, LOW); 
             
        else if(data == 'A')         
           digitalWrite(LIGHT1, HIGH);  
           
        if(data == 'b')              
           digitalWrite(FAN1, LOW);
        
        else if(data == 'B')          
           digitalWrite(FAN1, HIGH);
            
        if(data == 'c')              
           digitalWrite(LIGHT2, LOW);   
        
        else if(data == 'C')         
           digitalWrite(LIGHT2, HIGH);
            
        if(data == 'd')              
           digitalWrite(FAN2, LOW);   
        
        else if(data == 'D')         
           digitalWrite(FAN2, HIGH);
  
        if(data=='e')
          x=1;
        
        else if(data=='E')
          x=0;
     }
    Serial.print("TEMPRATURE = "); Serial.print(cel); Serial.print("*C"); Serial.println();
    if (x==1)
    {
        Serial.print("ON AUTO");
        if(lightval<800)
        {
          digitalWrite(LIGHT1, HIGH);
          digitalWrite(LIGHT2, HIGH);
        }
        else if(lightval>850)
        {
          digitalWrite(LIGHT1, LOW);
          digitalWrite(LIGHT2, LOW);
        }
        if(cel>25)
        {
          digitalWrite(FAN1, HIGH);
          digitalWrite(FAN2, HIGH);
        }
        if(cel<24.5)
        {
          digitalWrite(FAN1, LOW);
          digitalWrite(FAN2, LOW);
        }
           
    }
    Serial.print("LIGHT VALUE= "); Serial.println(lightval);    
    delay(250);
}
