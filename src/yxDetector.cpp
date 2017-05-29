 //
//  yxDetector.cpp
//  Eda2016FYP
//
//  Created by Yaxin  on 11/23/16.
//
//

#include "yxDetector.hpp"

yxDetector::yxDetector(){
    detectorCount=0;
    
}
yxDetector::~yxDetector(){

}
void yxDetector::setup(){
    kinect.openKinect();
}
void yxDetector::update(){
    
}

void yxDetector::stopDetector(){
    kinect.close();
}
cv::Mat yxDetector::setBackground(cv::Mat background){
    backImg = background;
}

cv::Point yxDetector::getSquareCorner(){
    
}

std::vector<vec2> yxDetector::findByDepth(float depthRange[]){
    std::vector<vec2> marker;
    
    if (kinect.isFrameNew()){
        
        vec2 poi = {(float)rROI, (float)cROI};
        /*
        if (sizeof(depthRange)/sizeof(*depthRange)!=2)
        {
            cerr << "You must have inputted wrong size of depth range..." << endl;
            marker.push_back(poi);
            return marker;
        }
        */
        cv::Mat depthMat = kinect.getDepthMat();
        int row = (int)depthMat.rows;
        int col = (int)depthMat.cols;
            
        /*------ find region of interest to draw ------*/
        int xMax = 0, yMax = 0, xMin = 0, yMin = 0;
        float depMax = 0;
        float depMin = 1000;

        for (int i = rROI; i < rROI+squareWidth; i++ )
        {
            for (int j = cROI; j < cROI+squareWidth; j++)
            {
                // depth value grows as distance increases
                float depthValue = depthMat.at<float>(i,j);
                if (depMax < depthValue) {
                    depMax = depthValue;
                    xMax = i;
                    yMax = j;
                }
                if (depMin > depthValue)
                {
                    depMin = depthValue;
                    xMin = i;
                    yMin = j;
                }
                if (depthValue < depthRange[1] && depthValue > depthRange[0])
                {
                    poi.set(j, i);
                    marker.push_back(poi);
                }
            }
        }
    
        /*------ mapping from Kinect to Screen ------*/
        for (int i = 0; i < marker.size(); i=i+1)
        {
            marker[i].x = fabs((marker[i].x-rROI + xMove)*kToScreen);
            marker[i].y = fabs((marker[i].y-cROI + yMove)*kToScreen);
            
            //marker[i].x = ofGetWindowWidth() - marker[i].x;
            marker[i].y = ofGetWindowHeight() - marker[i].y;
        }

        depthMat.release();
       
        detectorCount++;
    }
    return marker;
}

std::vector<vec3> yxDetector::depthList(float depthRange[]){
    std::vector<vec3> marker;
    
    if (kinect.isFrameNew()){
        
        vec3 poi = {(float)rROI, (float)cROI, 0};
        cv::Mat depthMat = kinect.getDepthMat();
        int row = (int)depthMat.rows;
        int col = (int)depthMat.cols;
        
        /*------ find region of interest to draw ------*/
        int xMax = 0, yMax = 0, xMin = 0, yMin = 0;
        float depMax = 0;
        float depMin = 1000;
        
        for (int i = rROI; i < rROI+squareWidth; i++ )
        {
            for (int j = cROI; j < cROI+squareWidth; j++)
            {
                // depth value grows as distance increases
                float depthValue = depthMat.at<float>(i,j);
                if (depMax < depthValue) {
                    depMax = depthValue;
                    xMax = i;
                    yMax = j;
                }
                if (depMin > depthValue)
                {
                    depMin = depthValue;
                    xMin = i;
                    yMin = j;
                }
                if (depthValue < depthRange[1] && depthValue > depthRange[0])
                {
                    poi.set(j, i, depthValue);
                    marker.push_back(poi);
                }
            }
        }
        
        /*------ mapping from Kinect to Screen ------*/
        for (int i = 0; i < marker.size(); i=i+1)
        {
            marker[i].x = fabs((marker[i].x-rROI + xMove)*kToScreen);
            marker[i].y = fabs((marker[i].y-cROI + yMove)*kToScreen);
            
            //marker[i].x = ofGetWindowWidth() - marker[i].x;
            marker[i].y = ofGetWindowHeight() - marker[i].y;
        }
        
        depthMat.release();
        
        detectorCount++;
    }
    return marker;
}


