//
//  tunnel.cpp
//  simpleFinal
//
//  Created by stephanie wolff on 11/30/15.
//
//

#include "tunnel.hpp"
#include <iostream>
#include <vector>

Tunnel::Tunnel(){
    speed = 3;
    recSize = 40;
    rotationInit = 90;
    sphereRadius = 5;
    sphere.setRadius(sphereRadius);
    collisionCounter.loadFont("verdana.ttf", 20);
    rotateZ = 1;
}

void Tunnel::add(int deform){
    std::vector<float> position (7);
    position[3] = rotationInit;
    position[4] = deform;
    position[5] = sphereRadius;
    position[6] = rotateZ;
    positions.push_back(position);
}

int Tunnel::draw(int mouseX, int mouseY, int cursorSize){
 //   collisionCounter.drawString(ofToString(collisions) , 5, 200);
//    ofPushMatrix();
//        ofTranslate(0,0,0);
//     //   ofRect(ofGetWindowWidth()/2 - 300 + .5 * 500,ofGetWindowHeight()/2 - 300 + .5 * 500, 100,100);
//    ofPopMatrix();
    for( int i = 0; i < positions.size(); i++){
        int zCoord = positions[i][2];
        int rotation = positions[i][3];
        
        ofNoFill();
        ofPushMatrix();
            ofTranslate(ofGetWindowWidth()/2 - (recSize/2) ,ofGetWindowHeight()/2 - (recSize/2), zCoord);
        
        //collisions
        if( zCoord > 600 ){
            //there is a square on our plane, there could be a collision
            float deltaX = abs(mouseX - (ofGetWindowWidth()/2 - 250 + positions[i][0] * 500));
            float deltaY = abs(mouseY - (ofGetWindowHeight()/2 - 250 + positions[i][1] * 500));
            float distance = sqrt(deltaX * deltaX + deltaY * deltaY);
            if (distance < positions[i][5] + cursorSize){
                collision = true;
                collisions ++; 
                ofRect(300,300,200,200);
            }else{
                collision = false;
            }
        }
        ofRotateY(rotation);
      //  ofRotateZ(20);
        ofEnableAlphaBlending();
        int opacity;
        if ( zCoord < 300){
            opacity = zCoord - 300;
        }
        if(positions[i][4] == 1){
            ofSetColor(200,100,100, 256 + opacity);
            if (collision) ofSetColor(0,0,0);
            ofRect(0,0, 0, recSize,recSize);
            if ( !positions[i][0]){
                positions[i][0] = ofRandomuf();
                positions[i][1] = ofRandomuf();
            }
            ofPushMatrix();
                if (collision) ofSetColor(250,0,0);
                ofTranslate(recSize * positions[i][0], recSize * positions[i][1], 0);
                sphere.drawWireframe();
            ofPopMatrix();
            
        } else {
            ofSetColor(100,100,200, 256 + opacity);
            ofRect(0,0, 0, recSize,recSize);
        }
    

    // free memory
        if( zCoord > 600 ){
            positions.erase(positions.begin() + i);
            
        }
     
        //rotate
        if ( rotation > 0) {
            positions[i][3] = rotation - rotationInit/630;
        }
        // move in z direction
        positions[i][2] += speed;
        ofPopMatrix();
    }
    ofDisableAlphaBlending();
    return collisions;
}