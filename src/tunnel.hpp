//
//  tunnel.hpp
//
//
//  Created by stephanie wolff on 11/30/15.
//
//

#ifndef tunnel_hpp
#define tunnel_hpp

#include <stdio.h>
#include "ofMain.h"
#include <vector>

class Tunnel {
public:
    Tunnel();
    void add(int deform);
    int draw(int mouseX, int mouseY, int cursorSize );
    //        0,       1,                 2,      3,           4,              5
    // sphere x,sphere y, z coord of square,rotation, deform bool, sphere radius
    vector <vector <float> > positions;
    int speed;
    float recSize;
    float rotationInit;
    float sphereRadius;
    ofSpherePrimitive sphere;
    bool collision;
    ofTrueTypeFont collisionCounter;
    int collisions;
    int rotateZ;
    
};



#endif /* tunnel_hpp */
