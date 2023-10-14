#include <dht.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN 

const byte address[6] = "00001"; // establish radio channel

struct Data_Package { // initialise data structure to be recieved (identical to the data structure transmitted)
  int humidity;
  float temp;
  int rain;
};

Data_Package data; // Create a variable with the above structure called data

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening(); // start recieving Data_Package
}

void loop() {
  if (radio.available()) { // check if the data can be read through radio channel
        radio.read(&data, sizeof(Data_Package)); // Read the whole data and store it into the 'data' structure
        
        outputConditions(data);
        outputAttire(data);
  }

  delay(5000);
}

// outputs the weather conditions to the terminal
void outputConditions(Data_Package &data){
  Serial.println("Hello Annabel, these are the current weather conditions:\n");
  Serial.print("Temperature: ");
  Serial.print(data.temp);
  Serial.print("°C   Humidity: ");
  Serial.print(data.humidity);
  Serial.print("%   Rain: ");
  if (data.rain < 150) {
    Serial.print("Not raining");
  } else if (data.rain >= 150 && data.rain < 200) {
    Serial.print("Raining lightly");
  } else {
    Serial.print("Raining heavily");
  }
}

// outputs the clothing recomendations to the terminal
void outputAttire(Data_Package &data){
  Serial.println("\n\nBased on these conditions, I recommend you wear:\n");
  
  if (data.temp <= 10){
      Serial.println("Thick pants and a Winter jacket becuase it is very cold.");
  } else if (data.temp > 10 && data.temp <=20){
      Serial.println("Warm pants, a jumper and possibly a scarf too.");
  } else if (data.temp > 20 && data.temp <=25){
      Serial.println("Shorts and a light sweater.");
  } else if (data.temp > 25) {
      Serial.println("A skirt and a singlet becuase its cooking outside!");
  }

  if (data.humidity < 30) {
    Serial.println("Humidity is low, try to wear materials such as cotton.");
  } else if (data.humidity >= 30 && data.humidity < 70) {
    Serial.println("Humidity is mild, choose any material.");
  } else if (data.humidity >= 70) {
    Serial.println("Humidity is high, wear materials such as linen or hemp.");
  }

  if (data.rain < 150){
    Serial.println("It is not currently raining so no need for a rain jacket.");
  } else if (data.rain >= 150 && data.rain < 200){
    Serial.println("Bring a rain jacket, it is raining lightly outside.");
  } else if (data.rain >+ 200){
    Serial.println("Pack an umberella today becuase it is down pouring sweetie... bad day to be a perm.");
  }  

    Serial.println("\nHave a nice day Annabel :)\n");

}
