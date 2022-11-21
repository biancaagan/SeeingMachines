#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	int lifeWidth = 500;
	int lifeHeight = 300;

	lifeImg.allocate(ofGetWidth(), ofGetHeight(), OF_IMAGE_GRAYSCALE);

	ofSetWindowShape(lifeImg.getWidth(), lifeImg.getHeight());

	ofPixels lifePix = lifeImg.getPixels();


	// For every cell in the image
	for (int y = 0; y < lifeImg.getHeight(); y++) {
		for (int x = 0; x < lifeImg.getWidth(); x++) {


			if (ofRandomuf() < 0.2) {
				lifePix.setColor(x, y, ofColor(255));
			}
			else {
				lifePix.setColor(x, y, ofColor(0));
			}
		}
	}

	lifeImg.setFromPixels(lifePix);

	newLifePix = lifePix;


}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

	/*
	Isolation: a live ? cell with less than 2 live neighbors will die ??.
	Overcrowding : a live ? cell with 4 or more neighbors will die ??.
	Reproduction : a dead ? cell with exactly 3 live neighbors will live ??.
	*/

	lifeImg.draw(0, 0);


	// Draw grid over image
	for (int x = 0; x < lifeImg.getWidth(); x++) {
		for (int y = 0; y < lifeImg.getHeight(); y++) {

			int lives = 0;

			ofColor pixColor = lifeImg.getColor(x, y);		// get color of pixel / cell

			ofSetColor(pixColor);

			ofDrawRectangle(x * gridSize, y * gridSize, gridSize, gridSize);		// draw grid

			// Check neighbors
			if (lifeImg.getColor(x - 1, y - 1) == 255) {		// top left
				lives++;
			}
			
			if (lifeImg.getColor(x, y - 1) == 255) {		// top middle
				lives++;
			}

			if (lifeImg.getColor(x + 1, y - 1) == 255) {		// top right
				lives++;
			}

			if (lifeImg.getColor(x - 1, y) == 255) {		// left middle
				lives++;
			}

			if (lifeImg.getColor(x + 1, y) == 255) {		// right midde
				lives++;
			}

			if (lifeImg.getColor(x - 1, y + 1) == 255) {		// bottom left
				lives++;
			}

			if (lifeImg.getColor(x, y + 1) == 255) {		// bottom middle
				lives++;
			}

			if (lifeImg.getColor(x + 1, y + 1) == 255) {		// bottom right
				lives++;
			}

			// Count neighbors are alive
			if (lifeImg.getColor(x, y) == 255) {		// if center cell is alive
				
				if (lives < 2) {
					newLifePix.setColor(x, y, ofColor(0));		// cell dies
				}
				if (lives >= 4) {
					newLifePix.setColor(x, y, ofColor(0));		// cell dies
				}
			}
			else {

				if (lives == 3) {
					newLifePix.setColor(x, y, ofColor(255));		// cell lives
				}

			}
		}
	}

	lifePix = newLifePix;
	lifeImg.setFromPixels(newLifePix);

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
