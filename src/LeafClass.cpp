//
//  LeafClass.cpp
//  Eda2016FYP
//
//  Created by Yaxin  on 11/8/16.
//
//

#include "LeafClass.hpp"

LeafClass::LeafClass(){
    initLeaf(0,0,0,0);
}

void LeafClass::initLeaf(float px, float py, float unitLength, ofColor leafColor){
    posX = px;
    posY = py;
    color = leafColor;
    unitLen = unitLength;
}

void LeafClass::setup(){
    path.setStrokeColor(color);
    path.setFillColor(color);

    path.setFilled(true);
    path.setStrokeWidth(unitLen/20);
    
    w = (float)(rand()%360);
}

void LeafClass::rotate(){
    
}

void LeafClass::oscillate(){
    
}

void LeafClass::trackMouse() {
    float x = ofGetMouseX(), y = ofGetMouseY();
    if (fabs(posX - x) < ofGetWindowWidth() / 4 && fabs(posY - y) < ofGetWindowHeight() / 4){
        velocityX = (x - posX)/ofRandom(100, 1000);
        velocityY = (y - posY)/ofRandom(100, 1000);
    }
    else{
        velocityX = (-1)*velocityX;
        velocityY = (-1)*velocityY;
    }
}

void LeafClass::accelerate(float ax, float ay){
    accX = ax;
    accY = ay;
}

void LeafClass::update(){
    velocityX = velocityX + accX;
    velocityY = velocityY + accY;
    posX = posX + velocityX;
    posY = posY + velocityY;
    /*if ((fabs(posX - ofGetWindowWidth()) < 5 || posX < 0) && velocityX!=0)
    {
        velocityX = -velocityX;
    }
    
    if ((fabs(posY - ofGetWindowHeight()) < 5 || posY < 0) && velocityY!=0)
    {
        velocityY = -velocityY;
    }
    
    if (posX > ofGetWindowWidth() || posX < 0)
        posX = ofGetWindowWidth()-5;
    if (posY > ofGetWindowHeight() || posY < 0)
        posY = ofGetWindowHeight()-5;
    */
    /*
    if (posX > ofGetWindowWidth()) posX = ofGetWindowWidth()-5;
    if (posX < 0) posX = 5;
    if (posY > ofGetWindowHeight()) posY = ofGetWindowHeight() - 5;
    if (posY < 0) posY = 5;
    */
    
    path.clear();
    path.moveTo(posX, posY);
    path.lineTo(posX+unitLen, posY+0.4*unitLen);
    path.lineTo(posX+1.8*unitLen, posY+1.5*unitLen);
    path.lineTo(posX+1.0*unitLen, posY+2.0*unitLen);
    path.lineTo(posX+0.0*unitLen, posY+1.9*unitLen);
    path.lineTo(posX+(-1.0)*unitLen, posY+unitLen);
    path.lineTo(posX+(-2.0)*unitLen, posY+0.5*unitLen);
    path.lineTo(posX+(-1.0)*unitLen, posY);
    path.close();
    
    //float angle = (float)(rand()%360)/100;
    w = ofGetFrameNum()*0.001+w;
    ofPoint t;
    t.set(-posX, -posY);
    path.translate(t);
    path.rotate(w, ofVec3f(0,0,1));
    t.set(posX, posY);
    path.translate(t);

}

void LeafClass::draw(){
    path.draw();
}

void LeafClass::shiftTo(float x, float y){
    posX = x;
    posY = y;
}

void LeafClass::setLocation(float x, float y){
    posX = x;
    posY = y;
}

void LeafClass::setSpeed(float x, float y){
    velocityX = x;
    velocityY = y;
}

void LeafClass::setLifetime(float x){
    lifetime = x;
}

float LeafClass::getX(){
    return posX;
}

float LeafClass::getY(){
    return posY;
}

float LeafClass::getVelocityX(){
    return velocityX;
}

float LeafClass::getVelocityY(){
    return velocityY;
}

void LeafClass::seek(float x, float y){
    vec2 normalV = {x - posX,y - posY};
    normalV.normalize();
    vec2 steer = {(float)forceMax*normalV.x, (float)forceMax*normalV.y};
    accelerate(steer.x, steer.y);
}
