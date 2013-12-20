#pragma once

#include "ofMain.h"
#include "ofxSVG.h"
#include "ofxControlPanel.h"

/*typedef struct {
    float x, y, w, h;
} rectangle;
*/
class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
    
        void drawViewportOutline(const ofRectangle & viewport);

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    ofxControlPanel gui;
    ofxSVG svg;
    
    ofVec4f rects_1[2];
    ofVec4f rects_2[2];
    ofVec4f rects_3[2];
    
    vector<ofVec4f> joint_1; //左のジョイント
    vector<ofVec4f> joint_2; //右のジョイント
    
    vector<ofVec4f> joint_3; 
    vector<ofVec4f> joint_4;
    
    vector<ofVec4f> joint_5;
    vector<ofVec4f> joint_6;
    
    vector<ofVec3f> hole;

    
    float width;
    float depth;
    float height;
    float hole_x;
    float hole_y;
    float hole_r;
    
    float fit;
    
    int save_count;
    
    float thickness;
    
    int j1;
    int j2;
    int j3;
    
    ofRectangle viewport;
    ofEasyCam camera;
    ofMesh meshBox;
    ofLight light;
    
    int space;
    float Rotate;
    
};
