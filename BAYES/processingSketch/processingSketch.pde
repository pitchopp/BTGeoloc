import processing.serial.*;

Serial myPort;        // The serial port
String[] data, h1, h2, h3;
boolean clear = false;
int c = 1;

void setup () {
  // set the window size:
  size(500, 500);
  
  //myPort = new Serial(this, "COM9", 9600);

  //myPort.bufferUntil('\n');

  background(0);
    String url = "http://127.0.0.1:8000/?70";
    println(url);
    link(url);
}

void draw () {
 
}


void serialEvent (Serial myPort) {
  // get the ASCII string:
  String inString = myPort.readStringUntil('\n');

  if (inString != null) {
    println(inString);
    
    link("http://127.0.0.1:8000/?"+inString);
  }
  
  
}