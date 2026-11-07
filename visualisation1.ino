// without #include our lives would be a lot harder
#include <Wire.h> // chip library
#include <vl53l7ch.h> //sensor librarie
// #define tells the code each time it used the SDA pin it'll translate to the number 
#define SDA_PIN 4 //communication 
#define SCL_PIN 5 //communication
#define LPN_PIN A3 //low power enable controls if pin is on or off so then ya have HIGH(3.3V) for on and LOW (OV) for off

VL53L7CH mySensor(&Wire,LPN_PIN); // in the fried chip it's already connected to 3.3V with a resistor but i'm just putting it here for like to be sure and it'll be needed if i'd ever use a different pcb
// Wire tells the sensor how to communicate with the chip like a handbook for nerds how to talk to girls but better cause it actually work, or ...it should work at least
// LPN_PIN tells what pin it is... A3
// the & means we're passing the handbook instead of making a copy or refernce

void setup() {
  Serial.begin(460800);

  Wire.setSDA(SDA_PIN); // tells the computer what this pin is being used for
  Wire.setSCL(SCL_PIN);//selects the 5 pin for SCL
  Wire.begin(); //starts the I2C for communication and the I2C s interface

  Wire.setClock(100000); // speed computer
  mySensor.begin(); // preparing the sensor library
  uint8_t status = mySensor.init(); // uint8_t is a data type, status is the viarable i'm using to store the data , the last one is like the data that get stored in the status

  if (status == 0){ // important to know that the outcome would actually be the error so that's how you know exactly what's wrong, it hink it goes op to 264 or something 
  // you can check what number means what error in the documentation of the library
    Serial.print("Sensor started");
  }
  else {
    Serial.print("Nope ya did something wrong");
    Serial.println(status);
  }
}

void loop() {
 
}
//YAAAAAAAAAY it worked YYAAy this means everything is perfect and that means my life is also perfect!!!!!
