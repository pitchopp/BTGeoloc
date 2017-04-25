import processing.serial.*;

Serial myPort;        // The serial port
float xPos = 1; 
float yPos = 1;// horizontal position of the graph
int change = 0;
boolean clear = false;

void setup () {
  // set the window size:
  size(500, 500);

  // List all the available serial ports
  // if using Processing 2.1 or later, use Serial.printArray()
  // println(Serial.list());

  // I know that the first port in the serial list on my mac
  // is always my  Arduino, so I open Serial.list()[0].
  // Open whatever port is the one you're using.
  myPort = new Serial(this, "COM9", 9600);

  // don't generate a serialEvent() unless you get a newline character:
  myPort.bufferUntil('\n');

  // set inital background:
  background(0);
}
void draw () {
  if (clear){
    background(0);
  }
  // draw the line:
  stroke(153);
  line(0,0,0,500);
  line(0,500,500,500);
  line(500,500,500,0);
  line(0,0,500,0);
  line(200,0,200,250);
  line(200,250,70,250);
  line(300,250,500,250);
  line(300,80,400,80);
  line(300,160,400,160);
  stroke(255);
  
  if(clear){
    ellipse(xPos,yPos,5,5);
  }
  
  // at the edge of the screen, go back to the beginning:
  
}


void serialEvent (Serial myPort) {
  // get the ASCII string:
  String inString = myPort.readStringUntil('\n');

  if (inString != null) {
    // trim off any whitespace:
    inString = trim(inString);
    // convert to an int and map to the screen height:
    if (change == 0){
      xPos = float(inString);
      change = 1; 
      clear = false;
  }
    else{
      yPos = float(inString); 
      change = 0;  
      clear = true;
  }
  }
  
}