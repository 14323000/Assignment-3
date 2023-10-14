
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <dht.h>


dht DHT;
#define DHT11_PIN 4

#define sensorPin A0


RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001"; // establish radio channel

struct Data_Package { // initialise data structure to be transmitted 
  int humidity;
  float temp;
  int rain;
};
Data_Package data; // Create a variable with the above structure


void setup() {
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}

void loop() {
  int chk;
  chk = DHT.read11(DHT11_PIN);    // READ data from the humidity and temp sensor

  data.humidity = (DHT.humidity);
  data.temp = (DHT.temperature);
  data.rain = readSensor(); // read data from the rain sensor


  radio.write(&data, sizeof(Data_Package)); // transmit the data structure to the reciever


  delay(1000);
}

// returns the analog reading from the rainsensor
int readSensor() {
  int sensorValue = analogRead(sensorPin);  // Read the analog value from sensor
  int outputValue = map(sensorValue, 0, 1023, 255, 0); // map the 10-bit data to 8-bit data
  return outputValue;             // Return analog rain value
}