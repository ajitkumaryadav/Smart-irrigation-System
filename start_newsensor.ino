#include<LiquidCrystal.h>
LiquidCrystal lcd(14,13,12,11,10,9);
char inchar,mosture_sensor;
String check_power= "ajityadav";
String check_power1= "motorband";
String power;
String power1;
int led=7;
//int c;
int x;
//int aaaa;
int a=2;
int b=3;
//int led=13;
//int relay=4;
//void mosture();
void stop();
void sensor();

void setup() {
  // put your setup code here, to run once:
  
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(A5,INPUT);
  pinMode(7,OUTPUT);
  // pinMode(13,OUTPUT);
  //pinMode(A0,INPUT);
 // pinMode(relay, OUTPUT);
  Serial.begin(9600); 
  //Serial.println("AT");//to avtivate
  lcd.begin(16,2);
  lcd.cursor();
  lcd.print("WELCOME");
   digitalWrite(2,LOW);
   digitalWrite(3,LOW);
  // digitalWrite(13,LOW);
  // Serial.print("pin state low\n");
  delay(1000); // give time for GSM module to register on network.
  Serial.println("AT");
  delay(2000);
  Serial.println("AT+CSCS=\"GSM\""); // set SMS mode to text
  delay(1000);
  Serial.println("AT+CMGF=1");
  delay(1000);
  Serial.println("AT+CNMI=2,2,0,0,0"); // set module to send SMS data to serial out upon receipt ,to save the message in gsm module
  delay(200);
}

void loop() 
{
 
  // put your main code here, to run repeatedly:
  int i;
  lcd.clear();
  lcd.print("type_message");
  lcd.setCursor(0,1);
   //lcd.print("ajityadav");
  //delay(2000);
  //lcd.clear(); 
     
  if(Serial.available() >0)
  {
    for(x=0;x<360;x++)
    { 
      //lcd.setCursor(0,0);
      //lcd.print("yadavajit");
      //delay(2000); 
      inchar=Serial.read(); 
      
      if (inchar=='#')
      {
         power=Serial.readStringUntil(13);
          lcd.setCursor(0,0);
          lcd.print(power);
          delay(2000);
      
        if(power==check_power )
        {
          sensor(); 
          /*     
          
          */
          Serial.print("AT+CMGD=1,4");//Delete all message
          delay(2000);
          //while(1){;}
           //mosture();
        }
        
        if(power==check_power1)
        {      
          lcd.setCursor(0,1);
          lcd.print("ACCESS MOTOR"); 
          digitalWrite(a, LOW); 
          digitalWrite(b, LOW);
          lcd.setCursor(0,2);
          lcd.print("motor_off");
          
          Serial.println("AT+CMGF=1");
          delay(500);
          Serial.println("AT+CMGS=\"8955563856\"");//Change the receiver phone number,number of gsm
          delay(3000);
          Serial.println("Motor OFF");    //the message you want to send
          Serial.write(26);
          delay(3000);
          Serial.print("AT+CMGD=1,4");//Delete all message
          delay(2000);
          //while(1){;}
           //mosture();
        }
      }
    }
  }
}
 void sensor()
{
  int d =analogRead(A4);
  Serial.print("adc=");
  Serial.println(d);
  delay(1000);
  Serial.println("");
  int leak=digitalRead(A5);
  Serial.print("digitalread=");
  Serial.println(leak);
  Serial.println("");
  delay(1000);
  
  if(leak==0 && d<300)
  {
    digitalWrite(a, LOW); 
     digitalWrite(b, LOW);
    digitalWrite(led, HIGH);
    lcd.setCursor(0,2);
    lcd.print("motor_off");
  Serial.println("AT+CMGF=1");//to type mesage
    delay(2000);
    Serial.println("AT+CMGS=\"8955563856\"");
    delay(2000);
    Serial.println("motor_off");
    Serial.write((char)26); //ctrl+z
    delay(2000);
    Serial.println("AT+CMGD=1,4");//Delete all message
     delay(2000);
  }
  else
  {
      lcd.setCursor(0,1);
          lcd.print("ACCESS MOTOR"); 
          digitalWrite(a, HIGH); 
          digitalWrite(b, LOW);
          lcd.setCursor(0,2);
          lcd.print("motor_on");
          Serial.println("AT+CMGF=1");
          delay(500);
          Serial.println("AT+CMGS=\"8955563856\"");//Change the receiver phone number,number of gsm
          delay(3000);
          Serial.print("Motor ON");    //the message you want to send
          Serial.write(26);
          delay(3000);
          Serial.println("AT+CMGD=1,4");//Delete all message
          delay(2000);
  }
  
  
}

