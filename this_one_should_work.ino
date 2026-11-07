// this is for if we want the display right here on arduino ide


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
// mySensor is the name i gave the sensor you can change this and i encourage you to change it if you want
uint8_t status = 0;


void setup() {
  Serial.begin(460800);

  Wire.setSDA(SDA_PIN); // tells the computer what this pin is being used for
  Wire.setSCL(SCL_PIN);//selects the 5 pin for SCL
  Wire.begin(); //starts the I2C for communication and the I2C s interface

  Wire.setClock(100000); // speed computer
  mySensor.begin(); // preparing the sensor library
  uint8_t status = mySensor.init(); // uint8_t is a data type, status is the viarable i'm using to store the data , the last one is like the data that get stored in the status
 

  mySensor.set_resolution(VL53LMZ_RESOLUTION_8X8); //this block is the new part that is doing the magic 
  status = mySensor.start_ranging();

}

void loop() {
  uint8_t NewDataReady = 0;//stores weteher new viarbles are available

  status = mySensor.check_data_ready(&NewDataReady); //checking wether data is ready , giving variable to the function so the librarie can put it's answer into the viarable
  
  if (status == 0 && NewDataReady != 0){ //&& means and so both conditions must be right before the code can run, first condition: did the function check the sensor, second condition: is the data ready

    VL53LMZ_ResultsData Results; // structure

    status = mySensor.get_ranging_data(&Results);//copy latest measruments into results
    // reslults.distance_mm :getting the distance measerments, 0: selects the first one , storing it as integer , so like ykyk python

    // Serial.println("First zone:"); // you'd use this block if you want 1 data
    // Serial.println(distance); 
    for(int i = 0; i < 64; i++){ //starts at zone 0 keeps running till it reaches zone 64 i++ ykyk that easy
      if(Results.nb_target_detected[i]> 0) {
        int distance = Results.distance_mm[
          VL53LMZ_NB_TARGET_PER_ZONE * i
        ];// reslults.distance_mm :getting the distance measerments, i: selects the first one , storing it as integer , so like ykyk python
        
        Serial.print(distance); 
      }
      
      else{
        Serial.print(-1); //this prints when we don't recieve data
        }
      if (i < 63){
        Serial.print(",");
      }
    }

    
    Serial.println();
    
  }
}
