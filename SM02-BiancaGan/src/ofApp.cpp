#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	grabber.setup(1280, 720);
	grabberImg.allocate(grabber.getWidth(), grabber.getHeight(), OF_IMAGE_COLOR);
	ofSetWindowShape(grabber.getWidth(), grabber.getHeight());

	blurAmount.set("Blur Amount", 0, 0, 100);
	lerpAmount.set("Lerp Amount", 0, 0, 1);
	invertMode.set("Invert Mode", false);
	keysmashMode.set("Key Smash Mode", false);
	randomMode.set("Random Color", false);

	guiPanel.setup("SM02 Assignment");
	guiPanel.add(blurAmount);
	guiPanel.add(lerpAmount);
	guiPanel.add(invertMode);
	guiPanel.add(keysmashMode);
	guiPanel.add(randomMode);

	displayGui = true;

	aKey = false;

}

//--------------------------------------------------------------
void ofApp::update(){

	grabber.update();

	ofPixels& grabPixels = grabber.getPixels();
	ofPixels& resultPixels = grabberImg.getPixels();


	for (int y = 0; y < grabber.getHeight(); y++) {
		for (int x = 0; x < grabber.getWidth(); x++) {

			ofColor currCol = grabPixels.getColor(x, y);
			ofColor invertCol = currCol.getInverted();
			ofColor randomCol(ofRandom(0, 255), ofRandom(0, 255), currCol.getBrightness());

			// Invert the colors of each pixel
			if (invertMode == true) {
				resultPixels.setColor(x, y, invertCol);
			}
			else {
				resultPixels.setColor(x, y, currCol);
			}

			// Key smash mode
			if (keysmashMode == true) {
				hVal = currCol.getHue();
				sVal = currCol.getSaturation();
				bVal = currCol.getBrightness();

				ofColor keysmashCol(hVal, sVal, bVal);
				//keysmashCol.setHsb(newhVal, newsVal, newbVal);
				/*invertMode = false;
				lerpAmount = 0;*/
				resultPixels.setColor(x, y, keysmashCol.clamp());
			}

			// Random color mode
			if (randomMode == true) {
				ofColor randomCol(ofRandom(0, 255), ofRandom(0, 255), currCol.getBrightness());
				resultPixels.setColor(x, y, randomCol);
			}

			// Lerping
			if (lerpAmount > 0 && invertMode == true) {
				resultPixels.setColor(x, y, currCol.lerp(invertCol, lerpAmount));
			}
			else if (lerpAmount > 0 && randomMode == true) {
				resultPixels.setColor(x, y, currCol.lerp(randomCol, lerpAmount));
			}
			
		}
	}

	// Blur image
	if (blurAmount > 0) {
		ofxCv::medianBlur(grabberImg, blurAmount);
	}

	grabberImg.update();

}

//--------------------------------------------------------------
void ofApp::draw(){

	grabberImg.draw(0, 0);

	if (displayGui) {
		guiPanel.draw();
	}

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

	if (key == '1') {
		displayGui = !displayGui;
	}

	// How can I get this key press to affect the image?
	if (key == 'a') {
		hVal = hVal + 10;
	}


}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

	if (key == 'a') {
		aKey = false;
	}
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
