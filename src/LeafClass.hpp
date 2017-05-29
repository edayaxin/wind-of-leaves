//
//  LeafClass.hpp
//  Eda2016FYP
//
//  Created by Yaxin  on 11/8/16.
//
//

#ifndef LeafClass_hpp
#define LeafClass_hpp

#include <stdio.h>
#include "ofMain.h"
#include "Vec.h"
#include "Particle.hpp"

#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/nonfree/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/nonfree/nonfree.hpp"
#include <opencv2/imgproc/imgproc.hpp>
#include "opencv2/calib3d/calib3d.hpp"

class LeafClass {
    
protected:
    float posX;
    float posY;
    float velocityX=0;
    float velocityY=0;
    float accX=0;
    float accY=0;
    float unitLen;
    
    float w;
    
    float speedFactor = 1; // the larger the faster
    
    ofPath path;
    ofColor color;
    ofColor fillColor;
    
public:
    LeafClass();
        virtual ~LeafClass(){};
    
    void initLeaf(float px, float py, float unitLength, ofColor leafColor);
    
    void setup();
    void update();
    void rotate();
    
    void oscillate();
    void trackMouse();
    void accelerate(float ax, float ay);
    void shiftTo(float x, float y);
    void seek(float x, float y);
    void draw();
    void keyPressed(int key);
    
    float getX();
    float getY();
    float getVelocityX();
    float getVelocityY();
    void setLocation(float x, float y);
    void setSpeed(float x, float y);
    void setLifetime(float x);
    
    float speedMax = 20.0f;
    float forceMax = 0.05f;
    float lifetime = 255.0;
};

#endif /* LeafClass_hpp */
