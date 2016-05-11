//Defining the ID's of each Dynamixel
#define boom 1
#define trolley 2
#define arm 3
#define hand 4

Dynamixel Dxl(1);

int timestamp = 0;


char i = 's';  //initializing the input to stop

int boomSpeed = 100;
int trolleySpeed = 350;
int armSpeed = 300;
int handGrab = 850;
int handLetGo = 225;


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
}

// instructions for each interrupt
void usbInterrupt(byte* input, byte ncount) {
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
                     Dxl.goalSpeed(trolley, trolleySpeed); 
                     break;
                     
            case 'y': //arm down
                      Dxl.goalSpeed(trolley, trolleySpeed|0x400); 
                      break;
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
  delay(100);
}
