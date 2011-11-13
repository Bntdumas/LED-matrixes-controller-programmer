#include <CmdMessenger.h>
#include <Streaming.h>

//cube size
#define CUBE_X 3
#define CUBE_Y 3
#define CUBE_Z 3


boolean array[CUBE_X][CUBE_Y][CUBE_Z];
char field_separator = ',';
char command_separator = ';';
bool frameReady = true;

CmdMessenger cmdMessenger = CmdMessenger(Serial, field_separator, command_separator);


// Commands we send from the Arduino to be received on the PC
enum
{
  kCOMM_ERROR    = 000, // Lets Arduino report serial port comm error back to the PC (only works for some comm errors)
  kACK           = 001, // Arduino acknowledges cmd was received
  kARDUINO_READY = 002, // After opening the comm port, send this cmd 02 from PC to check arduino is ready
  kERR           = 003, // Arduino reports badly formatted cmd, or cmd not recognised
  kSEND_CMDS_END  // Mustnt delete this line
};



// Commands we send from the PC and want to recieve on the Arduino.
// We must define a callback function in our Arduino program for each entry in the list below vv.
// They start at the address kSEND_CMDS_END defined ^^ above as 004
messengerCallbackFunction messengerCallbacks[] = 
{
  pictureStart, //4
  pictureData , //5
  pictureEnd,   //6
  NULL
};

void  pictureStart()
{
  //cmdMessenger.sendCmd(kACK,"starting picture");
  clear();
  frameReady = false;
}

void  pictureData()
{

  bool first = true;
  bool second = false;
  bool third = false;
  int x= 0;
  int y= 0;
  int z= 0;
  while ( cmdMessenger.available() )
  {
    char buf[20] = { '\0' };
    cmdMessenger.copyString(buf, 20);
    if(buf[0])
	{

		if (first)
		{
		    x = toInt(buf);
		    first = false;
            second = true;
		}
		else if(second)
		{
		    y = toInt(buf);
		    first = false;
            second = false;
            third = true;
		}
		else if (third) z = toInt(buf);
	}
  }
  array[y][x][z] = true;
}

void  pictureEnd()
{
  //cmdMessenger.sendCmd(kACK,"ending picture");
  frameReady = true;
}

// ------------------ S E T U P ----------------------------------------------

void attach_callbacks(messengerCallbackFunction* callbacks)
{
  int i = 0;
  int offset = kSEND_CMDS_END;
  while(callbacks[i])
  {
    cmdMessenger.attach(offset+i, callbacks[i]);
    i++;
  }
}

void setup()
{
  Serial.begin(115200);
   pinMode(0, OUTPUT);
   pinMode(1, OUTPUT);
   pinMode(2, OUTPUT);
   pinMode(3, OUTPUT);
   pinMode(4, OUTPUT);
   pinMode(5, OUTPUT);
   pinMode(6, OUTPUT);
   pinMode(7, OUTPUT);
   pinMode(8, OUTPUT);
   pinMode(9, OUTPUT);
   pinMode(10, OUTPUT);
   pinMode(11, OUTPUT);

   pinMode(13, OUTPUT);
   
   clear();
  //cmdMessenger.discard_LF_CR(); // Useful if your terminal appends CR/LF, and you wish to remove them
  cmdMessenger.print_LF_CR();   // Make output more readable whilst debugging in Arduino Serial Monitor
  
  // Attach default / generic callback methods
  //cmdMessenger.attach(kARDUINO_READY, arduino_ready);
  //cmdMessenger.attach(unknownCmd);

  // Attach my application's user-defined callback methods
  attach_callbacks(messengerCallbacks);
}

void clear(){
  for(int x = 0; x < CUBE_X; x++)
    for(int y = 0; y < CUBE_Y; y++)
     for(int z = 0; z < CUBE_Z; z++)
      array[x][y][z] = false;
}

int toInt(char *str){
   return atoi(str);
}

void latch(int i){
  digitalWrite(i, LOW);
  delayMicroseconds(100); //Calibrate!
  digitalWrite(i, HIGH);
}

void low(){
  for(int i = 0; i < 8; i++)
    digitalWrite(i+2,LOW);
}

void drawFrame()
{
	for(int z = 0; z < CUBE_Z; z++)
	for(int y = 0; y < CUBE_Y; y++)
	{
		for(int x = 0; x < CUBE_X; x++)
		{
			if (array[x][y][z] == true)
				switchLed(x,y,z);
		}
	}
}

void switchLed(int x, int y, int z)
{
			
	//first find led from 0 to 9 corresponding
	digitalWrite((x*y)+2, HIGH);
	
	digitalWrite(z+11, HIGH);
			

}
/*
void switchLed(int x, int y)
{
			  
	for(int i = 0; i < 8; i++)
			digitalWrite(i+2, i == x );

	  //save
	  latch(10);
	    
	for(int i = 0; i < 8; i++)
			digitalWrite(i+2, i == y );

	  //save
	  latch(11);
}
*/



void loop()
{
 	cmdMessenger.feedinSerialData();
	 if(frameReady)
		drawFrame();
}

