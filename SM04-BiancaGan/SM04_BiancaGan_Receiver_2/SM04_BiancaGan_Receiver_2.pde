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
//NetAddress myRemoteLocation;

int moveX, moveY;

int xPos, yPos;
int munchD = 15;
int userD = 50;

int score = 0;
int time = 20;



void setup() {
  size(600, 440);
  //frameRate(25);
  
  xPos = int(random(0, width));
  yPos = int(random(0, height));

  /* start oscP5, listening for incoming messages at port 12000 */
  oscP5 = new OscP5(this,3030);
  
}

void draw() {
  background(0); 
  
  // Score
  textSize(40);
  textAlign(CENTER);
  text("Score: " + score, width/2, 50);
    
  // Munch
  circle(xPos, yPos, munchD);
  
  // Big Circle
  float x = map(moveX, 0, 640, 640, 0);
  circle(x, moveY, userD);
  
  // Collision
  if(dist(x, moveY, xPos, yPos) < (userD/2) + (munchD/2) -5){
    moveMunch();
    userD += 5;
    score++;
  }
  
  // Countdown


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


void moveMunch() {
  xPos = int(random(0, width));
  yPos = int(random(0, height));
}
