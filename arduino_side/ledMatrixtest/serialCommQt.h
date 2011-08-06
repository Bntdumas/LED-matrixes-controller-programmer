boolean array[8][8];
char field_separator = ',';
char command_separator = ';';
bool frameReady = true;

// Attach a new CmdMessenger object to the default Serial port
CmdMessenger cmdMessenger = CmdMessenger(Serial, field_separator, command_separator);

// Commands we send from the Arduino to be received on the PC
enum
{
  kCOMM_ERROR    = 000, // Lets Arduino report serial port comm error back to the PC (only works for some comm errors)
  kACK           = 001, // Arduino acknowledges cmd was received
  kARDUINO_READY = 002, // After opening the comm port, send this cmd 02 from PC to check arduino is ready
  kERR           = 003, // Arduino reports badly formatted cmd, or cmd not recognised
  kSEND_CMDS_END = 100 // Mustnt delete this line
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
  cmdMessenger.sendCmd(kACK,"starting picture");
  clear();
  frameReady = false;
}

void  pictureData()
{
  // Message data is any ASCII bytes (0-255 value). But can't contain the field
  // separator, command separator chars you decide (eg ',' and ';')
  cmdMessenger.sendCmd(kACK,"picture data");
  bool first = true;
  int x= 0;
  int y= 0;
  while ( cmdMessenger.available() )
  {
    char buf[350] = { '\0' };
    cmdMessenger.copyString(buf, 350);
    if(buf[0])
	{
        cmdMessenger.sendCmd(kACK, buf);
		if (first) x = toInt(buf);
		else y = toInt(buf);
	}
	first = false;
  }
  array[x][y] = true;
}

void  pictureEnd()
{
  cmdMessenger.sendCmd(kACK,"ending picture");
  frameReady = true;
}

// ------------------ D E F A U L T  C A L L B A C K S -----------------------

void arduino_ready()
{
  // In response to ping. We just send a throw-away Acknowledgement to say "im alive"
  cmdMessenger.sendCmd(kACK,"Arduino ready");
}

void unknownCmd()
{
  // Default response for unknown commands and corrupt messages
  cmdMessenger.sendCmd(kERR,"Unknown command");
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

void clear(){
  for(int i = 0; i < 8; i++)
    for(int j = 0; j < 8; j++)
      array[i][j] = 0;
}

int toInt(char *str){
   return atoi(str);
}

void latch(int i){
  digitalWrite(i, LOW);
  delayMicroseconds(50); //Calibrate?
  digitalWrite(i, HIGH);
}

void low(){
  for(int i = 0; i < 8; i++)
    digitalWrite(i+2,LOW);
}

void drawFrame(){
  for(int i = 0; i < 8; i++){
    //Set column:
    digitalWrite(i+2,HIGH);
    latch(10);
    low();
    
    for(int j = 0; j < 8; j++){
      digitalWrite(j+2, array[i][j]);
    }
    latch(11);
    low();
  }
  
}



