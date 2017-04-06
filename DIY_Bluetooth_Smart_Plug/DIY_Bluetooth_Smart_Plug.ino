#include <math.h>

const int statusled =6; //green led
const int flash=4;      //blue led
int relay=7;            //relay on pin7

byte input;

void setup()
{
  Serial.begin(9600); 
  pinMode(statusled, OUTPUT);
  pinMode(relay,OUTPUT);
  pinMode(flash,OUTPUT);
 digitalWrite(13,HIGH);
}

void loop()
{
  
if (Serial.available() > 0) 
{
  input = Serial.read();
  //Serial.println(input);
}

 if(input== 0) 
 {                                 //OFF
     digitalWrite(statusled, HIGH);  
     digitalWrite(flash, HIGH);
     digitalWrite(relay, LOW);
 }
 else if (input == 1)
 {//ON
     digitalWrite(statusled, LOW);
     digitalWrite(flash, HIGH);
     digitalWrite(relay, HIGH); 
 }

temp();
  
}



double ThermistorC(int RawADC)
{
 double Temp;
 Temp = log(10000.0*((1024.0/RawADC-1))); 
 Temp = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * Temp * Temp ))* Temp );
 Temp = Temp - 273.15;          
return Temp;
}



void temp()
{
  int valC;                
  double tempC;
  int celsius;     
  valC=analogRead(5);      
  tempC=ThermistorC(valC); 
  //Serial.print("Temperature = ");
   Serial.print(tempC);  
  Serial.println(" C");
  delay(800); 

   if((tempC>45)&&(digitalRead(relay)== HIGH))   //Set your own threshold
   {
    blueflash();
    }

}

void blueflash()
{
  digitalWrite(flash,HIGH);
  digitalWrite(statusled,HIGH);
  delay(300);
  digitalWrite(flash,LOW);
  digitalWrite(statusled,HIGH);
  delay(300);
}


