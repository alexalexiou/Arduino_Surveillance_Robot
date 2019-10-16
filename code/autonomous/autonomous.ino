#include <Event.h>
#include <Timer.h>
#include <Time.h>
#include <Servo.h>


Servo servoLeft;                      // Define left servo's motor
Servo servoRight;                     // Define right servo's motor
const int trigPin = 5;                // ultrasonic's proximmity  trigger pin
const int echoPin = 2;                // ultrasonic's proximmity echo pin
int buzzerPin = 6;  //9              // define buzzer's pin
int inputPin = 9;  //88              // PIR sensor's pin 
//int pirState = LOW;                // we start, assuming no motion detected
int val = 0;  
Timer t;                            //Declaration of Timer library, responsible for timer interrupts.
boolean pirSense = false;
long xronos=0;


/*
*Setup function is used to initialize variables, pin modes, start using libraries, etc.
*The setup function will only run once, after each powerup or reset of the Arduino board.
**/
void setup() { 
  Serial.begin(9600);
  servoLeft.attach(4);              // Set left servo to digital pin 10
  servoRight.attach(3);             // Set right servo to digital pin 9

  pinMode(buzzerPin, OUTPUT);      // declare buzzer's pin as output
  pinMode(inputPin, INPUT);        // declare PIR sensor's pin as input

  pinMode(trigPin, OUTPUT);        //declare ultrasonic sensor's trigger pin as an output.Trigger pin is responsible for sending ultrasonic signals to environment.
  pinMode(echoPin, INPUT);         //declare ultrasonic sensor's echo pin as an input.Echo pin is responsible for receiving the signals, that trigger pin have sent.
  t.every(30000,monitoring);      // 2nd argument set the interrupt function that has to be called every 1st arg. value of seconds (in this case 30 sec).
} 


/*
* the loop() function does precisely what its name suggests
* and loops consecutively, allowing the program to change and respond
**/

void loop() {  
  long duration, distance;           
  digitalWrite(trigPin, LOW);                           // set trigger pin to low ( doesn't send any signal)
  delayMicroseconds(2);                                 // give some (tiny) delay time for ensuring that no signal have been sented
  digitalWrite(trigPin, HIGH);                          // send ultrasonic signal, by HIGH constant
  delayMicroseconds(10);                                // for 10 μs allows the ultrasonic sensor to send signals.
  digitalWrite(trigPin, LOW);                           //stops by LOW constant the sending signal
  pinMode(echoPin, INPUT);                              //echo pin receiving them (signals)
  duration = pulseIn(echoPin, HIGH);                    // assigns the duration of time betwween that signal needs to travel from the sensor and back.
  distance = microsecondsToCentimeters(duration);       //assigns to distance var the cm of the distance between robot and obstacle. 
  delay(100);                              
 Serial.println(distance);
  if (distance >= 40){
    moveForward();
  }
  else {

    stopMove();
    int x = random(0,2);                               //Decide randomly every time where to turn.
    if(x == 0 ){ 
      turnRight();     
      delay(500);                                      // 500 milliseconds needed for robot in order to turn in a direction.
    }
    else{
      turnLeft();       
      delay(500);
    }
  }
  t.update();                                        
}


/*
*monitoring function called by timer interrupt  every 30 sec
responsible to monitors the area
**/
void monitoring(){
   xronos = now();                //get the current time
  while( xronos+5 >now() ){       //for 5 sec monitors the area
    stopMove();                  // stops in order to perform the action of monitoring
    delay(1000);                // gives some time for ensuring that robot has being stopped
    pirSensor();                // calls pirSensor function
  } 
}


/*
*Motion routines for forward, reverse, turns, and stop
**/

void reverse() {
  servoLeft.write(0);
  servoRight.write(180); 
}

void moveForward() {
  servoLeft.write(180);
  servoRight.write(0);
}

void turnRight() {
  servoLeft.write(180);
  servoRight.write(180);
}
void turnLeft() {
  servoLeft.write(0);
  servoRight.write(0);
}

void stopMove() {
  servoLeft.write(90);
  servoRight.write(90);
}


/*
*The speed of sound is 340 m/s or 29 microseconds per centimeter.
*The ping travels out and back, so to find the distance of the
*object we take half of the distance travelled.
**/
long microsecondsToCentimeters(long microseconds)
{
   return microseconds / 29 / 2;
}


/*
*pirSensor function is responsible for PIR sensor operations
*and actions
**/
void pirSensor(){
  val = digitalRead(inputPin);                  // read input value of Pir sensor
  if (val == HIGH) {                            // check if the input is HIGH, sensor have detected any movement
    digitalWrite(buzzerPin, HIGH);              // turn Buzzer ON
    pirSense = true;
    delay(800);
    digitalWrite(buzzerPin, LOW); 
    //    if (pirState == LOW) {
    //      // we have just turned on
    //      Serial.println("Motion detected!");
    //      // We only want to print on the output change, not state
    //      pirState = HIGH;
    //    }
  } 
  else {
    digitalWrite(buzzerPin, LOW); // turn LED OFF
    //    if (pirState == HIGH){
    //      // we have just turned of
    //      Serial.println("Motion ended!");
    //      // We only want to print on the output change, not state
    //      pirState = LOW;
    //    }
  }
}








