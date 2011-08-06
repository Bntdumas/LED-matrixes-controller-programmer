#include <CmdMessenger.h>
#include <Streaming.h>

boolean array[8][8];
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
  // Message data is any ASCII bytes (0-255 value). But can't contain the field
  // separator, command separator chars you decide (eg ',' and ';')
  //cmdMessenger.sendCmd(kACK,"picture data");
  bool first = true;
  int x= 0;
  int y= 0;
  while ( cmdMessenger.available() )
  {
    char buf[20] = { '\0' };
    cmdMessenger.copyString(buf, 20);
    if(buf[0])
	{
        //cmdMessenger.sendCmd(kACK, buf);
		if (first) x = toInt(buf);
		else y = toInt(buf);
	}
	first = false;
  }
  array[y][x] = true;
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
  cmdMessenger.attach(kARDUINO_READY, arduino_ready);
  cmdMessenger.attach(unknownCmd);

  // Attach my application's user-defined callback methods
  attach_callbacks(messengerCallbacks);

  arduino_ready();
}

void clear(){
  for(int i = 0; i < 8; i++)
    for(int j = 0; j < 8; j++)
      array[i][j] = false;
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
	for(int y = 0; y < 8; y++)
	{
		for(int x = 0; x < 8; x++)
		{
			if (array[x][y] == true)
				switchLed(x,y);
		}
	}
}

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

void loop()
{
 	cmdMessenger.feedinSerialData();
	 if(frameReady)
		drawFrame();
}

