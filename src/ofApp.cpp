#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    ofSetFrameRate(60); // why set framerate??
    //ofToggleFullscreen();
    ofBackground(0);
    ofSetBackgroundAuto(true);

    /*------ 0417 added ------*/
    ofEnableAlphaBlending();
    ofSetWindowShape(1024*1700/1280, 1024);
    
    /* ----------- set up Kinect detection -----------*/
    objDetect.setup();
    
    /* ----------- set up leaf layer -----------*/
    leafLayer.setup();
    
    /* ----------- set up particle layer -----------*/
    layer1.setup();
    
    mainThreadCount = 0;
    
    cout << "window Hight, width" << ofGetWindowHeight()<< " " << ofGetWindowWidth() << endl;
}

//--------------------------------------------------------------
void ofApp::update(){
    /* ----------- Detector and Kinect update -----------------------*/
    roiPoints = objDetect.findByDepth(dRange);
    if ((int)roiPoints.size() == 0){
        objDetect.update();
    }

    /* ----------- Detector and Kinect update 0424 update-----------*/
    roiPointsWithDepth = objDetect.depthList(dRange);
    roiPointsWithDepthPar = objDetect.depthList(dRangePar);
    
    if ((int)roiPointsWithDepth.size() == 0){
        objDetect.update();
    }
    
    /* ----------- leaf layer animation ---------------------------*/
        //------- movement setting -------//
    
        //leafLayer.leafGatherTo(roiPoints);
        leafLayer.growLeaf(roiPoints);
    
    leafLayer.update();
    
   /* ----------- particle layer animation -----------------------*/
        //------- movement setting -------//
        //layer1.seekRoi(roiPoints);
    
        //layer1.seekRoiColor(roiPointsWithDepthPar);
          layer1.growRoiColor(roiPointsWithDepthPar);
        //------- bounder setting -------//
        layer1.repelMode();
        layer1.borderBounce();
        
    layer1.update();
    
    
    /* ----------- thread update -----------------------*/
    mainThreadCount++;
    
    if (mainThreadCount%1000==0){
        cout << "ROI points size " << roiPointsWithDepth.size() << endl;
    }
    
};

//--------------------------------------------------------------
void ofApp::draw(){
    float x = ofMap( ofNoise( ofGetElapsedTimef()*2.0, -1000), 0, 1, 0, ofGetWidth());
    
    for (int i = 0; i < roiPointsWithDepth.size(); i=i+1)
    {
        //cout<<"detected and draw"<<endl;
        
        /*---- color mapping ----*/
        vec4 newColor;
        float alphaValue = fmod(roiPointsWithDepth[i].z,255.0);
        alphaValue = alphaValue - 50;
        if(alphaValue == 0){alphaValue = 50;}
        
        if (roiPointsWithDepth[i].z < 900)
        {
            newColor = {255, 230, 153, alphaValue}; // yellow
        }
        else if(roiPointsWithDepth[i].z < 950)
        {
            newColor = {204, 255, 255,alphaValue}; // blue
        }
        else if(roiPointsWithDepth[i].z < 1000)
        {
            newColor = {255, 230, 255,alphaValue}; // purple
        }
        else if(roiPointsWithDepth[i].z < 1100)
        {
            newColor = {230, 255, 238,alphaValue}; // green
        }
        else
        {
            newColor = {0,0,0,0};
        }
        ofSetColor(newColor.x, newColor.y, newColor.z, newColor.w);
        
        /*---- draw circles -----*/
        int m = roiPointsWithDepth[i].x;
        int n = roiPointsWithDepth[i].y;
        
        //ofDrawCircle(m, n, 2);
    }
    
    /* ----------- particle system drawing ---------------------------*/
     layer1.draw();

    /* ----------- leaf layer drawing ---------------------------*/
    leafLayer.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 'f')
        ofToggleFullscreen();
    if (key == 'k')
        objDetect.stopDetector();
    if (key == 'q'){
         objDetect.stopDetector();
         ofExit();
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
