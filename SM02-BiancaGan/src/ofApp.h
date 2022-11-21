#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxCv.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		ofVideoGrabber grabber;
		ofImage grabberImg;

		ofParameter<int> blurAmount;
		ofParameter<float> lerpAmount;
		ofParameter<bool> invertMode;
		ofParameter<bool> keysmashMode;
		ofParameter<bool> randomMode;

		ofxPanel guiPanel;
		bool displayGui;

		bool aKey;

		int hVal;
		int sVal;
		int bVal;

		int newhVal;
		int newsVal;
		int newbVal;

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
