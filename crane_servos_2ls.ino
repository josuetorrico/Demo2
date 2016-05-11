//Defining the ID's of each Dynamixel
#define boom 1
#define trolley 2
#define arm 3
#define hand 4

Dynamixel Dxl(1);

int timestamp = 0;

//input pin values:
const int APin = 0;

// sensor thresholds:
const int A2Dlow  = 1500; 
const int A2Dhigh = 2300;

char i = 's';  //initializing the input to stop

int boomSpeed = 100;
int trolleySpeed = 350;
int armSpeed = 300;
int handGrab = 850;
int handLetGo = 225;

// limit evaluation:
int vdirection = 0; // 0 is stopped, 1 is up, 2 is down

void setup() {
  // Initialize the dynamixel bus:
  // Dynamixel 2.0 Baudrate -> 0: 9600, 1: 57600, 2: 115200, 3: 1Mbps
  Dxl.begin(3);

  Dxl.wheelMode(boom); //IDing boom
  Dxl.wheelMode(trolley); //IDing trolley
  Dxl.wheelMode(arm); //IDing arm
  Dxl.jointMode(hand); //IDing hand
  delay(500);
 
  //usb interrupt interface
  SerialUSB.attachInterrupt(usbInterrupt);
    
   //set pin 0 line sensor analog input
   pinMode(0, INPUT_ANALOG);
   pinMode(1, INPUT_ANALOG);
}

// instructions for each interrupt
void usbInterrupt(byte* input, byte ncount) {
//    const int APin = 0;
    int sensorUp = analogRead(0);
    int sensorDown = analogRead(1);

    SerialUSB.print("Up sensor = " );
    SerialUSB.println(sensorUp);
    
    SerialUSB.print("Down sensor = " );
    SerialUSB.println(sensorDown);
    
    for (byte i = 0; i < ncount; ++i) {
        switch (char(input[i])) {
            
            //boom commands
            
            case 'h': //boom ccw
                      Dxl.goalSpeed(boom, boomSpeed); 
                      break;
            
            case 'g': //boom cw
                      Dxl.goalSpeed(boom, boomSpeed | 0x400); 
                      break; 
            
            //trolley commands
            
            case 't': //arm up
                      if (sensorUp < A2Dlow){
                          Dxl.goalSpeed(trolley, 0);
                          vdirection = 0;
                          SerialUSB.print("You have reached the upper limit of the arm!!" ); 
                          break;
                      }
                      else{
                      Dxl.goalSpeed(trolley, trolleySpeed); 
                      vdirection = 1;
                      break;
                      }
            case 'y': //arm down
                      if (sensorDown < A2Dlow){
                          Dxl.goalSpeed(trolley, 0);
                          vdirection = 0;
                          SerialUSB.print("You have reached the lower limit of the arm!!" ); 
                          break;
                      }
                      else{
                      Dxl.goalSpeed(trolley, trolleySpeed|0x400); 
                      vdirection = 2;
                      break;
                      }
                      
            //arm commands

            case 'r': //trolley backward
                      Dxl.goalSpeed(arm , armSpeed| 0x400);
                      break;
                      
            case 'f': //trolley forward
                      Dxl.goalSpeed(arm , armSpeed); 
                      break;
                      
            //hand commands
            
            case 'e': //let go of box
                      Dxl.goalPosition(hand, handLetGo); 
                      break;
            
            case 'd': //grab box
                      Dxl.goalPosition(hand, handGrab); 
                      break;
                     
            //stop commands
                      
            case 's': //stop all servos per command except hand bc its not moving either open or closed
                      Dxl.goalSpeed(boom, 0); 
                      Dxl.goalSpeed(trolley, 0);
                      Dxl.goalSpeed(arm, 0);
                      break;
                    
            //set default to stop  so no movement in the system
                     
            default: 
                      Dxl.goalSpeed(boom, 0); 
                      Dxl.goalSpeed(trolley, 0);
                      Dxl.goalSpeed(arm, 0);
                      break;
        }
    }
    timestamp = millis();
}

void loop(){
//  int sensor = analogRead(Apin);
//  SerialUSB.print("sensor = " );
//  SerialUSB.println(sensor);

  // upper limit:
  if (vdirection == 1 && analogRead(0) < A2Dlow) {

    Dxl.goalSpeed(trolley, 0);
    vdirection = 0;
    SerialUSB.print("Notification: arm upper limit reached - action taken: arm stopped." );
  }

  // lower limit:
  if (vdirection == 2 && analogRead(1) < A2Dlow) {

    Dxl.goalSpeed(trolley, 0);
    vdirection = 0;
    SerialUSB.print("Notification: arm lower limit reached - action taken: arm stopped." );
  }

  //SerialUSB.print("sensor = " );
  //SerialUSB.println(analogRead(0));
  delay(100);
}
