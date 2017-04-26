import processing.serial.*;

Serial myPort;        // The serial port
String[] data, h1, h2, h3;
boolean clear = false;
int c = 1;

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
  
  stroke(204,102,0);
  printDonut(h1);
  stroke(0,102,204);
  printDonut(h2);
  stroke(0,204,102);
  printDonut(h3);
  clear = false;
  
  if(h1!=null&h2!=null&h3!=null){
  fill(255,0,0);
  printUser(h1,h2,h3);
  }
}


void serialEvent (Serial myPort) {
  // get the ASCII string:
  String inString = myPort.readStringUntil('\n');

  if (inString != null) {
    println(inString);
    data = split(inString, '|');
    clear = true;
    if (c == 1){
    
    h1 = data;
    c = 2;
  }else if (c == 2){
    
    h2 = data;
    c = 3;
  }else{
    h3 = data;
    
    c = 1;
  }
  }
  
  
}

void printCircle(String[] d){
  noFill();
  ellipse(50*float(d[0]),50*float(d[1]),50*float(d[2]),50*float(d[2]));
}

void printDonut(String[] d) {
  if (d != null){
    noFill();
    ellipse(50*float(d[0]),50*float(d[1]),50*float(d[2])+50,50*float(d[2])+50);
    
    ellipse(50*float(d[0]),50*float(d[1]),50*float(d[2])-50,50*float(d[2])-50);
  }
}

void printUser(String[] a,String[] b,String[] c){
  float x = (float(a[0])*(float(b[2])+float(c[2])) + float(b[0])*(float(a[2])+float(c[2])) + float(c[0])*(float(a[2])+float(b[2])))/(2*(float(a[2])+float(b[2])+float(c[2])));
  float y = (float(a[1])*(float(b[2])+float(c[2])) + float(b[1])*(float(a[2])+float(c[2])) + float(c[1])*(float(a[2])+float(b[2])))/(2*(float(a[2])+float(b[2])+float(c[2])));
  noFill();
  ellipse(50*x,50*y,5,5);
}

void printPosition(String[] a,String[] b,String[] c){
  float x = (float(a[0])*(float(a[2])) + float(b[0])*(float(b[2])) + float(c[0])*(float(c[2])))/((float(a[2])+float(b[2])+float(c[2])));
  float y = (float(a[1])*(float(a[2])) + float(b[1])*(float(b[2])) + float(c[1])*(float(c[2])))/((float(a[2])+float(b[2])+float(c[2])));
  noFill();
  ellipse(50*x,50*y,5,5);
}