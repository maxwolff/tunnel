#include "ofApp.h"
#include <vector>

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(25);
    frameSpeed = 3;
    tunnelVec.assign(4, tunnel1);
    tunnel1;
    tunnel = 0;
    
    instructions.loadFont("verdana.ttf", 20);

    
    ofEnableDepthTest();
    ofEnableSmoothing();
    ofSetVerticalSync(true);
    ofEnableAntiAliasing();
    
    givenBpm = 120;
    milPerBeat = 1000 * 60/givenBpm;
    /*
     sampleVec.assign(100,0);
     sampleVec[4] = 1;
     sampleCounter = 0;
     */
    
    onsetBool = false;
    int nOutputs = 2;
    int nInputs = 2;
    //int sampleRate = 44100;
    //int bufferSize = 256;
    //int nBuffers = 4;
    cursorSize = 50;
    
    
    // setup onset object
    onset.setup();
    //onset.setup("mkl", 2 * bufferSize, bufferSize, sampleRate);
    
    // setup pitch object
    pitch.setup();

    volume = 0;
   
    sound0.loadSound("teebs.mp3");
    sound0.setVolume(0.20f);
    sound0.setMultiPlay(true);
    sound0.setLoop(true);
    sound0.setSpeed(.5);
    sound0.play();
    
    sound1.loadSound("wav/fullTrack.wav");
    sound1.setVolume(0.01f);
    sound1.setMultiPlay(true);
    sound1.setLoop(true);
    
    
    
    stk::Stk::setSampleRate(44100.0);
    ofSoundStreamSetup(2, 0, 44100, 256, 4);
    track1.openFile(ofToDataPath("wav/drums1.wav",true));
    track2.openFile(ofToDataPath("wav/harmony1.wav",true));
    
    
    // depth / speed * 1frame/sec * 1000 ms/s
    // (600/ 3) * (1/25) * 1000 =
    timeToHit = 8000;

}

void ofApp::exit(){
    ofSoundStreamStop();
    ofSoundStreamClose();
}

void ofApp::audioIn(float * input, int bufferSize, int nChannels){
}

void ofApp::audioOut(float * output, int bufferSize, int nChannels){
    if(tunnel  == 1) {
        if( ofGetElapsedTimeMillis() - levelStart > 3000){
            stk::StkFrames frames(bufferSize,2);
            track1.tick(frames);
                for (int i = 0; i < bufferSize ; i++) {
                    output[2*i] = frames(i,0);
                    output[2*i +1]= frames(i,1);
                }
            onset.audioIn(output , bufferSize, nChannels);
        }
    }
    if(tunnel  ==  2) {
        if( ofGetElapsedTimeMillis() - levelStart > 3000){
            stk::StkFrames frames(bufferSize,2);
            track2.tick(frames);
            
            for (int i = 0; i < bufferSize ; i++) {
                output[2*i] = frames(i,0);
                output[2*i +1]= frames(i,1);
            }
            
            onset.audioIn(output , bufferSize, nChannels);

        }
        
    }
    /*
    if(ofGetElapsedTimeMillis() - levelStart > 40000) {
        ofSleepMillis(1000); 
        tunnel = 2;
        ofLog()<< ofToString(tunnel)<< "here it is" <<endl;
        levelStart = ofGetElapsedTimeMillis();
    }
    */
    // compute onset detection
    
    // compute pitch detection
//    pitch.audioIn(output, bufferSize, nChannels);

}

//--------------------------------------------------------------
void ofApp::update(){
    
    time = ofGetElapsedTimeMillis();
    updates = updates + 1;
    
    if( tunnel == 1){
        onsetThreshold = 1;
    }
    onset.setThreshold(onsetThreshold);
    
    sound1.setVolume(volume);
    
    
}

//--------------------------------------------------------------
void ofApp::draw(){

    if (tunnel == 0 ) {
        ofBackground(0, 0, 0);
        if (gotOnset) ofBackground(collisions * 3, collisions * 3, collisions* 3);
        instructions.drawString("Tunnel" , ofGetWindowWidth()/2, ofGetWindowHeight()/2);
        instructions.drawString("by Max Wolff" , ofGetWindowWidth()/2, ofGetWindowHeight()/2 + 50);
    } if (tunnel == 1){
        
        float thesh = onsetThreshold;
      //  instructions.drawString(ofToString(thesh), 5, 30);
        //cursor
        ofFill();

            if (gotOnset == 1){
                onsetTemp = 1;
            }
            
            time = ofGetElapsedTimeMillis();
            int temp = time / milPerBeat;
            
            if( temp > tunnelNum){
                if (tunnel == 1){
                     tunnel1.add(onsetTemp);
                }
                if (tunnel ==2){
                    tunnel2.add(onsetTemp);
                }
               
                onsetTemp = 0;
                tunnelNum = temp;
                sampleCounter ++;
            }
        
        
        //collisions
        // if not empty, there is a square that is the cursor's plane
        
        collisions = tunnel1.draw(mouseX, mouseY, cursorSize);
        volume = collisions/70.0;
        ofLog()<<ofToString( volume )<< "volume "<<endl;
        ofLog()<<ofToString( collisions )<< "collisions "<<endl;
        
            ofPushMatrix();
                ofTranslate(0,0);
                if (onset.received()) {
                    gotOnset = 1;
                } else {
                    gotOnset = 0;
                }
    //            onsetNovelty = onset.novelty;
    //            onsetThresholdedNovelty = onset.thresholdedNovelty;
    //            
                // update pitch info
                pitchConfidence = pitch.pitchConfidence;
                if (pitch.latestPitch) midiPitch = pitch.latestPitch;
            
                float bpmTotal = calcBpm * updates + beat.bpm;
                bpm = bpmTotal / updates;

            ofPopMatrix();
      //  }
        
       // cam.end();
        
    }
    ofPushMatrix();
    ofTranslate(0,0,0);
    ofSetColor(150,150,80);
    ofFill();
    ofCircle(mouseX, mouseY,cursorSize);
    
    ofNoFill();
    ofRect(ofGetWindowWidth()/2 - 250, ofGetWindowHeight()/2 - 250, 500,500);
    
    ofPopMatrix();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if ( key == 'a') {
        onsetThreshold = onsetThreshold + .5;
    }
    if ( key == 'z') {
        onsetThreshold = onsetThreshold - .5;
    }
    if ( key == '1') {
        tunnel = 0;
    }
    if ( key == '2') {
        tunnel = 1;
        sound0.stop();
        levelStart = ofGetElapsedTimeMillis();
        sound1.play();
       // sound.setVolume(volume);
        
    }
    if ( key == '3') {
        tunnel = 2;
        sound0.stop();
        levelStart = ofGetElapsedTimeMillis();
        sound1.play();
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}
