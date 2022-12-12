/*
 
 
 This version sends bytes of 1, 2, 3, or 4
 depending on the position of the object being tracked is.
 It sends a byte over once a second as to not overload
 the buffer in Arduino.
 
 Each byte corresponds to the direction each motor is turning.
 
 This is a new test, with a shorter coordinates range, for quicker
 changees in bytes being sent over.
 
 We'll see what happens.
 
 By Bianca Gan, 12/7/22
 
 
 */



#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    // Setup serial communicaation with Arduino
    serialMessage = false;
    serial.listDevices();
    vector <ofSerialDeviceInfo> deviceList = serial.getDeviceList();
    int baud = 9600;
    serial.setup("/dev/cu.usbmodem14401", baud);
    
    sendDataArr = new char[2];
    
    // Setup video grabber
    grabber.setDeviceID(2);       // for external webcam
    //grabber.setDeviceID(1);         // for builtin webcam
    grabber.setup(640, 480);
    ofSetWindowShape(640, 480);
    
    contourFinder.setUseTargetColor(true);
    
    // Set parameters
    colorTarget.set("Color Target", ofColor(255, 0, 0));
    colorOffset.set("Color Offset", 10, 0, 255);
    minArea.set("Min Area", 0.01, 0, 0.1);
    maxArea.set("Max Area", 0.05, 0, 0.1);
    blurAmount.set("Blur Amount", 0, 0, 100);
    erodeAmount.set("Erode Amount", 0, 0, 10);
    persistence.set("Persistence", 15, 0, 60);
    maxDistance.set("Max Distance", 64, 0, 640);
    showLabels.set("Show Labels", true);
    debugMode.set("Debug Mode", true);
    
    // Seet up the gui
    guiPanel.setup("tracker!", "settings.json");
    guiPanel.add(colorTarget);
    guiPanel.add(colorOffset);
    guiPanel.add(minArea);
    guiPanel.add(maxArea);
    guiPanel.add(blurAmount);
    guiPanel.add(erodeAmount);
    guiPanel.add(persistence);
    guiPanel.add(maxDistance);
    guiPanel.add(showLabels);
    guiPanel.add(debugMode);
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    // Video and pixel parameters
    grabber.update();
    
    if(grabber.isFrameNew()){
        
        grabberImg.setFromPixels(grabber.getPixels());
        
        colorUnderMouse = grabberImg.getColor(ofGetMouseX(), ofGetMouseY());
        
        if(blurAmount > 0){
            ofxCv::medianBlur(grabberImg, blurAmount);
        }
        
        if(erodeAmount > 0){
            ofxCv::erode(grabberImg, erodeAmount.get());
        }
        
        if(debugMode){
            grabberImg.update();
        }
        
        // Update tracker parameters
        contourFinder.setTargetColor(colorTarget, ofxCv::TRACK_COLOR_HSV);
        contourFinder.setThreshold(colorOffset);
        contourFinder.setMinAreaNorm(minArea);
        contourFinder.setMaxAreaNorm(maxArea);
        contourFinder.getTracker().setPersistence(persistence);
        contourFinder.getTracker().setMaximumDistance(maxDistance);
        
        
        // Find contours on video image
        contourFinder.findContours(grabberImg);
        
        
    }
    
    // Send serial data
    if(serialMessage && ofGetFrameNum() % 60){          // when true and every second
        serialMessage = false;      // then set back to false
        serial.writeByte(sendData);
        
    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackground(0);
    ofSetColor(255);
    
    
    if (debugMode)
    {
        // Draw the process image.
        grabberImg.draw(0, 0, ofGetWidth(), ofGetHeight());
    }
    else
    {
        // Draw the grabber image.
        grabber.draw(0, 0, ofGetWidth(), ofGetHeight());
    }
    
    // Draw the found contours.
    contourFinder.draw();
    
    string upMsg = "UP!\n";
    //ofSetColor(ofColor::yellow);
    //ofRect(ofGetWidth()/2, 45, 40, 25);
    ofSetColor(ofColor::red);
    ofDrawBitmapString(upMsg, ofGetWidth()/2, 60);
    
    string downMsg = "DOWN!\n";
    ofSetColor(ofColor::yellow);
    //ofRect(ofGetWidth()/2, 405, 40, 25);
    //ofSetColor(ofColor::red);
    ofDrawBitmapString(downMsg, ofGetWidth()/2, 420);
    
    string rightMsg = "RIGHT!\n";
    //ofSetColor(ofColor::yellow);
    //ofRect(580, ofGetHeight()/2 - 15, 45, 25);
    ofSetColor(ofColor::red);
    ofDrawBitmapString(rightMsg, 580, ofGetHeight()/2);
    
    string leftMsg = "LEFT!\n";
    //ofSetColor(ofColor::yellow);
    //ofRect(60, ofGetHeight()/2 - 15, 40, 25);
    ofSetColor(ofColor::red);
    ofDrawBitmapString(leftMsg, 60, ofGetHeight()/2);
    
    if (showLabels) {
        ofxCv::RectTracker& tracker = contourFinder.getTracker();
        
        for (int i = 0; i < contourFinder.size(); i++) {
            ofPoint center = ofxCv::toOf(contourFinder.getCenter(i));
            int label = contourFinder.getLabel(i);
            int age = tracker.getAge(label);
            string msg = ofToString(label) + ":" + ofToString(age);
            ofDrawBitmapString(msg, center);
            
            // Center coordinates of contour
            centerX = center.x;
            centerY = center.y;
            
            ofVec2f velocity = ofxCv::toOf(contourFinder.getVelocity(i));
            ofDrawLine(center.x, center.y, center.x + velocity.x, center.y + velocity.y);
        }
    }
    
    
    
    
    // Maps the centers so that the center is 0,0
    mappedX = (centerX - (ofGetWidth()/2));
    mappedY = -(centerY - (ofGetHeight()/2));
    
    
    // Serial event
    // Y coordinate more than 0
    if(mappedY > 100 && mappedX < 100 && mappedX > -100){
        serialMessage = true;
        sendData = 1;
    }
    
    // Y coordinate less than 0
    if(mappedY < -100 && mappedX < 100 && mappedX > -100){
        serialMessage = true;
        sendData = 2;
    }
    
    // X coordinate more than 0
    if(mappedX > 0 && mappedY < 100 && mappedY > -100){
        serialMessage = true;
        sendData = 3;
    }
    
    // X coordinate less than 0
    if(mappedX < 0 && mappedY < 100 && mappedY > -100){
        serialMessage = true;
        sendData = 4;
    }
    
    
    std::cout << "x is: " << mappedX << " y is: " << mappedY << endl;
    
    
    ofPushStyle();
    
    ofSetColor(colorUnderMouse);
    ofDrawRectangle(mouseX - 25, mouseY - 25, 50, 50);
    
    ofSetColor(colorUnderMouse.getInverted());
    ofNoFill();
    ofDrawRectangle(mouseX - 25, mouseY- 25, 50, 50);
    
    ofPopStyle();
    
    guiPanel.draw();
    
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    if(key == OF_KEY_UP){
        serialMessage = true;
        sendData = 1;
    }
    
    if(key == OF_KEY_DOWN){
        serialMessage = true;
        sendData = 2;
    }
    
    if(key == OF_KEY_LEFT){
        serialMessage = true;
        sendData = 3;
    }
    
    if(key == OF_KEY_RIGHT){
        serialMessage = true;
        sendData = 4;
    }
}


//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
    if (!guiPanel.getShape().inside(x, y)){
        // Track the color under the mouse.
        colorTarget = colorUnderMouse;
    }
    
}

//--------------------------------------------------------------
