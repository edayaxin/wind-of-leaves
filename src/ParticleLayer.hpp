//
//  ParticleLayer.hpp
//  ParticleSystem
//
//  Created by Yaxin  on 11/27/16.
//
//

#ifndef ParticleLayer_hpp
#define ParticleLayer_hpp

#include <stdio.h>
#include "ofMain.h"
#include "Vec.h"
#include "Particle.hpp"

class yxLayer {
public:
    yxLayer();
        virtual ~yxLayer(){};
    
    void setup();
    void update();
    void gatherMode(std::vector<vec2> roi);
    void repelMode();
    void borderBounce();
    void seekMouse();
    void seekRoi(std::vector<vec2> roi);
    void draw();
    
    void gatherModeColor(std::vector<vec3> roiDepth);
    void seekRoiColor(std::vector<vec3> roiDepth);
    void growRoiColor(std::vector<vec3> roiDepth);
    
    vector <yxParticle> ps;
    int pNum;
    
    float forceX=0.01f;
    float forceY=0.01f;
    
};
#endif /* ParticleLayer_hpp */
