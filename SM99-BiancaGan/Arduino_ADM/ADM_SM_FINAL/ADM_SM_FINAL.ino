/*
 * This code currently takes input from OpenFrameworks
 * over the serial port, reading bytes of either 
 * 1, 2, 3, or 4, and corresponding each incoming byte
 * to a movement of the two stepper motors to move the 
 * pen carriage up, down, left, or right.
 * 
 * By Bianca Gan, 12/6/22
 */

 
#include <Stepper.h>

// Change this to the number of steps on your motor
#define STEPS 200

// Create an instance of the stepper class,
// specifying the number of steps of the motor 
// and the pins it's attached to
Stepper stepper1(STEPS, 8, 9, 10, 11);    // LEFT MOTOR 
Stepper stepper2(STEPS, 3, 4, 5, 6);      // RIGHT MOTOR

unsigned int xPos;
unsigned int yPos;

int stps = 50;

//bool motorForwardState = false;

int stepCount = 200;

int upCount = 0;
int downCount = 0;
int leftCount = 0;
int rightCount = 0;

void setup() {
  Serial.begin(9600);

  // Set the speed of the motor 
  stepper1.setSpeed(150);
  stepper2.setSpeed(150);

}

void loop() {

  char inByte = 0;

  while(Serial.available()){
    inByte = Serial.read();
  }

    // MOVE UP
    if(inByte == 1 && upCount < 12){
      for(int s = 0; s < 15; s++){
        stepper1.step(-2);
        stepper2.step(2);
        delay(25);
      }

      upCount++;
      downCount--;

    }


    // MOVE DOWN
    if(inByte == 2 && downCount < 18){
      for(int s = 0; s < 15; s++){
        stepper1.step(2);
        stepper2.step(-2);
        delay(25);
      }  
      
      downCount++;
      upCount--;

    }


    // MOVE LEFT
    if(inByte == 3 && leftCount < 20){
      for(int s = 0; s < 15; s++){
        stepper1.step(-2);
        stepper2.step(-6);
        delay(10);
      }   

      leftCount++;
      rightCount--;

    } 

    // MOVE RIGHT
    if(inByte == 4 && rightCount < 20){
      for(int s = 0; s < 15; s++){
        stepper1.step(6);
        stepper2.step(2);
        delay(10);
      }

      rightCount++;
      leftCount--;

    }


    // Direction count constrain
    if(upCount >= 12){
      upCount = 12;
    }

    if(downCount >= 18){
      downCount = 18;
    }

    if(leftCount >= 20){
      leftCount = 20;
    }

    if(rightCount >= 20){
      rightCount = 20;
    }


  }
