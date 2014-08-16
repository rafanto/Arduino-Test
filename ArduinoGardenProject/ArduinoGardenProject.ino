#include <dht11.h>
dht11 DHT;
#define DHT11_PIN 4  //define a pin for DHT sensor

int lightPin    = 0; // define a pin for Photo resistor
int moisturePin = 5; // define a pin for Moisture sensor
int relayPin    = 3; // define a pin for Relay 
String statePump = "OFF"; // define a state of pump

void setup(){
Serial.begin(9600);
pinMode(relayPin, OUTPUT); 
Serial.println("ARDUINO GARDEN TEST PROGRAM ");
Serial.print("DHT LIBRARY VERSION: ");
Serial.println(DHT11LIB_VERSION);
Serial.println("Type,\tstatus,\tHumidity (%),\tTemperature (C)");
Serial.println();
}

void loop(){ 
int chktemp;
int chkmoisture;
int light;
 
chkmoisture = analogRead(moisturePin); // READ DATA MOISTURE SENSOR
light = analogRead(lightPin);          // READ DATA PHOTORESITOR
chktemp = DHT.read(DHT11_PIN);         // READ DATA TEMP & HUM SENSOR

Serial.print("DHT11 SENSOR,\t");
 
switch (chktemp){
  case DHTLIB_OK:  
       Serial.print("OK,\t"); 
       break;
  case DHTLIB_ERROR_CHECKSUM: 
       Serial.print("Checksum error,\t"); 
       break;
  case DHTLIB_ERROR_TIMEOUT: 
       Serial.print("Time out error,\t"); 
       break;
  default: 
       Serial.print("Unknown error,\t"); 
       break;
}
  
// DISPLAT DATA
Serial.print(DHT.humidity,1);
Serial.print("\t");
Serial.println(DHT.temperature,1);

Serial.print("MOISTURE SENSOR, \t");
Serial.println(chkmoisture);

if (chkmoisture < 300){
   statePump = "ON";
   Serial.println("I am thirsty, please give me water");
}

if (chkmoisture > 300 && chkmoisture < 700){
   statePump = "OFF";
   Serial.println("I feel so comfortable");
}

if (chkmoisture > 700){
   statePump = "OFF";
   Serial.println("Too much water, I might get hurt");
}

Serial.print("LIGHT SENSOR, \t");
Serial.println(light);

if (statePump == "ON") {      
   digitalWrite(relayPin, HIGH); 
   Serial.println("The Water Pump is ON"); 
} 
else {
   digitalWrite(relayPin, LOW); 
   Serial.println("The Water Pump is OFF"); 
} 
delay(5000);
}
