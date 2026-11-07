//tips: make sure you're using capital letters (cry face)


#include <Wire.h>  //the libraries
void setup() {
  Serial.begin(115200); // This is the baud rate, What it means??? it's kinda just how fast it goes, 
  //you can change this run the code see if you can notice the difference Nope scratch that apparantly it needs to be compatible with 
  // the RP2040 - Zero i'm using or it'll show faulty code
  // the one above is for speed with the I2C 
 delay(2000);

  Wire.setSDA(4);
  Wire.setSCL(5);
  Wire.begin();

  Wire.setClock(100000); // so this is just kinda how many pulses the clock generates per second and wire is just the librarie
// this one above is for speed with computer
SerialUART.println("Scanning I2C...");

for (byte address = 1; address < 127; address++) {
  Wire.beginTransmission(address);

  byte error = Wire.endTransmission();// this should all be in loop

  if (error == 0) {
    SerialPort.print("Device found at: 0x");
    SerialPort.println(address, HEX);//here too 
  }
}
  Serial.println("Shadow orchestra started"); //you won't see this cause it'll print before you can see the program

}

void loop() {
  int devicesFound = 0;

  for (byte address = 1; address < 127; address++){ //for loops have three parts for (START;CONDITION;UPDATE)
  // here: start = creating viarible adress and giving it 1 as start value , condition ,update = address = adress 
    Wire.beginTransmission(address); //I'm telling my chip it wants to contact with like the I2C
    byte error = Wire.endTransmission(); //actually does the communication

    if (error == 0) { //checks if comunication even worked
      Serial.print("Devices found: "); // what's the differnce between print and println ?
      // print just prints the stuff like if in html you do two paragraphs but println prints a line below so it comes verticle
      Serial.println(devicesFound);

      delay(3000);
    }
  }
  
}
//  why this? the adresses 1 - 126 are usable 7-bit I2C addresses
