/**
 * oscP5parsing by andreas schlegel
 * example shows how to parse incoming osc messages "by hand".
 * it is recommended to take a look at oscP5plug for an
 * alternative and more convenient way to parse messages.
 * oscP5 website at http://www.sojamo.de/oscP5
 */

import oscP5.*;
import netP5.*;

OscP5 oscP5;
NetAddress myRemoteLocation;


void setup() {
  size(640, 480);
  frameRate(25);
  
  /* start oscP5, listening for incoming messages at port 12000 */
  oscP5 = new OscP5(this,3030);
  
}

void oscEvent(OscMessage theOscMessage) {
  
  /* check if theOscMessage has the address pattern we are looking for. */
  if(theOscMessage.checkAddrPattern("/blob/pos")==true) {
    /* check if the typetag is the right one. */
    if(theOscMessage.checkTypetag("ii")) {
      /* parse theOscMessage and extract the values from the osc message arguments. */
      int mX = theOscMessage.get(0).intValue();  
      int mY = theOscMessage.get(1).intValue();
      print("### received an osc message /test with typetag ifs.");
      println(" values: "+mX+", "+mY);
      moveX = mX;
      moveY = mY;
      return;
    }  
  } 
}

float moveX, moveY;

void draw() {
  background(0);  
  circle(moveX, moveY, 50);
}
