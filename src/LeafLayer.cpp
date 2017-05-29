//
//  LeafLayer.cpp
//  Eda2016FYP
//
//  Created by Yaxin  on 11/8/16.
//
//

#include "LeafLayer.hpp"

LeafLayer::LeafLayer(){
    leafColor = ofColor(78, 141, 105);
}

void LeafLayer::setup(){
    
    for (int i=0; i < leafNum; i++){
        LeafClass myLeaf;
        float leafX = ofRandom(0, ofGetWindowWidth());
        float leafY = ofRandom(0, ofGetWindowHeight());
        myLeaf.initLeaf(leafX, leafY, leafUnitLen, leafColor);
        myLeaf.setup();
        leaves.push_back(myLeaf);
    }
}

void LeafLayer::update(){
    // change leaves postion and rotation
    for (int i=0; i < leafNum; i++){
        //leaves[i].trackMouse();
        leaves[i].update();
    }
}

void LeafLayer::draw(){

    for (int i = 0; i < leafNum; i++){
        leaves[i].draw();
    }
}

void LeafLayer::leafGatherTo(std::vector<vec2> Poi){
    
    int point_size = Poi.size();
    if (point_size > 0)
    {
        int poiSample = 8;
        //int poiSample = (int)min(point_size,2800) / 100; // Poi.size() is large
        int poiBase = (int)point_size/poiSample;
        
        for (int i = 0; i < poiSample; i = i+1) {
            
            int point = (int)min(i*poiBase + rand()%poiBase, point_size-1);

            int leafSample = (int) leafNum/poiSample;
            
            for (int j = 0; j < leafSample; j++){
                
                int leafIndex = min(j+leafSample*i, leafNum - 1);
                float vx = 0, vy = 0;
                
                if (fabs(leaves[leafIndex].getX() - Poi[point].x) < 10 && fabs(leaves[leafIndex].getY() - Poi[point].y) < 10)
                {
                    float lx = (float)(5-(rand()%10));
                    float ly = (float)(5-(rand()%10));
                    vx = 0;
                    vy = 0;
                    leaves[leafIndex].setLocation(Poi[point].x+lx, Poi[point].y+ly);
                }
                else{
                    // if go outside of the window
                    if (leaves[leafIndex].getX() > (ofGetWindowWidth() - 3) || leaves[leafIndex].getX() < 3.0)
                    {
                        leaves[leafIndex].setLocation(Poi[point].x, Poi[point].y);
                    }
                    if (leaves[leafIndex].getY() > (ofGetWindowHeight() - 3) || leaves[leafIndex].getY() < 3.0)
                    {
                        leaves[leafIndex].setLocation(Poi[point].x, Poi[point].y);
                    }

                }

                leaves[leafIndex].seek(Poi[point].x, Poi[point].y);
                //cout << "gather works for leaf " << leafIndex << endl;
            }
        }
    }

}

void LeafLayer::growLeaf(std::vector<vec2> Poi) {
    
    int point_size = Poi.size();

    /*------ find new target every 200 frames ------*/
    if (point_size > 0 && ofGetFrameNum()%200 == 0)
    {
        // total tracking target sample number
        int poiSample = min((int)point_size / 2, leafNum);
        
        // number of detected points in each tracking sample
        int poiBase = (int)point_size/poiSample;
        
         for (int i = 0; i < poiSample; i = i+1) {
             // select tracking sample index from all detected
             int point = (int)min(i*poiBase + rand()%poiBase, point_size-1);
             
             // leaf numbers for each target
             int leafSample = (int) leafNum/poiSample;
             for (int j = 0; j < leafSample; j++){
                 
                 int leafIndex = min(j+leafSample*i, leafNum - 1);
  
                 float lx = (float)(50-(rand()%100));
                 float ly = (float)(50-(rand()%100));
                 
                 leaves[leafIndex].setLocation(Poi[point].x+lx, Poi[point].y+ly);
                 leaves[leafIndex].seek(Poi[point].x, Poi[point].y);
                 leaves[leafIndex].setSpeed(0.0f, 0.0f);
                 leaves[leafIndex].setLifetime(255.0f);
             }
         }
    }
}
