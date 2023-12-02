

#define BLYNK_TEMPLATE_ID "TMPL3m8thMvb1"
#define BLYNK_TEMPLATE_NAME "Car robot"
#define BLYNK_AUTH_TOKEN "CBmxGQ54faCF1dZgAlFzbYiAqzxl7CPT"

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h> //download and add library blynk master
#include <BlynkSimpleEsp8266.h>



#include<Servo.h>


// Define the motor pins
#define ENA D0
#define IN1 D1 //motor 1 
#define IN2 D2 //motor 2
#define IN3 D3 //motor 3
#define IN4 D4 //motor 4
#define ENB D5

#define metal D7 //Analogpin metal driver
#define buzzer D8

Servo servo;

char auth[] = "CBmxGQ54faCF1dZgAlFzbYiAqzxl7CPT"; //Enter your Blynk auth token
char ssid[] = "iQOO Neo7"; //Enter your WIFI name
char pass[] = "123456789v"; //Enter your WIFI passowrd
int x = 50;
int y = 50;
int Speed=255;
int start=0;
int angle=90;

//make blynk account and create 4 datastream V0 for x of joystick

BLYNK_WRITE(V0) {
  x = param[0].asInt();
}

//V1 for Y of joystick
BLYNK_WRITE(V1) {
  y = param[0].asInt();
}
//V2 for Speed of joystick
BLYNK_WRITE(V2) {
  Speed = param.asInt();
}
//v3 for start automatic run
BLYNK_WRITE(V3) {
  start = param.asInt();
}

BLYNK_WRITE(V4) {
  angle = param.asInt();
}


void setup() {
  Serial.begin(9600);

  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);
   pinMode(metal, INPUT);
  pinMode(buzzer, OUTPUT);
  servo.attach(D6);
  servo.write(90);

//  pinMode(trigPin,OUTPUT);
//  pinMode(trigPin,INPUT);
//  
  //Serial.print("CarForward");
  //carForward();

  Blynk.begin(auth, ssid, pass);
}

void smartcar() {
if (y > 70) {
    carForward();
    Serial.println("carForward");
  } else if (y < 30) {
    carBackward();
    Serial.println("carBackward");
  } else if (x < 30) {
    carLeft();
    Serial.println("carLeft");
  } else if (x > 70) {
    carRight();
    Serial.println("carRight");
  } else if (x < 70 && x > 30 && y < 70 && y > 30) {
    carStop();
    Serial.println("carstop");
  }
}
void loop() {
    
    Blynk.run();
    if(start==1){
      carForward();
    }else{
    smartcar();
    }
    if(digitalRead(metal)==HIGH){
      Serial.print("1");
      digitalWrite(buzzer,HIGH);
      delay(100);
    }else{
      Serial.print("0");
      digitalWrite(buzzer,LOW);
    }
    
    servo.write(angle);
    delay(2000);
}

/**************Motor movement functions*****************/
void carForward() {
  analogWrite(ENA, Speed);
  analogWrite(ENB, Speed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

}
void carBackward() {
 analogWrite(ENA, Speed);
  analogWrite(ENB, Speed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

}
void carLeft() {
 
   analogWrite(ENA, Speed);
  analogWrite(ENB, Speed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  

}
void carRight() {
  


  analogWrite(ENA, Speed);
  analogWrite(ENB, Speed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

}
void carStop() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
