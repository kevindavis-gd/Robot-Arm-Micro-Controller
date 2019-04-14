#include <Servo.h>


// create servo object to control a servo
Servo Shoulder_1;
Servo Shoulder_2;
Servo Elbow_1;
Servo Elboy_2;

// variable to store the servo position
int pos = 0;

void setup()
{
  // open the serial port at 9600 bps:
  Serial.begin(9600);
  // attaches the servo on pin 1 to the servo object
  Shoulder_1.attach(1);
  Serial.println(Shoulder_1.read());
  //Shoulder_1.write();
}

void loop()
{
  // goes from 0 degrees to 180 degrees
  for (pos = 0; pos <= 180; pos += 1)
  {
    // in steps of 1 degree
    // tell servo to go to position in variable 'pos'
    Shoulder_1.write(pos);
    // waits 1000ms for the servo to reach the position
    delay(5000);
  }
  // goes from 180 degrees to 0 degrees
  for (pos = 180; pos >= 0; pos -= 1)
  {
    // tell servo to go to position in variable 'pos'
    Shoulder_1.write(pos);
    // waits 15ms for the servo to reach the position
    delay(5000);
  }
}
