#pragma once

#include "ofMain.h"
#include "yxKinect.hpp"
#include "yxDetector.hpp"
#include "ParticleLayer.hpp"
#include "LeafLayer.hpp"
#include "Vec.h"
#include "ofxRipples.h"
#include "ofxBounce.h"

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
    
    //ofColor leafColor = ofColor(78, 141, 105);
    LeafLayer leafLayer;

    yxDetector objDetect;
    std::vector<vec2> roiPoints;
    
    std::vector<vec3> roiPointsWithDepth;
    std::vector<vec3> roiPointsWithDepthPar;
    
    std::vector<vec2> roiRegion;
    
    //float dRange[2] = {650, 1135}; //normal: 735, 730; 650,735; 650, 1135
    //float dRange[2] = {730, 800}; // for touch detection
    float dRange[2] = {700, 1100}; // for color mapping
    float dRangePar[2] = {800, 900};
    int mainThreadCount;
    
    yxLayer layer1;
    
    bool sendSerial;
    ofSerial ardSerial;
    int ofDetect;
    
};
