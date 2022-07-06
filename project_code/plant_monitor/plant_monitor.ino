//#code_BY_M.SIVA KRISHNA
#include "DHT.h"
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
DHT dht(5, DHT11);

int value;
int c=0;
//Declar your pin as per your board
int sensoranalog =34;
int sensorPin = 19;
int sensorValue = 0; 
int motor1Pin1 = 27; 
int motor1Pin2 = 26; 
int enable1Pin = 14; 
//Default value for motor to run in high speed
const int freq = 30000;
const int pwmChannel = 0;
const int resolution = 8;
int dutyCycle = 200;
//Blynk and wifi data
char auth[] = "RMZ4lJNH6s3h4iHWJamsHcXaJqUr2Zsu";// Enter yor authentication code
char ssid[] = "AIM EDUCATION & XEROX"; // Enter your wifi name
char pass[] = "mschari@73"; // Enter your wifi Password
void setup() {
  Serial.begin(9600);
  pinMode(2, INPUT);
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(enable1Pin, OUTPUT);
  ledcSetup(pwmChannel, freq, resolution);
  
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(enable1Pin, pwmChannel);
  Blynk.begin(auth, ssid, pass);
  Serial.println(F("DHTxx test!"));
  dht.begin();
}
void sendSensor()
{
  float h = dht.readHumidity(); //dht.readHumidity() for read humidity
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit
  float hif = dht.computeHeatIndex(t, h,false); // or dht.readTemperature(true) for Fahrenheit
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
   
  Blynk.virtualWrite(V7, h);  //V7 is for Humidity
  Blynk.virtualWrite(V6, t); //V6 is for Temperature
  Blynk.virtualWrite(V8, hif);//V8 is for Heat Index
}
void moist(){
  sensorValue = digitalRead(sensorPin);
  value=analogRead(sensoranalog);
  Blynk.virtualWrite(V5, value);
  if (value>=900 && c<=5) {
    Blynk.notify("I need water..💦🪴");
    c=c+1;
    delay(300000);
  }
  if(value==500){
    Blynk.notify("Thank's for Food..?❤?");
    
  }
  
}
BLYNK_WRITE(V1)

{

int a = param.asInt();
value=analogRead(sensoranalog);
  if(a==1){
//   Serial.print("enough of water");
  digitalWrite(motor1Pin1, HIGH); 
  digitalWrite(motor1Pin2, LOW);
  ledcWrite(pwmChannel,255);
  }
   else{
    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motor1Pin2, LOW);
   }
   if(c==4 && a==0 && value>=1500){
    digitalWrite(motor1Pin1, HIGH); 
    digitalWrite(motor1Pin2, LOW);
    ledcWrite(pwmChannel,255);
    if(value<=600){
     digitalWrite(motor1Pin1, LOW);
    digitalWrite(motor1Pin2, LOW);
    }
    
   }
 

}

void loop() {
   Blynk.run();

  sendSensor();
  moist();
 
//#code_BY_M.SIVA KRISHNA
}
