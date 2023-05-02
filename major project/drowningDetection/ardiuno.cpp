#include <Servo.h>

const int in=2,out=3,buzz=4,led=5;
int temp=0;
int count = 0;
String a = "";
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;

void setup() 
{
Serial.begin(9600);
pinMode(in,INPUT);
pinMode(out,INPUT);
pinMode(buzz,OUTPUT);
pinMode(led,OUTPUT);
servo1.attach(6);
servo2.attach(9);
servo3.attach(10);
servo4.attach(11);
servo1.write(180);
servo2.write(180);
servo3.write(180);
servo4.write(180);
}

void loop() 
{
Serial.println(temp);
delay(1000);
if(digitalRead(in)==0)
{ 
temp=temp+1;
delay(2000);
}
else if(digitalRead(out)==0)
{
temp=temp-1;
if (temp < 0)
{
temp = 0; 
}
delay(2000);
}
while(Serial.available()) 
{
a = Serial.readString();
}
if (a == "lift")
{
if (count < 5)
{
digitalWrite(buzz,LOW);
digitalWrite(led,LOW);
count += 1;
delay(1000);
}
else if (count >= 5)
{
digitalWrite(buzz,HIGH);
digitalWrite(led,HIGH);
delay(10000);
servo1.write(0);
servo2.write(0);
servo3.write(0);
servo4.write(0);
}
}
}
