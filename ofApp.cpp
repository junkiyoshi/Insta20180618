#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofBackground(39);
	ofSetWindowTitle("Insta");

	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);
	
	ofImage image_gecko;
	image_gecko.load("images/gecko.png");
	ofImage image_dog;
	image_dog.load("images/dog.png");
	ofImage image_bat;
	image_bat.load("images/bat.png");

	this->images.push_back(image_gecko);
	this->images.push_back(image_dog);
	this->images.push_back(image_bat);

	this->images_index = -1;
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	if (ofGetFrameNum() % 180 == 0) {

		this->images_index = (this->images_index + 1) % this->images.size();
		this->pix = this->images[this->images_index].getPixelsRef();
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate((ofGetWidth() - this->images[this->images_index].getWidth()) * 0.5, (ofGetHeight() - this->images[this->images_index].getHeight()) * 0.5);

	int number_of_circle = 550;
	vector<ofPoint> points;
	while (points.size() < number_of_circle) {

		int x = ofRandom(this->images[this->images_index].getWidth());
		int y = ofRandom(this->images[this->images_index].getHeight());

		ofColor pix_color = this->pix.getColor(x, y);
		if (pix_color != ofColor(0)) {

			continue;
		}

		float x_increase = ofMap(ofNoise(ofRandom(number_of_circle), ofGetFrameNum() * 0.005), 0, 1, -10, 10);
		float y_increase = ofMap(ofNoise(ofRandom(number_of_circle), ofGetFrameNum() * 0.005), 0, 1, -10, 10);
		x += x_increase;
		y += y_increase;

		points.push_back(ofPoint(x, y));
	}

	ofColor color;
	for (int i = 0; i < points.size(); i++) {

		color.setHsb(ofRandom(255), 255, 255);
		ofSetColor(color);
		ofDrawCircle(points[i], 3);

		for (int j = 0; j < points.size(); j++) {

			float distance = points[i].distance(points[j]);
			if (distance < 50) {

				ofSetColor(color, ofMap(distance, 0, 50, 255, 0));
				ofDrawLine(points[i], points[j]);
			}
		}
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}