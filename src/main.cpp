#include "ofMain.h"
#include "ofApp.h"
//#include "ofGLProgrammableRenderer.h"

//========================================================================
int main( ){
	ofSetupOpenGL(1024,768,OF_WINDOW);			// <-------- setup the GL context
    
//    ofGLWindowSettings glWindowSettings;
//    glWindowSettings.setGLVersion(4,1);
//    ofCreateWindow(glWindowSettings);
    
	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());

}
