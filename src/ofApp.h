#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

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
    void neuroLines();
        int w,h;
        ofShader shader;
        ofFbo fbo;
        ofEasyCam cam;
    bool save;
    float dist;
    int loops;
    void animateMesh(ofMesh &m);
    ofImage img, blankImg;
    int origW, origH;
    ofMesh wall;
    ofMesh mesh;
    vector<ofVec3f> offsets;
    ofMesh pointMesh;
    ofTexture dotTexture;
    void generateVbo(ofMesh &m);
    string fn;
    
    ofxPanel gui;
    ofParameter<int> guiReduce;
    ofParameter<float> guiIntensityThreshold;
    ofParameter<float> guiRndAmt;
    ofParameter<float> guiConnectionDistance;
    ofParameter<float> guiNoiseSpeed;
    ofParameter<float> guiNoiseScale;
    ofParameter<int> guiMeshAlpha;
    ofParameter<bool> guiNoise;
    ofParameter<bool> remesh;
};
