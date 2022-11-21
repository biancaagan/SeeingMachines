// ofApp.h
#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxCv.h"
#include "ofxOsc.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp
{
public:
    void setup();
    void update();
    void draw();
    void mousePressed(int x, int y, int button);
    //void keyPressed(int key);
    //void mouseDragged(int x, int y, int button);
    
    ofVideoGrabber grabber;
    ofImage grabberImg;
    
    ofxCv::ContourFinder contourFinder;
    
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
    
    ofColor colorUnderMouse;
    
    ofxCvBlob centroid;
    
    string sendAddr;
    int sendPort;
    int centerX;
    int centerY;
    
    ofxOscSender sender;
    ofxPanel guiPanel;
    
    
};
