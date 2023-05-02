#include <Servo.h>

// Define input/output pins and variables
const int in = 2, out = 3, buzz = 4, led = 5;
int temp = 0; // Temperature variable
int count = 0; // Count variable for 'lift' command
String a = ""; // String variable for reading serial input

// Declare four servo objects
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;

void setup() 
{
  // Initialize serial communication and set pin modes
  Serial.begin(9600);
  pinMode(in, INPUT);
  pinMode(out, INPUT);
  pinMode(buzz, OUTPUT);
  pinMode(led, OUTPUT);
  
  // Attach servo objects to their respective pins and move servos to 180 degrees
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
  // Print the current temperature to serial monitor and wait for 1 second
  Serial.println(temp);
  delay(1000);
  
  // If the 'in' sensor is triggered, increment the temperature by 1 and wait for 2 seconds
  if (digitalRead(in) == 0) 
  { 
    temp = temp + 1;
    delay(2000);
  }
  // If the 'out' sensor is triggered, decrement the temperature by 1, but do not allow the temperature to go below 0
  else if (digitalRead(out) == 0) 
  {
    temp = temp - 1;
    if (temp < 0) 
    {
      temp = 0;
    }
    delay(2000);
  }
  
  // Read incoming serial data and store it in string variable 'a'
  while (Serial.available()) 
  {
    a = Serial.readString();
  }
  
  // If the string received over serial is "lift"
  if (a == "lift") 
  {
    // If count is less than 5, turn off the buzzer and LED and increment count by 1
    if (count < 5) 
    {
      digitalWrite(buzz, LOW);
      digitalWrite(led, LOW);
      count += 1;
      delay(1000);
    }
    // If count is 5 or greater, turn on the buzzer and LED for 10 seconds and move all servos to 0 degrees
    else if (count >= 5) 
    {
      digitalWrite(buzz, HIGH);
      digitalWrite(led, HIGH);
      delay(10000);
      servo1.write(0);
      servo2.write(0);
      servo3.write(0);
      servo4.write(0);
    }
  }
}
