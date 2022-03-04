#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openframeworks");

	ofBackground(0);
	ofSetLineWidth(1);
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWindowSize() * 0.5);

	// 配色デザイン ビビッドブルー P144
	vector<ofColor> color_palette;
	color_palette.push_back(ofColor(18, 85, 163));
	color_palette.push_back(ofColor(0, 165, 231));
	color_palette.push_back(ofColor(93, 177, 186));
	color_palette.push_back(ofColor(44, 121, 191));
	color_palette.push_back(ofColor(136, 185, 79));
	color_palette.push_back(ofColor(246, 221, 80));
	color_palette.push_back(ofColor(200, 59, 57));
	//color_palette.push_back(ofColor(255, 255, 255));

	int span = 60;
	for (int x = span * -8; x < span * 8; x += span) {

		for (int y = span * -8; y < span * 8; y += span) {

			vector<glm::vec2> vertices;
			int radius = span * 0.9;

			int r = ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.0035), 0, 1, 0, 4);
			auto location = glm::vec2(x, y);

			if (r == 1) {

				location += glm::vec2(radius, 0);
			}
			else if (r == 2) {

				location += glm::vec2(radius, radius);
			}
			else if (r == 3) {

				location += glm::vec2(0, radius);
			}

			int deg_start = r * 90;

			for (int deg = deg_start; deg <= deg_start + 90; deg += 1) {

				vertices.push_back(location + glm::vec2(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD)));
			}

			r = (r + 2) % 4;

			location = glm::vec2(x, y);
			if (r == 1) {

				location += glm::vec2(radius, 0);
			}
			else if (r == 2) {

				location += glm::vec2(radius, radius);
			}
			else if (r == 3) {

				location += glm::vec2(0, radius);
			}

			deg_start = r * 90;
			for (int deg = deg_start; deg <= deg_start + 90; deg += 1) {

				vertices.push_back(location + glm::vec2(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD)));
			}

			this->palette_shuffle(color_palette);

			ofSetColor(color_palette[0]);
			ofFill();
			ofBeginShape();
			ofVertices(vertices);
			ofEndShape(true);

			ofSetColor(255);
			ofNoFill();
			ofBeginShape();
			ofVertices(vertices);
			ofEndShape(true);
		}
	}
}

//--------------------------------------------------------------
void ofApp::palette_shuffle(vector<ofColor>& color_palette) {

	for (int i = 0; i < color_palette.size(); i++) {

		int k = ofRandom(i, color_palette.size());
		ofColor tmp = color_palette[i];
		color_palette[i] = color_palette[k];
		color_palette[k] = tmp;
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}