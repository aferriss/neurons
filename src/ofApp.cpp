#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    w = 800;
    h = 974;
    ofSetWindowShape(w, h);
    
    fbo.allocate(w, h, GL_RGBA, 8);
    shader.load("base");
    shader.bindDefaults();
    ofDisableArbTex();
    
    save = false;
    dist = 120;
    loops = 5;
    cam.setFarClip(100000000);
    

    
    
//    pointMesh.setMode(OF_PRIMITIVE_POINTS);
//    pointMesh.enableIndices();
//    pointMesh.enableColors();
//    
//    for(int h = -loops; h< loops; h++){
//        for(int j = -loops; j < loops; j++){
//            for(int i = -loops; i < loops; i++){
//                pointMesh.addVertex(ofVec3f(i*dist  , j*dist , h*dist ));
//                ofColor c = ofColor(255);
//                c.a = 2;
//                pointMesh.addColor(c);
//                offsets.push_back(ofVec3f(ofRandom(0,100000), ofRandom(0,100000), ofRandom(0,100000)));
//            }
//        }
//    }
//    
//        connectionDistance = 150;
//        int numVerts = pointMesh.getNumVertices();
//        for (int a=0; a<numVerts; ++a) {
//            ofVec3f verta = pointMesh.getVertex(a);
//            for (int b=a+1; b<numVerts; ++b) {
//                ofVec3f vertb = pointMesh.getVertex(b);
//                float distance = verta.distance(vertb);
//                if (distance <= connectionDistance) {
//                    // In OF_PRIMITIVE_LINES, every pair of vertices or indices will be
//                    // connected to form a line
//                    pointMesh.addIndex(a);
//                    pointMesh.addIndex(b);
//                }
//            }
//        }
    
    fbo.begin();
    ofClear(0,255);
    fbo.end();
    
    glPointSize(2);
    
    
    gui.setup();
//    gui.add(remesh.set("Remesh", false));
    gui.add(guiReduce.set("Reduce", 9, 2, 22));
    gui.add(guiIntensityThreshold.set("Intense Thresh", 2.0, 0.0, 255.0));
    gui.add(guiRndAmt.set("Rand Amt", 3, 0, 10));
    gui.add(guiConnectionDistance.set("Connect Dist", 15, 1, 100));
    gui.add(guiMeshAlpha.set("Alpha", 2, 0, 255));
    gui.add(guiNoiseSpeed.set("Noise Speed", 0.65, 0, 1));
    gui.add(guiNoiseScale.set("Noise Scale", 0.02, 0, 0.2));
    gui.add(guiNoise.set("Do Noise", true));
    
    
    fn = "images/black.png";
    generateVbo(wall);
    
    fn = "images/ai4.png";
    generateVbo(mesh);
    
}
//--------------------------------------------------------------
void ofApp::generateVbo(ofMesh &m){
    m.clear();
    offsets.clear();
    
    int reduce = guiReduce;
    float intensityThreshold = guiIntensityThreshold;
    float rndAmt = guiRndAmt;
    float connectionDistance = guiConnectionDistance;
    int meshAlpha = guiMeshAlpha;
   
    img.load(fn);
    img.resize(img.getWidth()/reduce, img.getHeight()/reduce);
    
    m.setMode(OF_PRIMITIVE_LINES);
    m.enableColors();
    m.enableIndices();
    
    int imW = img.getWidth()/2;
    int imH = img.getHeight()/2;
    
    for (int x=-imW; x<imW; ++x) {
        for (int y=-imH; y<imH; ++y) {
            ofColor c = img.getColor(x + imW , y + imH);
            c.a = meshAlpha;
            float intensity = c.getLightness();
            if (intensity >= intensityThreshold) {
                float saturation = c.getSaturation();
                float z = ofMap(saturation, 0, 255, 0, 1000);

                ofVec3f pos(x*reduce + ofRandom(-rndAmt,rndAmt), y*reduce + ofRandom(-rndAmt,rndAmt), z);
                if(intensity < 30){
                    if( ofRandom(10) < 8 ){
                        m.addVertex(pos);
                        m.addColor(c);
                    }
                } else {
                    m.addVertex(pos);
                    m.addColor(c);
                }
                offsets.push_back(ofVec3f(ofRandom(0,100000), ofRandom(0,100000), ofRandom(0,100000)));
            }
        }
    }
    
    
    int numVerts = m.getNumVertices();
    
    for (int a=0; a<numVerts; ++a) {
        ofVec3f verta = m.getVertex(a);
        for (int b=a+1; b<numVerts; ++b) {
            ofVec3f vertb = m.getVertex(b);
            float distance = verta.distance(vertb);
            if (distance <= connectionDistance) {
                m.addIndex(a);
                m.addIndex(b);
            }
        }
    }

}
//--------------------------------------------------------------
void ofApp::animateMesh(ofMesh &m){
    int numVerts = m.getNumVertices();
    for (int i=0; i<numVerts; ++i) {
        ofVec3f vert = m.getVertex(i);
        
        float time = ofGetElapsedTimef();
        float timeScale = guiNoiseSpeed;
        float displacementScale = guiNoiseScale;
        ofVec3f timeOffsets = offsets[i];
        
        vert.x += (ofSignedNoise(time*timeScale+timeOffsets.x)) * displacementScale;
        vert.y += (ofSignedNoise(time*timeScale+timeOffsets.y)) * displacementScale;
        vert.z += (ofSignedNoise(time*timeScale+timeOffsets.z)) * displacementScale;
        m.setVertex(i, vert);
    }
}
//--------------------------------------------------------------
void ofApp::update(){
    if(save){
        ofPixels savePix;
        fbo.readToPixels(savePix);
        ofSaveImage(savePix, "saved/" + ofGetTimestampString() + ".png");
        save = false;
    }
    
    
    if(guiNoise){
//        int numVerts = mesh.getNumVertices();
//        for (int i=0; i<numVerts; ++i) {
//            ofVec3f vert = mesh.getVertex(i);
//            
//            float time = ofGetElapsedTimef();
//            float timeScale = 0.65;
//            float displacementScale = 0.09;
//            ofVec3f timeOffsets = offsets[i];
//            
//            vert.x += (ofSignedNoise(time*timeScale+timeOffsets.x)) * displacementScale;
//            vert.y += (ofSignedNoise(time*timeScale+timeOffsets.y)) * displacementScale;
//            vert.z += (ofSignedNoise(time*timeScale+timeOffsets.z)) * displacementScale;
//            mesh.setVertex(i, vert);
//        }
        animateMesh(mesh);
        animateMesh(wall);
    }
//    numVerts = pointMesh.getNumVertices();
//    for (int i=0; i<numVerts; ++i) {
//        ofVec3f vert = pointMesh.getVertex(i);
//
//        float time = ofGetElapsedTimef();
//        float timeScale = 0.65;
//        float displacementScale = 0.9;
//        ofVec3f timeOffsets = offsets[i];
//
//        vert.x += (ofSignedNoise(time*timeScale+timeOffsets.x)) * displacementScale;
//        vert.y += (ofSignedNoise(time*timeScale+timeOffsets.y)) * displacementScale;
//        vert.z += (ofSignedNoise(time*timeScale+timeOffsets.z)) * displacementScale;
//        pointMesh.setVertex(i, vert);
//    }
}

//--------------------------------------------------------------
void ofApp::draw(){
//    ofDisableAlphaBlending();
//    ofEnablePointSprites();
//    ofDisableDepthTest();
    ofEnableDepthTest();
    
    fbo.begin();
        if(ofGetKeyPressed(' ')){
            ofClear(0,255);
        }
        
        cam.begin();
    
//    ofPushMatrix();
//    ofScale(16, 16, 16);
//    ofTranslate(30,30,0);
//    pointMesh.draw();
//    ofPopMatrix();
//        shader.begin();
            ofPushMatrix();
//                if(ofGetKeyPressed('r')){
        //            ofRotate(ofGetFrameNum()*0.15, 0, 0, 1);
        //            ofTranslate(0,sin(ofGetFrameNum()*0.01)*100, 0);
//                    ofTranslate(0, 0, sin(ofGetFrameNum()*0.005)*200);
//                }

    
                for(int i = 0 ; i< 1; i++){
//                    ofTranslate(0, 0, -200);
                    ofScale(i+1, i+1, 1);
//                    if(i == 0){
                        mesh.draw();
//                    } else {
                        ofScale(5, 5, 1);
                        ofTranslate(0, 0, -200);
                        wall.draw();
//                    }
                }
            ofPopMatrix();
//        shader.end();
        cam.end();
    fbo.end();
    
    ofEnableAlphaBlending();
    fbo.draw(0,0);
    ofDisableDepthTest();
    ofSetColor(255);
    gui.draw();
//    cout<<ofToString(ofMap(cam.getDistance(), 0, 100000,0,1))<<endl;
}
//--------------------------------------------------------------
void ofApp::neuroLines(){
//    fbo.begin();
//    ofClear(0,255);
//    cam.begin();
//    ofSetColor(255, 60);
//    shader.begin();
//    for(int l = -loops; l < loops; l++){
//        for(int h = -loops; h< loops; h++){
//            for(int j = -loops; j < loops; j++){
//                for(int i = -loops; i < loops; i++){
//                    ofDrawLine(i*dist, dist*l, -dist*loops, j*dist, h*dist, dist*loops);
//                    
//                }
//            }
//        }
//    }
//    shader.end();
//    cam.end();
//    fbo.end();

    fbo.begin();
    if(ofGetKeyPressed(' ')){
        ofClear(255,255);
    }
    cam.begin();
        ofSetColor(67, 133, 245, 10);
        pointMesh.draw();
    
        ofScale(0.7, 1.7, 0.7);
        ofSetColor(234, 66, 53, 10);
        pointMesh.draw();
    
        ofScale(1.7, 0.7, 0.7);
        ofSetColor(252, 188, 5, 10);
        pointMesh.draw();

        ofScale(0.7, 1.7, 0.7);
        ofSetColor(52, 168, 83, 10);
        pointMesh.draw();
    cam.end();
    
    fbo.end();

    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key== 's'){
        save = true;
    }
    
    if(key == 'r'){
        fn = "images/black.png";
        generateVbo(wall);
        
        fn = "images/ai4.png";
        generateVbo(mesh);
    }
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
