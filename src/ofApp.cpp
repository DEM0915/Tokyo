#include "ofApp.h"

void ofApp::setup(){
    
    ofBackground(0);
    ofSetFullscreen( true );
    ofHideCursor();
    ofSetCircleResolution(91);
    
    tokyo.load("tokyo.jpg");
    real.load( "Real.mp3" );
    real.setLoop( true );
    real.play();
    
    
    for (int i = 0; i < N; i++) {
        spectrum[i] = 0.0f;
        
    }
    
    for ( int j = 0; j < n; j++ ) {
        tx[j] = ofRandom( 0, 1000 );
        ty[j] = ofRandom( 0, 1000 );
    }

}


void ofApp::update(){
    
    ofSoundUpdate();
    
    float *val = ofSoundGetSpectrum( N );
    
    for ( int i=0; i<N; i++ ) {
        spectrum[i] *= 0.97;
        spectrum[i] = max( spectrum[i], val[i] );
    }
    
    float time = ofGetElapsedTimef();
    float dt = time - time0;
    
    dt = ofClamp( dt, 0.0, 0.1 );
    time0 = time;
    Rad = ofMap( spectrum[ bandRad ], 1, 3, 400, 800, true );
    Vel = ofMap( spectrum[ bandVel ], 0, 0.1, 0.05, 0.5 );
    
    for (int j=0; j<n; j++) {
        tx[j] += Vel * dt;
        ty[j] += Vel * dt;
        
        p[j].x = ofSignedNoise( tx[j] ) * Rad;
        p[j].y = ofSignedNoise( ty[j] ) * Rad;
    }

}


void ofApp::draw(){
    
    ofSetColor(255);
    tokyo.draw(0,0, ofGetWidth(), ofGetHeight());
    
    ofSetColor( 7, 7, 7 , 160);
    ofDrawCircle(ofGetWidth()/2, ofGetHeight()/2, 325);
    
    ofFill();
    if(petit){
        
    ofSetColor( 0, 0, 0 );
    for (int i = 0; i < N; i++) {
        
        if ( i == bandRad || i == bandVel ) {
            ofSetColor( 70, 70, 70 , 70 );
        } else {
            
            ofSetColor( 200, 176, 168 );
        }
        ofDrawRectangle( 3 + i * 7, 768, 3, -spectrum[i] * 100 );
    }
        
    }
    
    ofPushMatrix();
    
    ofTranslate( ofGetWidth() / 2, ofGetHeight() / 2 );
    
    
    
    ofSetColor( 255, 255, 255 , 100 );
    ofFill();
    for (int i=0; i<n; i++) {
        ofDrawCircle( p[i], 2 );
    }
    
    float dist = 40;
    for (int j=0; j<n; j++) {
        for (int k=j+1; k<n; k++) {
            if ( ofDist( p[j].x, p[j].y, p[k].x, p[k].y )
                < dist ) {
                ofDrawLine( p[j], p[k] );
            }
        }
    }
    
    ofPopMatrix();

}

void ofApp::keyPressed(int key){
    
    if(key== 't') petit =! petit;
}