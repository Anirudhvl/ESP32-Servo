#include <Servo.h>
#include <WiFi.h>
#include <PCD8544.h>
 int posDegrees = 0;
Servo servo1, servo2, servo3,servo4;



 int handPos = 0, arm1Pos = 60, arm2Pos = 8, baseRot = 0;
const char* ssid     = "ssid";
const char* password = "password";

WiFiServer server(80);
void setup()
{
    Serial.begin(115200);

    pinMode(5, OUTPUT);      // set the LED pin mode
servo1.attach(14);
servo2.attach(13);
servo3.attach(12);
servo4.attach(18);
servo1.write(handPos);
servo2.write(60);
servo3.write(arm2Pos);
servo4.write(0);
    delay(10);

    // We start by connecting to a WiFi network

    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected.");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    
    server.begin();

}

int value = 0;

void loop(){
  delay(10);
 WiFiClient client = server.available();   // listen for incoming clients

  if (client) {                             // if you get a client,
    Serial.println("New Client.");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            // the content of the HTTP response follows the header:
            
            client.print("HAND (Servo 1): <button onclick= location.href=\"/A\"> RELEASE </button> <button onclick= location.href=\"/B\"> GRAB </button> <br>");
            client.print("ARM1 (Servo 2): <button onclick= location.href=\"/C\"> UP </button> <button onclick= location.href=\"/D\"> DOWN </button> <br>");
            client.print("ARM2 (Servo 3): <button onclick= location.href=\"/E\"> UP </button> <button onclick= location.href=\"/F\"> DOWN </button> <br>");
             client.print("BASE (Servo 4): <button onclick= location.href=\"/G\"> RIGHT </button> <button onclick= location.href=\"/H\"> LEFT </button> <br>");
            //client.print("Click <a href=\"/B\">here</a> to turn the LED on pin 5 off.<br>");

            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          } else {    // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }



int i = 0;
        // Check to see if the client request was "GET /H" or "GET /L":
////////////////////////// SERVO1 ///////////////////////////////////        
        if (currentLine.endsWith("GET /A")) {
          
          while(i<5)
{
digitalWrite(5, HIGH);
   servo1.write(handPos);
   
        Serial.println(handPos);
        delay(10);
        digitalWrite(5, LOW);
        handPos =handPos + 2;
        i ++;
        if (handPos >180)
        break;
}        
                      } 
      if (currentLine.endsWith("GET /B")) {
      while(i<5)
{

   servo1.write(handPos);
   digitalWrite(5, HIGH);
        Serial.println(handPos );
        delay(10);
        digitalWrite(5, LOW);
        handPos = handPos - 2;
        i ++;
        if (handPos <= 0)
        break;
}        
                     
        }


////////////////////////// SERVO2 ///////////////////////////////////        
          if (currentLine.endsWith("GET /C")) {
          
          while(1)
{
   if (arm1Pos >180)
        break;
digitalWrite(5, HIGH);
   servo2.write(arm1Pos);
   
        Serial.println(arm1Pos);
        delay(20);
        digitalWrite(5, LOW);
        arm1Pos =arm1Pos + 2;
      
       
}        
                      } 
  if (currentLine.endsWith("GET /D")) {
          
          while(1)
{
      if (arm1Pos < 60)
        break;
digitalWrite(5, HIGH);
   servo2.write(arm1Pos);
   
        Serial.println(arm1Pos);
        delay(20);
        digitalWrite(5, LOW);
        arm1Pos =arm1Pos - 1;
     
    
}        
                      } 
                       
                       
////////////////////////// SERVO3 ///////////////////////////////////                       
                       if (currentLine.endsWith("GET /E")) {
          
          while(1)
{
  if (arm2Pos >80)
        break;
   servo3.write(arm2Pos);
digitalWrite(5, HIGH);
 
   
        Serial.println(arm2Pos);
        delay(10);
        digitalWrite(5, LOW);
        arm2Pos =arm2Pos + 2;
       
       
}    
                       }    
                        if (currentLine.endsWith("GET /F")) {
          
          while(1)
{
   if (arm2Pos < 8)
        break;
digitalWrite(5, HIGH);
   servo3.write(arm2Pos);
   
        Serial.println(arm2Pos);
        delay(10);
        digitalWrite(5, LOW);
        arm2Pos =arm2Pos - 2;
       
       
}  
                        }      
////////////////////////// SERVO4 /////////////////////////////////// 
  if (currentLine.endsWith("GET /G")) {
          
          while(1)
{
  if (baseRot >180)
        break;
   servo4.write(baseRot);
digitalWrite(5, HIGH);
 
   
        Serial.println(baseRot);
        delay(10);
        digitalWrite(5, LOW);
        baseRot =baseRot + 2;
       
       
}    
                       }    
                        if (currentLine.endsWith("GET /H")) {
          
          while(1)
{
   if (baseRot < 0)
        break;
digitalWrite(5, HIGH);
   servo4.write(baseRot);
   
        Serial.println(baseRot);
        delay(10);
        digitalWrite(5, LOW);
        baseRot =baseRot - 2;
       
       
}  
                        } 
////////////////////////////////////////////////////////////////////      
      }
    }
    // close the connection:
    client.stop();
    Serial.println("Client Disconnected.");
    
  }
}
