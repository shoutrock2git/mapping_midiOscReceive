#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    ofBackground( 0, 0, 0 );
    
    for( int i = 0; i < 3; i++ ){
        pitchs.push_back( 0 );
        velocitys.push_back( 0 );
    }
    
    receiver.setup(PORT);
    
    nCurveVertices = 16;
    
    curveVertices[0].x = 100;
    curveVertices[0].y = 100;
    curveVertices[1].x = 100;
    curveVertices[1].y = 150;
    curveVertices[2].x = 150;
    curveVertices[2].y = 150;
    curveVertices[3].x = 150;
    curveVertices[3].y = 100;
    
    curveVertices[4].x = 300;
    curveVertices[4].y = 100;
    curveVertices[5].x = 350;
    curveVertices[5].y = 100;
    curveVertices[6].x = 350;
    curveVertices[6].y = 150;
    curveVertices[7].x = 300;
    curveVertices[7].y = 150;
    
    
    curveVertices[8].x = 100;
    curveVertices[8].y = 200;
    curveVertices[9].x = 150;
    curveVertices[9].y = 200;
    curveVertices[10].x = 150;
    curveVertices[10].y = 250;
    curveVertices[11].x = 100;
    curveVertices[11].y = 250;
    
    
    curveVertices[12].x = 300;
    curveVertices[12].y = 200;
    curveVertices[13].x = 350;
    curveVertices[13].y = 200;
    curveVertices[14].x = 350;
    curveVertices[14].y = 250;
    curveVertices[15].x = 300;
    curveVertices[15].y = 250;
    
    
    
    
    
    
    
    
    for (int i = 0; i < nCurveVertices; i++){
        curveVertices[i].bOver 			= false;
        curveVertices[i].bBeingDragged 	= false;
        curveVertices[i].radius = 4;
    }
    
    
    
    
}

//--------------------------------------------------------------
void ofApp::update(){

    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    string msg = "";
    msg += "FPS: " + ofToString( ofGetFrameRate() ) + "\n";
    msg += "receiver: " + ofToString( receiver.hasWaitingMessages() ) + "\n";
    
//    pitchs.clear();
//    velocitys.clear();
    
    // OSCの個数分繰り返す
    int index = 0;
    while(receiver.hasWaitingMessages()) {
        
        ofxOscMessage m;
        receiver.getNextMessage(&m);
        
        string address = m.getAddress();
        vector <string> splitAddress = ofSplitString(address, "/");
        int ch = ofToInt(splitAddress[1]);
        string type = splitAddress[2];
        float value = ofToFloat(splitAddress[3]);
        
        msg += "ch: " + ofToString(ch) + ", type: " + type + ", value: " + ofToString(value) + "\n";
        
        if( type == "pitch" ){
            pitchs[ch] = value;
        }
        
        if( type == "velocity" ){
            velocitys[ch] = value;
        }
        
        index++;
    }
    
    // ビジュアライズ
    drawVisual();
 

    ofSetColor( 0, 0, 0, 255 );
    ofDrawBitmapString( msg, 30, 30 );
}

//--------------------------------------------------------------
void ofApp::drawVisual(){
    
    
    /*
    float ww = ofGetWidth();
    float wh = ofGetHeight();
    
    ofSetColor(250, 0, 0);
    ofCircle( ww * 0.5 - 200 + 200*ofRandom(-1, 1) * 0, wh * 0.5 + 100*ofRandom(-2, 2), velocitys[0]*0.5 );
    ofSetColor(0, 250, 0);
    ofCircle( ww * 0.5 - 200 + 200*ofRandom(-2, 2) * 1, wh * 0.5 + 100*ofRandom(-1, 1), velocitys[1]*0.5 );
    ofSetColor(0, 0, 250);
    ofCircle( ww * 0.5 - 200 + 200*ofRandom(-3, 3) * 2, wh * 0.5 + 100*ofRandom(-0.5, 0.5), velocitys[2]*0.5 );
    ofSetColor(250, 250, 0);
    ofCircle( ww * 0.5 - 200 + 200*ofRandom(-0.5, 0.5) * 3, wh * 0.5 + 100*ofRandom(-1, 1), velocitys[3]*0.5 );
    
    ===================================
 
    for( int i = 0; i < 4; i++ ){
        //ofCircle( ww * 0.5 - 200 + 200 * i, wh * 0.5 - 100, pitchs[i] );
        //ofCircle( ww * 0.5 - 200 + 200 * i, wh * 0.5 + 100, velocitys[i] );
    }
     */
    
    
    
    //------(f)--------------------------------------
    //
    // 		ofCurveVertex
    //
    // 		because it uses catmul rom splines, we need to repeat the first and last
    // 		items so the curve actually goes through those points
    //
    
    
    // sorry about all the if/states here, but to do catmull rom curves
    // we need to duplicate the start and end points so the curve acutally
    // goes through them.
    
    // for i == 0, we just call the vertex twice
    // for i == nCurveVertices-1 (last point) we call vertex 0 twice
    // otherwise just normal ofCurveVertex call
    
    
    
    

    
    
    
    
    // show a faint the non-curve version of the same polygon:
    
//1
 
    ofSetColor(200,200,0,velocitys[0]);
    ofFill();
    ofBeginShape();
    
    for (int i = 0; i < 4; i++){
        
        if (i == 0){
            ofVertex(curveVertices[0].x, curveVertices[0].y); // we need to duplicate 0 for the curve to start at point 0
            ofVertex(curveVertices[0].x, curveVertices[0].y); // we need to duplicate 0 for the curve to start at point 0
        }else if (i == 4){
            ofVertex(curveVertices[i].x, curveVertices[i].y);
            ofVertex(curveVertices[0].x, curveVertices[0].y);	// to draw a curve from pt 6 to pt 0
            ofVertex(curveVertices[0].x, curveVertices[0].y);	// we duplicate the first point twice
        } else {
            ofVertex(curveVertices[i].x, curveVertices[i].y);
        }
    }
    
    ofEndShape();
    
    
    
    ofEnableAlphaBlending();
    ofNoFill();
    
    
    //wire color
    ofSetColor(0,0,0,40);
    
    
    ofBeginShape();
    for (int i = 0; i < 4; i++){
        ofVertex(curveVertices[i].x, curveVertices[i].y);
    }
    ofEndShape(true);
    
    
    //circle color
    ofSetColor(255,255,255,80);
    
    
    for (int i = 0; i < 4; i++){
        if (curveVertices[i].bOver == true) ofFill();
        else ofNoFill();
        ofCircle(curveVertices[i].x, curveVertices[i].y,4);
    }
    
    
    
//2
    ofSetColor(0,200,0,velocitys[1]);
    ofFill();
    ofBeginShape();
    
    for (int i = 4; i < 8; i++){
        
        if (i == 0){
            ofVertex(curveVertices[0].x, curveVertices[0].y); // we need to duplicate 0 for the curve to start at point 0
            ofVertex(curveVertices[0].x, curveVertices[0].y); // we need to duplicate 0 for the curve to start at point 0
        }else if (i == 8){
            ofVertex(curveVertices[i].x, curveVertices[i].y);
            ofVertex(curveVertices[4].x, curveVertices[4].y);	// to draw a curve from pt 6 to pt 0
            ofVertex(curveVertices[4].x, curveVertices[4].y);	// we duplicate the first point twice
        } else {
            ofVertex(curveVertices[i].x, curveVertices[i].y);
        }
    }
    
    ofEndShape();
    ofNoFill();
    
    //wire color
    ofSetColor(0,0,0,40);
    
    
    ofBeginShape();
    for (int i = 4; i < 8; i++){
        ofVertex(curveVertices[i].x, curveVertices[i].y);
    }
    ofEndShape(true);
    
    
    //circle color
    ofSetColor(255,255,255,80);
    
    
    for (int i = 4; i < 8; i++){
        if (curveVertices[i].bOver == true) ofFill();
        else ofNoFill();
        ofCircle(curveVertices[i].x, curveVertices[i].y,4);
    }
    
//3
    ofSetColor(0,0,200,velocitys[2]);
    ofFill();
    ofBeginShape();
    
    for (int i = 8; i < 12; i++){
        
        if (i == 0){
            ofVertex(curveVertices[0].x, curveVertices[0].y); // we need to duplicate 0 for the curve to start at point 0
            ofVertex(curveVertices[0].x, curveVertices[0].y); // we need to duplicate 0 for the curve to start at point 0
        }else if (i == 12){
            ofVertex(curveVertices[i].x, curveVertices[i].y);
            ofVertex(curveVertices[8].x, curveVertices[8].y);	// to draw a curve from pt 6 to pt 0
            ofVertex(curveVertices[8].x, curveVertices[8].y);	// we duplicate the first point twice
        } else {
            ofVertex(curveVertices[i].x, curveVertices[i].y);
        }
    }
    
    ofEndShape();
    
    
    
    ofEnableAlphaBlending();
    ofNoFill();
    
    
    //wire color
    ofSetColor(0,0,0,40);
    
    
    ofBeginShape();
    for (int i = 8; i < 12; i++){
        ofVertex(curveVertices[i].x, curveVertices[i].y);
    }
    ofEndShape(true);
    
    
    //circle color
    ofSetColor(255,255,255,80);
    
    
    for (int i = 8; i < 12; i++){
        if (curveVertices[i].bOver == true) ofFill();
        else ofNoFill();
        ofCircle(curveVertices[i].x, curveVertices[i].y,4);
    }
    
    
//4
    ofSetColor(200,0,0,velocitys[3]);
    ofFill();
    ofBeginShape();
    
    for (int i = 12; i < 16; i++){
        
        if (i == 0){
            ofVertex(curveVertices[0].x, curveVertices[0].y); // we need to duplicate 0 for the curve to start at point 0
            ofVertex(curveVertices[0].x, curveVertices[0].y); // we need to duplicate 0 for the curve to start at point 0
        }else if (i == 16){
            ofVertex(curveVertices[i].x, curveVertices[i].y);
            ofVertex(curveVertices[12].x, curveVertices[12].y);	// to draw a curve from pt 6 to pt 0
            ofVertex(curveVertices[12].x, curveVertices[12].y);	// we duplicate the first point twice
        } else {
            ofVertex(curveVertices[i].x, curveVertices[i].y);
        }
    }
    
    ofEndShape();
    
    
    
    ofEnableAlphaBlending();
    ofNoFill();
    
    
    //wire color
    ofSetColor(0,0,0,40);
    
    
    ofBeginShape();
    for (int i = 12; i < 16; i++){
        ofVertex(curveVertices[i].x, curveVertices[i].y);
    }
    ofEndShape(true);
    
    
    //circle color
    ofSetColor(255,255,255,80);
    
    
    for (int i = 12; i < 16; i++){
        if (curveVertices[i].bOver == true) ofFill();
        else ofNoFill();
        ofCircle(curveVertices[i].x, curveVertices[i].y,4);
    }
   
    
    
    ofDisableAlphaBlending();
    
    
    //-------------------------------------
    

    
    
    
    
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
    
    for (int i = 0; i < nCurveVertices; i++){
        float diffx = x - curveVertices[i].x;
        float diffy = y - curveVertices[i].y;
        float dist = sqrt(diffx*diffx + diffy*diffy);
        if (dist < curveVertices[i].radius){
            curveVertices[i].bOver = true;
        } else {
            curveVertices[i].bOver = false;
        }
    }
     
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    for (int i = 0; i < nCurveVertices; i++){
        if (curveVertices[i].bBeingDragged == true){
            curveVertices[i].x = x;
            curveVertices[i].y = y;
        }
    }
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
    for (int i = 0; i < nCurveVertices; i++){
        float diffx = x - curveVertices[i].x;
        float diffy = y - curveVertices[i].y;
        float dist = sqrt(diffx*diffx + diffy*diffy);
        if (dist < curveVertices[i].radius){
            curveVertices[i].bBeingDragged = true;
        } else {
            curveVertices[i].bBeingDragged = false;
        }
    }
    
}

//--------------------------------------------------------------

void ofApp::mouseReleased(int x, int y, int button){
    
    for (int i = 0; i < nCurveVertices; i++){
        curveVertices[i].bBeingDragged = false;	
    }
    
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