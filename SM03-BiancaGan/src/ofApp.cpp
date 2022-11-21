#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetWindowShape(512, 424);
    
    // Use a settings object to configure the device.
    ofxKinectV2::Settings settings;
    settings.enableRGB = false;
    settings.enableIR = true;
    settings.enableDepth = true;
    
    kinect.open(0, settings);
    
    // Allocate image
    thresholdImg.allocate(640, 360, OF_IMAGE_GRAYSCALE);
    
    // Set parameters
    nearThreshold.set("Near Threshold", 10, 0, 4000);
    farThreshold.set("Far Threshold", 1000, 0, 4000);
    
    // Set gui
    guiPanel.setup("Depth Threshold", "settings.json");
    guiPanel.add(nearThreshold);
    guiPanel.add(farThreshold);
    

}

//--------------------------------------------------------------
void ofApp::update(){
    
    kinect.update();
    
    // Only load the data if there is a new frame to process.
    if (kinect.isFrameNew())
    {
        texIR.loadData(kinect.getIRPixels());
        //depthTex.loadData(kinect.getDepthPixels());
    }

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    texIR.draw(0, 0);
    //depthTex.draw(0, 0);

    
    // Get the point distance using the SDK function (in meters).
    float distAtMouse = kinect.getDistanceAt(ofGetMouseX(), ofGetMouseY());
    ofDrawBitmapStringHighlight(ofToString(distAtMouse, 3), ofGetMouseX(), ofGetMouseY() - 10);
    
    // Get the point depth using the texture directly (in millimeters).
    const ofFloatPixels& rawIRPix = kinect.getRawIRPixels();
    //const ofFloatPixels& rawDepthPix = kinect.getRawIRPixels();
    int depthAtMouse = rawIRPix.getColor(ofGetMouseX(), ofGetMouseY()).r;
    ofDrawBitmapStringHighlight(ofToString(depthAtMouse), ofGetMouseX() + 16, ofGetMouseY() + 10);
    

    // Threshold the depth
    ofShortPixels rawIRTex = kinect.getRawIRPixels();
    //ofShortPixels rawDepthTex = kinect.getRawIRPixels();
    ofPixels& thresholdPix = thresholdImg.getPixels();
    
    for(int y = 0; y < rawIRPix.getHeight(); y++){
        for(int x = 0; x < rawIRPix.getWidth(); x++){
            int depth = rawIRPix.getColor(x, y).r;
            
            if(nearThreshold < depth && depth < farThreshold){
                thresholdPix.setColor(x, y, ofColor(255));

            }
            else{
                thresholdPix.setColor(x, y, ofColor(0));
            }
        }
    }
    
    thresholdImg.update();
    
    thresholdImg.draw(0, 360);
    
    guiPanel.draw();
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
