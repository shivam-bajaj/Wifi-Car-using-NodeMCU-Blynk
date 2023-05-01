

#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "";
char pass[] = "";
int f,r,l,b;
int relay1=14,relay2=12,relay3=13;
int led1=16,led2=2,led_s;
int ir_b,ir_edge =5 ,ir_obstacle=4,st_e,st_o;
boolean check=false,go=true;
WidgetLCD lcd(V4);
void setup()
{
  // Debug console
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);
  pinMode(relay1,OUTPUT);
  pinMode(relay2,OUTPUT);
  pinMode(relay3,OUTPUT);
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(ir_edge,INPUT);
  pinMode(ir_obstacle,INPUT);
  digitalWrite(relay1,HIGH);
  digitalWrite(relay2,HIGH);
  digitalWrite(relay3,HIGH);
}

int car(int i){
  switch(i){
    case 0:
    digitalWrite(relay1,HIGH);
    digitalWrite(relay2,HIGH);
    digitalWrite(relay3,HIGH);
    lcd.clear();
    lcd.print(2,0,"Stop");
    go=false;

    break;

    case 1:
    digitalWrite(relay1,LOW);
    digitalWrite(relay2,LOW);
    digitalWrite(relay3,HIGH);
    lcd.clear();
    lcd.print(1,0,"Move Forward");
    go=true;
    break;

    case 2:
    digitalWrite(relay1,HIGH);
    digitalWrite(relay2,LOW);
    digitalWrite(relay3,HIGH);
    lcd.clear();
    lcd.print(2,0,"Turn Right");
    go=true;
    break;


    case 3:
    digitalWrite(relay1,LOW);
    digitalWrite(relay2,HIGH);
    digitalWrite(relay3,HIGH);
    lcd.clear();
    lcd.print(2,0,"Turn Left");
    go=true;
    break;

    case  4:
    digitalWrite(relay1,HIGH);
    digitalWrite(relay2,HIGH);
    digitalWrite(relay3,LOW);
    lcd.clear();
    lcd.print(1,0,"Step Backward");
    go=false;
    break;

    case 5 :
    digitalWrite(relay1,HIGH);
    digitalWrite(relay2,HIGH);
    digitalWrite(relay3,HIGH);
    lcd.clear();
    lcd.print(0,0,"kaha ja raha h ");
    go = false;
    break;

    case 6 :
    digitalWrite(relay1,HIGH);
    digitalWrite(relay2,HIGH);
    digitalWrite(relay3,HIGH);
    lcd.clear();
    lcd.print(2,0,"Obstacle ahead");
    go = false;
    break;

    case 7:
    digitalWrite(relay1,HIGH);
    digitalWrite(relay2,HIGH);
    digitalWrite(relay3,HIGH);
    lcd.clear();
    lcd.print(2,0,"both");
    go=false;
    break;

    default:
    lcd.clear();
    lcd.print(4,0,"404");
    break;
   }


}
BLYNK_WRITE(V0) //Button Widget is writing to pin V1
{
  f = param.asInt();
  if(f ==1){
    car(1);
  }
  else{
    car(0);
  }
}
BLYNK_WRITE(V1){
  r = param.asInt();
  if(r ==1){
    car(2);
  }
  else{
    car(0);
  }
}
BLYNK_WRITE(V2){
  l = param.asInt();
  if(l ==1){
    car(3);
  }
  else{
    car(0);
  }
 }
BLYNK_WRITE(V3){
  b = param.asInt();
  if(b ==1){
    car(4);
  }
  else{
    car(0);
  }
}

BLYNK_WRITE(V5){
 led_s = param.asInt();
 if( led_s == 1){
  digitalWrite(led1,HIGH);
  digitalWrite(led2,HIGH);
 }
 else{
  digitalWrite(led1,LOW);
  digitalWrite(led2,LOW);
 }
}

BLYNK_WRITE(V6){
  ir_b = param.asInt();
  if ( ir_b  == 1){
    check=true;
    Serial.println("check/button app on");
  }
  else{
    check=false;
    Serial.println("check/button app off");
  }
}



void loop()
{
  Blynk.run();
  if((check==true )&& (go ==true)){
    Serial.println("\ in loop");
    // write if condition statements and take one more boolean to stop in this statement
    st_e = digitalRead(ir_edge);
    st_o = digitalRead(ir_obstacle);
    if ( st_e == 1 && st_o ==1){
      car(5);
      Serial.println("/n edge");
    }
    if ( st_e == 0 && st_o == 0){
      car(6);
      Serial.println("/n obstacle");
    }
    if (st_e == 1 && st_o == 0){
      car(7);
      Serial.println("/n both");
    }
  }
}
