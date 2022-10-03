// ****************************************************************** 
// Dallas Semiconductor DS18B20 Temperature Sensor Demo Program 
// COMP-10184 
// Mohawk College 

//Statment of Authorship: I, Haiden Murphy, student number 000839028 certify that this material is my original work. 
//No other person's work has been used without due acknowledgment and I have not made my workavailable to anyone else.
 
// library for Arduino framework  
#include <Arduino.h> 
// 1-Wire sensor communication libary 
#include <OneWire.h> 
// DS18B20 sensor library 
#include <DallasTemperature.h> 
 
// Pin that the  DS18B20 is connected to 
const int oneWireBus = D3;      
 
// Setup a oneWire instance to communicate with any OneWire devices 
OneWire oneWire(oneWireBus); 

// Pass our oneWire reference to Dallas Temperature sensor  
DallasTemperature DS18B20(&oneWire);

int numberOfDevices;
DeviceAddress tempAddress; // We'll use this variable to store a found device address

// function to print a device address

void setup() 
{ 
  // configure the USB serial monitor 
  Serial.begin(115200); 
 
  // Start the DS18B20 sensor 
  DS18B20.begin();

  numberOfDevices = DS18B20.getDeviceCount();

  Serial.println("Temperature Application");

  for(int i=0;i<numberOfDevices; i++) 
  {
      // Search the wire for address
      if(DS18B20.getAddress(tempAddress, i)) 
      {
        for (uint8_t i = 0; i < 8; i++) 
        {
          if (tempAddress[i] < 16) Serial.print("0");
            Serial.print(tempAddress[i], HEX);
            
        }
        Serial.println();
      }
  }
}

void loop() 
{ 
  float fTemp; 
 
  // ask DS18B20 for the current temperature 
  DS18B20.requestTemperatures();
 
  // fetch the temperature.  We only have 1 sensor, so the index is 0. 
  fTemp = DS18B20.getTempCByIndex(0);

  if(fTemp <= 10)
  {
    Serial.print(" is too Cold!");
  }
  else if(fTemp >= 35)
  {
    Serial.print(" is too Hot!");
  }
  else if(fTemp >= 30)
  {
    Serial.print(" is Hot");
  }
  else if(fTemp >= 25)
  {
    Serial.print(" is Perfect");
  }
  else if(fTemp >= 15)
  {
    Serial.print(" is Warm");
  }
  else if(fTemp >= 10)
  {
    Serial.print(" is Cool");
  }
  Serial.println();

 
  // print the temp to the USB serial monitor 
  Serial.print("Current temperature is: " + String(fTemp) + " deg. Celsius"); 
 
  // wait 2s (2000ms) before doing this again 
  delay(2000); 
}