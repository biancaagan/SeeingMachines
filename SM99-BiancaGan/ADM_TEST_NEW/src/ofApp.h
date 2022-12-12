#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxCv.h"
#include "ofxOsc.h"
#include "ofxGui.h"



class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    void keyPressed(int key);
    void mousePressed(int x, int y, int button);
    
    
    // Serial communication elements
    ofSerial serial;
    bool serialMessage;         // a flag for sending serial
    char receivedData[14];      // for storing incoming data
    char sendData = 1;
    char* sendDataArr;
    
    int sendX;
    int sendY;
    
    int dir;
    
    int yCount;
    int xCount;
    
    // Variables for mapped coordinates with center being 0,0
    int mappedX = 0;
    int mappedY = 0;
    
    int xState;
    int yState;
    
    
    // Video elements
    ofVideoGrabber grabber;
    ofImage grabberImg;
    
    ofxCv::ContourFinder contourFinder;
    int centerX = 320;
    int centerY = 240;
    
    // GUI parameters
    ofParameter<ofColor> colorTarget;
    ofParameter<int> colorOffset;
    ofParameter<float> minArea;
    ofParameter<float> maxArea;
    ofParameter<int> blurAmount;
    ofParameter<bool> debugMode;
    ofParameter<int> erodeAmount;
    ofParameter<int> persistence;
    ofParameter<float> maxDistance;
    ofParameter<bool> showLabels;
    
    ofxPanel guiPanel;
    
    ofColor colorUnderMouse;
    
    
    
    
    
    
};
