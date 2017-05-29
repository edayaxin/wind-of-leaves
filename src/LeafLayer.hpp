//
//  LeafLayer.hpp
//  Eda2016FYP
//
//  Created by Yaxin  on 11/8/16.
//
//

#ifndef LeafLayer_hpp
#define LeafLayer_hpp

#include <stdio.h>
#include <iostream>
#include <algorithm>
#include "ofMain.h"
#include "LeafClass.hpp"
#include "Vec.h"

class LeafLayer{
    
protected:
    vector <LeafClass> leaves;
    
public:
    LeafLayer();
        virtual ~LeafLayer(){};
    
    int leafNum = 100;
    float leafUnitLen = 5;
    int timeFactor = 1000; // the larger the slower
    int speedFactor = 1; // the larger the faster
    ofColor leafColor;
    
    void setup();
    void update();
    void draw();
    
    void growLeaf(std::vector<vec2> Poi);
    void gatherLeaf(std::vector<vec2> Poi);
    void leafGatherTo(std::vector<vec2> Poi);
    
    void leafMover();
    void clear();
};

#endif /* LeafLayer_hpp */
