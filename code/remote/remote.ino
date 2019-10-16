
#include <SPI.h>
#include <WiFi.h>
#include <Servo.h>

char ssid[] = "Wind WiFi 7BE1DC";      //  network SSID  
char pass[] = "6A6E775W9A";            //  network password
int status = WL_IDLE_STATUS;           // the Wifi radio's status
WiFiServer server(2000);               // defines the availiable port of the server, for incoming requests
String buffer="";                      // defines a string buffer, where android messages have to be kept
int ledPin = 10;                       // defines the digital pin for the led
int buzzerPin = 6;                     // defines the digital pin for the buzzer device
Servo servoLeft;                       // Define left servo's motor
Servo servoRight;                      // Define right servo's motor


/*
*Setup function is used to initialize variables, pin modes, start using libraries, etc.
*The setup function will only run once, after each powerup or reset of the Arduino board.
**/
void setup() {

  Serial.begin(9600);                              // Initialize serial and wait for port to open:
  pinMode(buzzerPin,OUTPUT);                       // declare buzzer as an output
  pinMode(ledPin, OUTPUT);                         //declare led also as an output
  servoLeft.attach(4);                             // Set left servo to digital pin 10
  servoRight.attach(3);                            // Set right servo to digital pin 9
  digitalWrite(ledPin,LOW);                        // setting led off
                                                   // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present"); 
    // don't continue:
    while(true);                                  // if wifi shield isn't attached send a message to serial and stay in this loop
  } 

   // attempt to connect to Wifi network:
  while ( status != WL_CONNECTED) { 
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network.    
    status = WiFi.begin(ssid, pass);
    // wait 10 seconds for connection:
    delay(10000);
  } 
  server.begin();
  Serial.println("Server running...");
  digitalWrite(ledPin,HIGH);
         
  // you're connected now, so print out the status:
  printWifiStatus();
}



/*
* the loop function does precisely what its name suggests
* and loops consecutively, allowing the program to change and respond
**/
void loop() {

  // listen for incoming clients
  WiFiClient client = server.available();
  if (client) {
    Serial.println("new client");   
    while (client.connected()) {
      if (client.available()){
        char c = client.read();
        if (c=='\n'){
          buffer="";
        }
        else{
          buffer = buffer + c;
          if (buffer.compareTo("forw") == 0){
            back();  
            
          }
          else if(buffer.compareTo("right") == 0){       
             turnRight();
          
          }
          else if (buffer.compareTo("left") == 0){
            turnLeft();           
           
          }
          else if (buffer.compareTo("back") == 0){
             moveForward();
            
          }else if (buffer.compareTo("stop") == 0){
            stopMove();
          }
          
          else if (buffer.compareTo("horn") == 0){
            digitalWrite(buzzerPin,HIGH);
          }
          else if (buffer.compareTo("nohorn") == 0){
            digitalWrite(buzzerPin,LOW);
          }
          


        }
      }
    }

    if (!client.connected()) {
      Serial.println();
      Serial.println("disconnecting from server.");
      client.stop();
      
           
    }
  }
}


 // print the SSID of the network you're attached to
void printWifiStatus() {
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("shield IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}


/*
*Motion routines for forward, reverse, turns, and stop
**/

void moveForward() {
  servoLeft.write(0);
  servoRight.write(180); 
}

void back() {
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



