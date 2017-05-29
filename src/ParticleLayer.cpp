//
//  ParticleLayer.cpp
//  ParticleSystem
//
//  Created by Yaxin  on 11/27/16.
//
//

#include "ParticleLayer.hpp"

yxLayer::yxLayer(){
    pNum = 5000;
}

void yxLayer::setup(){
    
    for (int i = 0; i < pNum; i++) {
        yxParticle p;
        float xInit =(float)ofGetWindowWidth()/2.0 + 10.0;
        float yInit =(float)ofGetWindowHeight()/2.0+ 10.0;
        
        float rx = (float)(500-(rand()%1000));
        float ry = (float)(500-(rand()%1000));
        
        //p.initParticle(xInit+rx, yInit+ry);
        if (i%4 == 0)
        {
            p.initParticle((float)ofGetWindowWidth()*2, (float)ofGetWindowHeight()*2);
            
        }
        else if(i%4 == 1)
        {
            p.initParticle(0, (float)ofGetWindowHeight());
        }
        else if (i%4 == 2)
        {
            p.initParticle((float)ofGetWindowWidth(), 0);
        }
        else
        {
            p.initParticle(0, 0);
        }
        
        p.setup();
        
        //p.applyForce(forceX+rx/1000, forceY+ry/1000);
        ps.push_back(p);
    }
    
}
void yxLayer::update(){
    for (int i = 0; i < pNum; i++) {
        /*if(ps[i].isDead()){
            ps[i].initParticle((float)ofGetWindowWidth()/2.0-50+(rand()%100), (float)ofGetWindowHeight()/2.0-50+(rand()%100));
        }*/
        ps[i].update();
    }
}
void yxLayer::draw(){
    for (int i = 0; i < pNum; i++){
        ps[i].draw();
        //cout << "ps is drawing" << endl;
    }
}
void yxLayer::gatherMode(std::vector<vec2> roi){
    int point_size = roi.size();
    
    if (point_size > 0 && ofGetFrameNum()%10 == 0)
    {
        int poiSample = min((int)point_size / 2, pNum);
        int poiBase = (int)point_size/poiSample;
        
        for (int i = 0; i < poiSample; i = i+1) {
            int point = (int)min(i*poiBase + rand()%poiBase, point_size-1);
            
            int pointSample = (int) pNum/poiSample;
            for (int j = 0; j < pointSample; j++){
                if(ps[i].isDead()){
                    ps[i].initParticle(roi[point].x, roi[point].y);
                }
                ps[i].seek(roi[point].x, roi[point].y);
                ps[i].velocity.set(0.0f, 0.0f);
            }
        }
    }
}

void yxLayer::gatherModeColor(std::vector<vec3> roiDepth){
    int point_size = roiDepth.size();
    
    if (point_size > 0 && ofGetFrameNum()%10 == 0)
    {
        int poiSample = min((int)point_size / 100, pNum);
        int poiBase = (int)point_size/poiSample;
        
        for (int i = 0; i < poiSample; i = i+1) {
            int point = (int)min(i*poiBase + rand()%poiBase, point_size-1);
            
            int pointSample = (int) pNum/poiSample;
            for (int j = 0; j < pointSample; j++){
                if(ps[i].isDead()){
                    ps[i].initParticle(roiDepth[point].x, roiDepth[point].y);
                }
                ps[i].seek(roiDepth[point].x, roiDepth[point].y);
                ps[i].velocity.set(0.0f, 0.0f);
                
                vec4 newColor;
                /*---- color mapping ----*/
                float alphaVlaue = fmod(roiDepth[i].z,255.0);
                //alphaVlaue = 255.0;
                if (roiDepth[i].z < 900)
                {
                    //newColor = {255, 230, 153, alphaVlaue}; // yellow
                    newColor = {255, 255, 255, alphaVlaue};
                }
                else if(roiDepth[i].z < 950)
                {
                    newColor = {153, 214, 255,alphaVlaue}; // blue
                }
                else if(roiDepth[i].z < 1000)
                {
                    newColor = {194, 153, 255,alphaVlaue}; // purple
                }
                else if(roiDepth[i].z < 1100)
                {
                    newColor = {153, 255, 187,alphaVlaue}; // green
                }
                else
                {
                    newColor = {0,0,0,0};
                }
                ps[i].changeColor(newColor);
            }
        }
    }
}

void yxLayer::repelMode(){
    float xInit =(float)ofGetWindowWidth()/2.0;
    float yInit =(float)ofGetWindowHeight()/2.0;
    float rx = (float)(50-(rand()%100));
    float ry = (float)(50-(rand()%100));
    
    //xInit = (float)ofGetMouseX();
    //yInit = (float)ofGetMouseY();
    
    for (int i = 0; i < pNum; i++) {
        if(ps[i].location.x < 0 || ps[i].location.x > (float)ofGetWindowWidth()){
            ps[i].initParticle(xInit, yInit);
            ps[i].applyForce(forceX+rx/1000, forceY+ry/1000);
        }
        if(ps[i].location.y < 0 || ps[i].location.y > (float)ofGetWindowHeight()){
            ps[i].initParticle(xInit, yInit);
            ps[i].applyForce(forceX+rx/1000, forceY+ry/1000);
        }
    }
}

void yxLayer::borderBounce(){
    for (int i = 0; i < pNum; i++) {
        if(ps[i].location.x < 0 || ps[i].location.x > (float)ofGetWindowWidth()){
            ps[i].bounce(true, false);
        }
        if(ps[i].location.y < 0 || ps[i].location.y > (float)ofGetWindowHeight()){
            ps[i].bounce(false, true);
        }
    }
}

void yxLayer::seekMouse(){
    float row = (float)ofGetMouseX();
    float col = (float)ofGetMouseY();
    for (int i = 0; i < pNum; i++) {
        ps[i].seek(row, col);
    }
}

void yxLayer::seekRoi(std::vector<vec2> roi){
    int point_size = roi.size();
    
    if (point_size > 0 && ofGetFrameNum()%10 == 0)
    {
        int poiSample = min((int)point_size / 2, pNum);
        int poiBase = (int)point_size/poiSample;
        
        for (int i = 0; i < poiSample; i = i+1) {
            int point = (int)min(i*poiBase + rand()%poiBase, point_size-1);
            
            int pointSample = (int) pNum/poiSample;
            for (int j = 0; j < pointSample; j++){
                if(ps[i].isDead()){
                    ps[i].initParticle(roi[point].x, roi[point].y);
                }
                ps[i].seek(roi[point].x, roi[point].y);
            }
        }
    }
}

void yxLayer::seekRoiColor(std::vector<vec3> roiDepth){
    int point_size = roiDepth.size();
    
    if (point_size > 0 && ofGetFrameNum()%5 == 0)
    {

        int poiSample = min((int)point_size / 2, pNum);
        int poiBase = (int)point_size/poiSample;
        
        cout << "depth point size is " << point_size << endl;
        cout << "poiSample is " << poiSample << endl;
        cout << "poiBase is " << poiBase << endl;
        
        for (int i = 0; i < poiSample; i = i+1) {
            int point = (int)min(i*poiBase + rand()%poiBase, point_size-1);
            
            int pointSample = (int) pNum/poiSample;
            
            for (int j = 0; j < pointSample; j++){
                if(ps[i].isDead()){
                   // ps[i].initParticle(roiDepth[point].x, roiDepth[point].y);
                }
                ps[i].seek(roiDepth[point].x, roiDepth[point].y);
                
                vec4 newColor;
                /*---- color mapping ----*/
                float alphaValue = fmod(roiDepth[i].z,255.0);
                alphaValue = 255.0;
                if (roiDepth[i].z < 900)
                {
                    newColor = {255, 230, 153, alphaValue}; // yellow
                }
                else if(roiDepth[i].z < 950)
                {
                    newColor = {153, 214, 255,alphaValue}; // blue
                }
                else if(roiDepth[i].z < 1000)
                {
                    newColor = {194, 153, 255,alphaValue}; // purple
                }
                else if(roiDepth[i].z < 1100)
                {
                    newColor = {153, 255, 187,alphaValue}; // green
                }
                else
                {
                    newColor = {0,0,0,0};
                }
                ps[i].changeColor(newColor);
            }
        }
    }
}

void yxLayer::growRoiColor(std::vector<vec3> roiDepth){
    int point_size = roiDepth.size();
    
    if (point_size > 0 && ofGetFrameNum()%250 == 0)
    {
        
        int poiSample = min((int)point_size, pNum);
        
        cout << "depth point size is " << point_size << endl;
        cout << "poiSample is " << poiSample << endl;
        
        for (int i = 0; i < poiSample; i = i+1) {
            if(ps[i].isDead()){
                 ps[i].initParticle(roiDepth[i].x-50+(rand()%100), roiDepth[i].y-50+(rand()%100));
            }
                //ps[i].initParticle(roiDepth[i].x-50+(rand()%100), roiDepth[i].y-50+(rand()%100));
            
                ps[i].seek(ofGetWindowWidth()/2.0 + 20.0, ofGetWindowHeight()/2.0+ 10.0);
                vec4 newColor;
                /*---- color mapping ----*/
                float alphaValue = fmod(roiDepth[i].z,255.0);
                //alphaValue = 255.0;
                if (roiDepth[i].z < 900)
                {
                    //newColor = {255, 230, 153, alphaValue}; // yellow
                    newColor = {255, 255, 255, alphaValue};
                }
                else if(roiDepth[i].z < 950)
                {
                    newColor = {204, 255, 255,alphaValue}; // blue
                }
                else if(roiDepth[i].z < 1000)
                {
                    newColor = {255, 230, 255,alphaValue}; // purple
                }
                else if(roiDepth[i].z < 1100)
                {
                    newColor = {230, 255, 238,alphaValue}; // green
                }
                else
                {
                    newColor = {0,0,0,0};
                }
            
                ps[i].changeColor(newColor);
        }
    }
}
