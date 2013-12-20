#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofSetWindowShape(1200, 800);
    ofEnableAlphaBlending();
    ofBackground(240);
    ofSetFrameRate(60);
    
    //----------------------------------------GUI setup-------
    gui.setup("Box", 950, 0, 250, 580);
    gui.addPanel("1", 1);
    gui.setWhichPanel(0);
    gui.addSlider("Width (mm)", "width", 100, 50, 280, true);
    gui.addSlider("Depth (mm)", "depth", 100, 50, 280, true);
    gui.addSlider("Height (mm)", "height", 100, 50, 280, true);
    gui.addSlider("Thickness (mm)", "thickness", 3, 1, 6, false);
    gui.addSlider("Side_Joints", "joints1", 5, 3, 15, true);
    gui.addSlider("Top_Joints1", "joints2", 5, 3, 15, true);
    gui.addSlider("Top_Joints2", "joints3", 5, 3, 15, true);
    //gui.addToggle("Hole_Set", "hole_set", false);
    //gui.addSlider("Hole_Size", "hole_size", 3, 1, 5, false);
    gui.addSlider("Fit_Joint", "fit", 0.1, 0, 0.5, false);
    /*gui.addToggle("Toggle 1", "toggle1", true);
    gui.addPanel("2", 1);
    gui.setWhichPanel(1);
    gui.addSlider("Slider 2", "slider2", 0, 0, 10, false);
    gui.loadSettings("controlPanelSettings.xml");
    */
    
    //----------------------------------------view setting-------
    viewport.x = 950;
	viewport.y = 600;
	viewport.width = 250;
	viewport.height = 200;
   
    
    space = 15;
    ofNoFill();
    ofSetColor(0, 0, 0);
    ofSetLineWidth(1);
    
    
    for (int i = 0; i < j1;i++ ) {
        ofVec4f R;
        R.set(0,0,0,0);
        joint_1.push_back(R);
        joint_2.push_back(R);
    }
    
    for (int i = 0; i < j2;i++ ) {
        ofVec4f R;
        R.set(0,0,0,0);
        joint_3.push_back(R);
        joint_4.push_back(R);
    }
    
    for (int i = 0; i < j3;i++ ) {
        ofVec4f R;
        R.set(0,0,0,0);
        joint_5.push_back(R);
        joint_6.push_back(R);
    }
    
}

//--------------------------------------------------------------
void testApp::update(){
    
    //----------------------------------------w,d,h setting-------
    width = gui.getValueI("width");
    depth = gui.getValueI("depth");
    height = gui.getValueI("height");
    thickness = gui.getValueF("thickness");
    j1 = int(gui.getValueI("joints1")/2)*2+1;
    j2 = int(gui.getValueI("joints2")/2)*2+1;
    j3 = int(gui.getValueI("joints3")/2)*2+1;
    fit = gui.getValueF("fit");
    //hole_r = gui.getValueF("hole_size");
    
    //----------------------------------------joints update-----
    joint_1.clear();
    joint_2.clear();
    joint_3.clear();
    joint_4.clear();
    joint_5.clear();
    joint_6.clear();
    
    for (int i = 0; i < j1;i++ ) {
        ofVec4f R;
        R.set(0,0,0,0);
        joint_1.push_back(R);
        joint_2.push_back(R);
    }
    
    for (int i = 0; i < j2;i++ ) {
        ofVec4f R;
        R.set(0,0,0,0);
        joint_3.push_back(R);
        joint_4.push_back(R);
    }
    
    for (int i = 0; i < j3;i++ ) {
        ofVec4f R;
        R.set(0,0,0,0);
        joint_5.push_back(R);
        joint_6.push_back(R);
    }

    //----------------------------------------Rect position update-----
    
    for (int i = 0; i < 1; i++ ) {
        rects_1[i].x = 400 - width/2 + thickness;
        rects_1[i].y = 0 - height/2 + thickness;
        rects_1[i].z = width - thickness*2;               
        rects_1[i].w = height - thickness*2;              
        
        rects_2[i].x = 400 - width/2 - depth + thickness ;
        rects_2[i].y = 0 - height/2 + thickness;
        rects_2[i].z = depth - thickness*2;               
        rects_2[i].w = height - thickness*2;             
        
        rects_3[i].x = 400 - width/2 + thickness;
        rects_3[i].y = 0 - height/2 - depth + thickness ;
        rects_3[i].z = width - thickness*2;               
        rects_3[i].w = depth - thickness*2;
    }
    
        //-------------------------Side_Joint position update
    
    for (int i = 0; i < j1 / 2 + 1; i++) {     
        if (j1 % 2 == 1) {
            joint_1[i].x = rects_2[0].x - thickness;
            joint_1[i].y = rects_2[0].y + rects_2[0].w/j1 * 2 * i;
            joint_1[i].z = thickness;
            joint_1[i].w = rects_2[0].w/j1;
        }else{
            if (i < j1 / 2) {
                joint_1[i].x = rects_2[0].x - thickness;
                joint_1[i].y = rects_2[0].y + rects_2[0].w/j1*2*i;
                joint_1[i].z = thickness;
                joint_1[i].w = rects_2[0].w/j1;
            }
        }
    }
    
    for (int i = 0; i < j1 / 2; i++) {
        joint_2[i].x = rects_2[0].x - thickness*2 + depth;
        joint_2[i].y = rects_2[0].y + rects_2[0].w/j1*(i*2+1)-fit/2;
        joint_2[i].z = thickness;
        joint_2[i].w = rects_2[0].w/j1+fit;
    }
    
        //-------------------------Top_Joint1 position update
    
    for (int i = 0; i < j2 / 2 + 1; i++) {
        if (j2 % 2 == 1) {
            joint_3[i].x = rects_3[0].x + rects_3[0].z/j2 * 2 * i;
            joint_3[i].y = rects_3[0].y -thickness;
            joint_3[i].z = rects_3[0].z/j2;
            joint_3[i].w = thickness;
        }else{
            if (i < j2 / 2) {
                joint_3[i].x = rects_3[0].x + rects_3[0].z/j2 * 2 * i;
                joint_3[i].y = rects_3[0].y -thickness;
                joint_3[i].z = rects_3[0].z/j2;
                joint_3[i].w = thickness;
            }
        }
    }
    
    for (int i = 0; i < j2 / 2; i++) {
        joint_4[i].x = rects_1[0].x + rects_3[0].z/j2*(i*2+1) - fit/2;
        joint_4[i].y = rects_1[0].y - thickness;
        joint_4[i].z = rects_1[0].z/j2 + fit;
        joint_4[i].w = thickness;
    }
    
        //-------------------------Top_Joint2 position update
    
    for (int i = 0; i < j3 / 2 + 1; i++) {
        if (j3 % 2 == 1) {
            joint_5[i].x = rects_3[0].x - thickness;
            joint_5[i].y = rects_3[0].y + rects_3[0].w/j3 * 2 * i;
            joint_5[i].z = thickness;
            joint_5[i].w = rects_3[0].w/j3;
        }else{
            if (i < j3 / 2) {
                joint_5[i].x = rects_3[0].x - thickness;
                joint_5[i].y = rects_3[0].y + rects_3[0].w/j3*2*i;
                joint_5[i].z = thickness;
                joint_5[i].w = rects_3[0].w/j3;
            }
        }
    }
    
    for (int i = 0; i < j3 / 2; i++) {
        joint_6[i].x = rects_2[0].x + rects_2[0].z/j3*(i*2 + 1) - fit/2;
        joint_6[i].y = rects_2[0].y - thickness;
        joint_6[i].z = rects_2[0].z/j3 + fit;
        joint_6[i].w = thickness;
    }
    
    //----------------------------------------3Dview---
    meshBox.clearVertices();
    meshBox.clear();
    
    meshBox.addVertex(ofVec3f(width/4 ,depth/4, -height/4));
    meshBox.addVertex(ofVec3f(width/4 , -depth/4, -height/4));
    meshBox.addVertex(ofVec3f(-width/4 , -depth/4, -height/4));
    meshBox.addVertex(ofVec3f(-width/4 , depth/4, -height/4));
    meshBox.addVertex(ofVec3f(width/4 , depth/4, height/4));
    meshBox.addVertex(ofVec3f(width/4 , -depth/4, height/4));
    meshBox.addVertex(ofVec3f(-width/4 , -depth/4, height/4));
    meshBox.addVertex(ofVec3f(-width/4 ,depth/4, height/4));
    
    
    meshBox.addTriangle(0,1,2);
    meshBox.addTriangle(2,3,0);
    meshBox.addTriangle(4,5,6);
    meshBox.addTriangle(6,7,4);
    meshBox.addTriangle(0,1,4);
    meshBox.addTriangle(4,1,5);
    meshBox.addTriangle(5,1,2);
    meshBox.addTriangle(2,5,6);
    meshBox.addTriangle(6,2,3);
    meshBox.addTriangle(3,6,7);
    meshBox.addTriangle(7,3,0);
    meshBox.addTriangle(0,7,4);
    
    //----------------------------------------3D Rotate----------
    if (Rotate > 360) {
        Rotate = 0;
    }else{
        Rotate += 0.8;
    }
    
    
    //----------------------------------------GUI update---------------
    gui.update();
}

//--------------------------------------------------------------
void testApp::draw(){
    

    
    //----------------------------------------3Dview draw---
    ofPushMatrix();
    ofEnableSmoothing();
    drawViewportOutline(viewport);
	camera.begin(viewport);
    
    
    ofRotateX(-80);
    ofRotateY(0);
    ofRotateZ(Rotate);
    
    ofNoFill();
    ofSetLineWidth(1);
    ofSetColor(120, 120, 220);
    meshBox.drawWireframe();
	ofSphere(0, 0, 0, 1);
    //ofDrawGridPlane(1000);
    
	camera.end();
    ofDisableSmoothing();
    
    
    //----------------------------------------plan------------
   
    ofTranslate(0, ofGetWindowHeight()/2); //positioning
    
    for (int i = 0; i < 1; i++ ) {
        ofRect(rects_1[i].x, rects_1[i].y, rects_1[i].z, rects_1[i].w);
        ofRect(rects_1[i].x + width + depth + space*2, rects_1[i].y, rects_1[i].z, rects_1[i].w);
        
        ofRect(rects_2[i].x - space, rects_2[i].y, rects_2[i].z, rects_2[i].w);
        ofRect(rects_2[i].x + width + depth + space, rects_2[i].y, rects_2[i].z, rects_2[i].w);
        
        ofRect(rects_3[i].x, rects_3[i].y -  space, rects_3[i].z, rects_3[i].w);
        ofRect(rects_3[i].x, rects_3[i].y + depth + height + space, rects_3[i].z, rects_3[i].w);
    }
    
    //----------------------------------------joints_parts 1~2------
    for (int i = 0; i < j1/2 + 1; i++ ) {
        
        ofRect(joint_1[i].x - space, joint_1[i].y, joint_1[i].z, joint_1[i].w);//  □
        ofRect(joint_2[i].x - space, joint_2[i].y, joint_2[i].z, joint_2[i].w);//■ □ □ □
                                                                               //  □
        
        ofRect(joint_1[i].x + depth , joint_1[i].y, joint_1[i].z, joint_1[i].w);//  □
        ofRect(joint_2[i].x + width , joint_2[i].y, joint_2[i].z, joint_2[i].w);//□ ■ □ □
                                                                               //   □
        
        ofRect(joint_1[i].x + width + depth + space, joint_1[i].y, joint_1[i].z, joint_1[i].w);//  □
        ofRect(joint_2[i].x + width + depth + space, joint_2[i].y, joint_2[i].z, joint_2[i].w);//□ □ ■ □
                                                                                               //  □
        
        ofRect(joint_1[i].x + depth*2 + width + space*2, joint_1[i].y, joint_1[i].z, joint_1[i].w);//  □
        ofRect(joint_2[i].x + width*2 + depth + space*2, joint_2[i].y, joint_2[i].z, joint_2[i].w);//□ □ □ ■
                                                                                                   //  □
        
        }
    //----------------------------------------joint_parts 3~4------
    for (int i = 0; i < j2/2 + 1; i++ ) {
        
        ofRect(joint_3[i].x, joint_3[i].y - space, joint_3[i].z, joint_3[i].w);
        ofRect(joint_4[i].x, joint_4[i].y, joint_4[i].z, joint_4[i].w);
        
        ofRect(joint_3[i].x, joint_3[i].y + depth - thickness - space, joint_3[i].z, joint_3[i].w);
        ofRect(joint_4[i].x, joint_4[i].y + height - thickness, joint_4[i].z , joint_4[i].w);
        
        ofRect(joint_3[i].x, joint_3[i].y + depth + height + space, joint_3[i].z, joint_3[i].w);
        ofRect(joint_4[i].x + width + depth + space*2, joint_4[i].y, joint_4[i].z, joint_4[i].w);
        
        ofRect(joint_3[i].x, joint_3[i].y + depth*2 + height -thickness + space, joint_3[i].z, joint_3[i].w);
        ofRect(joint_4[i].x + width + depth + space*2, joint_4[i].y + height - thickness, joint_4[i].z, joint_4[i].w);
        
    }
    //----------------------------------------joint_parts 5~6------
    for (int i = 0; i < j3/2 + 1; i++ ) {
        
        ofRect(joint_5[i].x, joint_5[i].y -  space, joint_5[i].z, joint_5[i].w);
        ofRect(joint_6[i].x - space, joint_6[i].y, joint_6[i].z, joint_6[i].w);
        
        ofRect(joint_5[i].x + width - thickness, joint_5[i].y -  space, joint_5[i].z, joint_5[i].w);
        ofRect(joint_6[i].x - space, joint_6[i].y + height - thickness, joint_6[i].z, joint_6[i].w);
        
        ofRect(joint_5[i].x, joint_5[i].y + depth + height + space, joint_5[i].z, joint_5[i].w);
        ofRect(joint_6[i].x + width + depth + space, joint_6[i].y, joint_6[i].z, joint_6[i].w);
        
        ofRect(joint_5[i].x + width - thickness, joint_5[i].y + depth + height + space, joint_5[i].z, joint_5[i].w);
        ofRect(joint_6[i].x + width + depth + space, joint_6[i].y + height - thickness, joint_6[i].z, joint_6[i].w);
        
    }
    
    //-------------------------------------------------------
    ofRect(rects_3[0].x - thickness, rects_3[0].y -  space-thickness, thickness, thickness);
    ofRect(rects_3[0].x - thickness, rects_3[0].y -  space+rects_3[0].w, thickness, thickness);
    ofRect(rects_3[0].x + rects_3[0].z, rects_3[0].y -  space-thickness, thickness, thickness);
    ofRect(rects_3[0].x + rects_3[0].z, rects_3[0].y -  space+rects_3[0].w, thickness, thickness);
    
    ofRect(rects_3[0].x - thickness, rects_3[0].y -thickness+ depth + height + space, thickness, thickness);
    ofRect(rects_3[0].x - thickness, rects_3[0].y +rects_3[0].w+ depth + height + space, thickness, thickness);
    ofRect(rects_3[0].x + rects_3[0].z, rects_3[0].y -thickness+ depth + height + space, thickness, thickness);
    ofRect(rects_3[0].x + rects_3[0].z, rects_3[0].y +rects_3[0].w+ depth + height + space, thickness, thickness);

    ofPopMatrix();
    //----------------------------------------hole---------------
    
    /*if (gui.getValueB("hole_set")) {
        ofCircle(hole_x, hole_y, hole_r);
        ofLine(hole_x , 0, hole_x , ofGetWindowHeight());
        ofLine(0, hole_y , ofGetWindowWidth(), hole_y);
    }
    */
    
    
    //---------------------------------------saveAction---------
    if (save_count > 0) {
        ofFill();
        ofSetColor(240,save_count);
        ofSetLineWidth(0);
        
        ofRect(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
        
        save_count -= 3;
    }
    
    if (save_count<0) {
        save_count=0;
    }

    //----------------------------------------GUI draw---------------
    gui.draw();
    
    
    //----------------------------------------information-------------
    ofSetColor(150);
    string info = "FPS:" + ofToString(ofGetFrameRate())
                    + "\n" + "[s] = save as .svg"
                    + "\n" + "[g] = hide GUI Panel";
    ofDrawBitmapString(info, 10, 30);


}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    if ( key == 'g' ) gui.hidden = !gui.hidden;
    
    
}

//--------------------------------------------------------------

void testApp::drawViewportOutline(const ofRectangle & viewport){
	ofPushStyle();
    ofNoFill();
	ofSetColor(230);
	ofSetLineWidth(2.0f);
	ofRect(viewport);
	ofPopStyle();
}

void testApp::keyReleased(int key){
    
    //----------------------------------------svg export--------
    if (key == 's') {
        save_count=270;
        svg.addLayer("layer");
        
        svg.translate(0, 400);
        svg.fill("none");
        svg.stroke("#f00", 0.01);
        
        svg.text("※グループ化されている展開図を[合体]してください", 200, 100);
        svg.text("(合成するオブジェクトを選択 → [ウィンドウ] → [パスファインダ] → [合体])", 200, 120);
        
        //-------------------------------------Rect 1
        svg.groupBegin();
        { svg.rect(rects_1[0].x, rects_1[0].y, rects_1[0].z, rects_1[0].w);
            for (int i = 0; i < j1/2 + 1; i++ ) {
                svg.rect(joint_1[i].x + depth , joint_1[i].y, joint_1[i].z, joint_1[i].w);
                if (i < j1/2) {
                    svg.rect(joint_2[i].x + width , joint_2[i].y, joint_2[i].z, joint_2[i].w);
                }
            }
            for (int i = 0; i < j2/2 ; i++ ) {
                svg.rect(joint_4[i].x, joint_4[i].y, joint_4[i].z, joint_4[i].w);
                svg.rect(joint_4[i].x, joint_4[i].y + height - thickness, joint_4[i].z, joint_4[i].w);
            }
        }
        svg.groupEnd();
        
        //-------------------------------------Rect 2
        svg.groupBegin();
        {svg.rect(rects_1[0].x + width + depth + space*2, rects_1[0].y, rects_1[0].z, rects_1[0].w);
            for (int i = 0; i < j1/2 + 1; i++ ) {
                svg.rect(joint_1[i].x + depth*2 + width + space*2, joint_1[i].y, joint_1[i].z, joint_1[i].w);
                if (i < j1/2) {
                    svg.rect(joint_2[i].x + width*2 + depth + space*2, joint_2[i].y, joint_2[i].z, joint_2[i].w);
                }
                
            }
            for (int i = 0; i < j2/2 ; i++ ) {
                svg.rect(joint_4[i].x + width + depth + space*2, joint_4[i].y, joint_4[i].z, joint_4[i].w);
                svg.rect(joint_4[i].x + width + depth + space*2, joint_4[i].y + height - thickness, joint_4[i].z, joint_4[i].w);
            }
        }
        svg.groupEnd();
        
        //-------------------------------------Rect 3
        svg.groupBegin();
        {
            svg.rect(rects_2[0].x - space, rects_2[0].y, rects_2[0].z, rects_2[0].w);
            for (int i = 0; i < j1/2 + 1; i++ ) {
                svg.rect(joint_1[i].x - space, joint_1[i].y, joint_1[i].z, joint_1[i].w);
                if (i < j1/2) {
                    svg.rect(joint_2[i].x - space, joint_2[i].y, joint_2[i].z, joint_2[i].w);
                }
            }
            for (int i = 0; i < j3/2 ; i++ ) {
                svg.rect(joint_6[i].x - space, joint_6[i].y, joint_6[i].z, joint_6[i].w);
                svg.rect(joint_6[i].x - space, joint_6[i].y + height - thickness, joint_6[i].z, joint_6[i].w);
                
            }
        }
        svg.groupEnd();
        
        //-------------------------------------Rect 4
        svg.groupBegin();
        {
            svg.rect(rects_2[0].x + width + depth + space, rects_2[0].y, rects_2[0].z, rects_2[0].w);
            for (int i = 0; i < j1/2 + 1; i++ ) {
                svg.rect(joint_1[i].x + width + depth + space, joint_1[i].y, joint_1[i].z, joint_1[i].w);
                if (i < j1/2) {
                    svg.rect(joint_2[i].x + width + depth + space, joint_2[i].y, joint_2[i].z, joint_2[i].w);
                }
            }
            
            for (int i = 0; i < j3/2; i++ ) {
                svg.rect(joint_6[i].x + width + depth + space, joint_6[i].y, joint_6[i].z, joint_6[i].w);
                svg.rect(joint_6[i].x + width + depth + space, joint_6[i].y + height - thickness, joint_6[i].z, joint_6[i].w);
            }
        }
        svg.groupEnd();
        
        //-------------------------------------Rect 5
        svg.groupBegin();
        {
            svg.rect(rects_3[0].x, rects_3[0].y -  space, rects_3[0].z, rects_3[0].w);
            for (int i = 0; i < j2/2 + 1; i++ ) {
                svg.rect(joint_3[i].x, joint_3[i].y - space, joint_3[i].z, joint_3[i].w);
                svg.rect(joint_3[i].x, joint_3[i].y + depth - thickness - space, joint_3[i].z, joint_3[i].w);
            }
            for (int i = 0; i < j3/2 + 1; i++ ) {
                svg.rect(joint_5[i].x, joint_5[i].y -  space, joint_5[i].z, joint_5[i].w);
                svg.rect(joint_5[i].x + width - thickness, joint_5[i].y -  space, joint_5[i].z, joint_5[i].w);
            }
            svg.rect(rects_3[0].x - thickness, rects_3[0].y -  space-thickness, thickness, thickness);
            svg.rect(rects_3[0].x - thickness, rects_3[0].y -  space+rects_3[0].w, thickness, thickness);
            svg.rect(rects_3[0].x + rects_3[0].z, rects_3[0].y -  space-thickness, thickness, thickness);
            svg.rect(rects_3[0].x + rects_3[0].z, rects_3[0].y -  space+rects_3[0].w, thickness, thickness);
        }
        svg.groupEnd();
        
        //-------------------------------------Rect 6
        svg.groupBegin();
        {
            svg.rect(rects_3[0].x, rects_3[0].y + depth + height + space, rects_3[0].z, rects_3[0].w);
            
            for (int i = 0; i < j2/2 + 1; i++ ) {
                svg.rect(joint_3[i].x, joint_3[i].y + depth + height + space, joint_3[i].z, joint_3[i].w);
                svg.rect(joint_3[i].x, joint_3[i].y + depth*2 + height -thickness + space, joint_3[i].z, joint_3[i].w);
            }
            for (int i = 0; i < j3/2 + 1; i++ ) {
                svg.rect(joint_5[i].x, joint_5[i].y + depth + height + space, joint_5[i].z, joint_5[i].w);
                svg.rect(joint_5[i].x + width - thickness, joint_5[i].y + depth + height + space, joint_5[i].z, joint_5[i].w);
            }
            svg.rect(rects_3[0].x - thickness, rects_3[0].y -thickness+ depth + height + space, thickness, thickness);
            svg.rect(rects_3[0].x - thickness, rects_3[0].y +rects_3[0].w+ depth + height + space, thickness, thickness);
            svg.rect(rects_3[0].x + rects_3[0].z, rects_3[0].y -thickness+ depth + height + space, thickness, thickness);
            svg.rect(rects_3[0].x + rects_3[0].z, rects_3[0].y +rects_3[0].w+ depth + height + space, thickness, thickness);
        }
        svg.groupEnd();
        /*ofFileDialogResult saveFileResult = ofSystemSaveDialog(ofGetTimestampString() , "Save your file");
         if (saveFileResult.bSuccess){
         svg.saveToFile("Rect_"+ofToString(ofGetTimestampString())+".svg");
         }
         */
        
        //-------------------------------------Save Window
        
        ofFileDialogResult saveFileResult = ofSystemSaveDialog(ofGetTimestampString() , "Save your file");
        
        if (saveFileResult.bSuccess){
            svg.saveToFile(saveFileResult.getPath() + ".svg");
            
        }
        
        
    }else{}
    


}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
    /*if (x<900) {
        hole_x = x - 5;
        hole_y = y - 5;
    }else{
        hole_x = -100;
        hole_y = -100;
    }
     */
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
     gui.mouseDragged(x, y, button);
    
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
     gui.mousePressed(x, y, button);
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
     gui.mouseReleased();
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}