

const int trigPin = D5; // 12;
const int echoPin = D6; // 14;

//define sound velocity in cm/uS
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "webpageCode.h";
#define SOUND_VELOCITY 0.034
#define CM_TO_INCH 0.393701

ESP8266WebServer server(80);
const char* ssid = "Medialab";
const char* password = "Mediacollege";

long duration;
float distanceCm;


void setup() {
  Serial.begin(115200); // Starts the serial communication
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  while(WiFi.status()!=WL_CONNECTED){delay(500);Serial.print(".");}
  
  Serial.println();
  Serial.print("IP Address: "); Serial.println(WiFi.localIP());

  server.on("/", webpage);
  server.begin();
  
}
void webpage()
{
  server.send(200,"text/html", webpageCode);
}
void loop() {
  // Clears the trigPin
  // SB
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  server.handleClient();
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);

  // Calculate the distance
  distanceCm = duration * SOUND_VELOCITY/2;
  


  // Convert to inches
  
 if (distanceCm > 40) {
    Serial.println("Groter dan 40 cm ");
    digitalWrite(LED_BUILTIN, HIGH);
    delay(1000);
    }
    else {
      Serial.println("Kleiner dan 40 cm ");
      delay(5000);
      digitalWrite(LED_BUILTIN, LOW); 
      
    }


  

  
 
  
}
