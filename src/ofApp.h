#pragma once

#include "ofMain.h"
#include "ofxAubio.h"
#include "ofxGui.h"
#include "tunnel.hpp"
#include "ofxStk.h"

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void exit();
    
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    void audioIn(float * input, int bufferSize, int nChannels);
    void audioOut(float * output, int bufferSize, int nChannels);
    
    ofSoundPlayer sound0;
    ofSoundPlayer sound1; 
    
    float timeToHit;
    int levelStart;
    int startTime;
    
    int frameSpeed;
    int givenBpm;
    int calcBpm;
    int updates;
    int collisions;
    float volume;
    
    
    ofTrueTypeFont instructions;
    ofCamera cam; 
    
    int time;
    int milPerBeat;
    int tunnelNum;
    int sampleCounter;
    bool onsetBool;
    int onsetTemp;
    
    int tunnel;
    vector <Tunnel> tunnelVec;
    Tunnel tunnel0;
    Tunnel tunnel1;
    Tunnel tunnel2;
    int cursorSize;
    bool collision; 
    
    
    stk::FileWvIn track1;
    stk::FileWvIn track2;
    
    float * gOutput;
    
    
private:
    ofxAubioOnset onset;
    ofxAubioPitch pitch;
    ofxAubioBeat beat;
    ofxAubioMelBands bands;
    
    ofxPanel pitchGui;
    ofxFloatSlider midiPitch;
    ofxFloatSlider pitchConfidence;
    
    ofxPanel beatGui;
    ofxFloatSlider bpm;
    
    ofxPanel onsetGui;
    ofxFloatSlider gotOnset;
    ofxFloatSlider onsetThreshold;
    ofxFloatSlider onsetNovelty;
    ofxFloatSlider onsetThresholdedNovelty;
    
    ofxPanel bandsGui;
    ofPolyline bandPlot;
};
