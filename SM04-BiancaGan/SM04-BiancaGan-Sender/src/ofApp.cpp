// ofApp.cpp
#include "ofApp.h"

void ofApp::setup()
{
    grabber.setDeviceID(1);
    grabber.setup(640, 480);
    ofSetWindowShape(640, 480);
    
    contourFinder.setUseTargetColor(true);
    
    colorTarget.set("Color Target", ofColor(255, 0, 0));
    colorOffset.set("Color Offset", 10, 0, 255);
    minArea.set("Min Area", 0.01, 0, 0.1);        // card will never be bigger than half the screen
    maxArea.set("Max Area", 0.05, 0, 0.1);
    blurAmount.set("Blur Amount", 0, 0, 100);
    erodeAmount.set("ErodeAmount", 0, 0, 10);
    persistence.set("Persistence", 15, 0, 60);
    maxDistance.set("Max Distance", 64, 0, 640);
    showLabels.set("Show Labels", false);
    debugMode.set("Debug Process", false);
    
    // Setup the gui
    guiPanel.setup("Tracker!");
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
    
    // Set up the OSC sender.
    sendAddr = "localhost";
    sendPort = 3030;
    sender.setup(sendAddr, sendPort);
}

void ofApp::update(){
    
    grabber.update();
    
    if (grabber.isFrameNew()) {
        
        grabberImg.setFromPixels(grabber.getPixels());
        
        colorUnderMouse = grabberImg.getColor(ofGetMouseX(), ofGetMouseY());
        
        if (blurAmount > 0) {        // blur only if it is in use, not if 0
            ofxCv::medianBlur(grabberImg, blurAmount);        // blur the color the is most prominent, in this case red
        }
        
        if (erodeAmount > 0) {
            ofxCv::erode(grabberImg, erodeAmount.get());
        }
        
        if (debugMode) {
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

}

void ofApp::draw()
{
    //grabberImg.draw(0, 0);
    //contourFinder.draw();
        
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
    
    std::cout << "x: " << centerX << "y: " << centerY << endl;
    
    ofPushStyle();
    
    ofSetColor(colorUnderMouse);
    ofDrawRectangle(mouseX - 25, mouseY - 25, 50, 50);
    
    ofSetColor(colorUnderMouse.getInverted());
    ofNoFill();
    ofDrawRectangle(mouseX - 25, mouseY- 25, 50, 50);
    
    ofPopStyle();
    
    guiPanel.draw();
    
    // Send center x,y coordinates
    ofxOscMessage msg;
    msg.setAddress("/blob/pos");
    msg.addIntArg(centerX);
    msg.addIntArg(centerY);
    sender.sendMessage(msg);


}

void ofApp::mousePressed(int x, int y, int button)
{
    if (!guiPanel.getShape().inside(x, y)){
        // Track the color under the mouse.
        colorTarget = colorUnderMouse;
    }
}


/*
 
void ofApp::keyPressed(int key)
{
    if (key == 's'){
        ofxOscMessage msg;
        msg.setAddress("/cursor/color");
        
        sender.sendMessage(msg);
    }
}


void ofApp::mouseDragged(int x, int y, int button)
{
    ofxOscMessage msg;
    msg.setAddress("/cursor/move");
    msg.addIntArg(ofGetMouseX());
    msg.addIntArg(ofGetMouseY());
    
    sender.sendMessage(msg);
}

 */
