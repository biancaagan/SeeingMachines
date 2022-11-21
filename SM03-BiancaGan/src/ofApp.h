#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxKinectV2.h"



class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
    
        ofxKinectV2 kinect;
        ofTexture depthTex;
    
        ofTexture texIR;
    
        ofParameter<int> nearThreshold;
        ofParameter<int> farThreshold;

        ofImage thresholdImg;
        ofxPanel guiPanel;
    
    

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
};
