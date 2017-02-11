#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    //Version 2 despues de GUITHUB
    
    ofEnableSmoothing();
    ofSetCircleResolution(60);
    
  gui = new ofxUISuperCanvas("SYNTH OSC");
    gui->setPosition(15, 15);
    
  gui->addLabel("ON/OFF");
  gui->addToggle("ON/OFF", false, 50, 50);// toggle ON OFF
    
  gui->addSpacer();
    
  vector<string> vnames; vnames.push_back("SIN"); vnames.push_back("SQR"); //............ Crea un vector con los nombres de botones.
    
  gui->addLabel("WAVEFORM", OFX_UI_FONT_MEDIUM);
  ofxUIRadio *radio = gui->addRadio("WF", vnames, OFX_UI_ORIENTATION_VERTICAL);// se crea un objeto UiRadio
  radio->activateToggle("SIN");
    
  gui->addSpacer();
  
  gui->addSlider("FRECUENCY",60,1000,150);
  gui->addSlider("LEVEL",0,1,0.5);
  
    
    gui->addSpacer();
    gui->addLabel("ROTARY SLIDER");
    gui->addRotarySlider("ROTARY", 60.0, 1000.0, &frec);

  gui->autoSizeToFitWidgets();
  ofAddListener(gui->newGUIEvent, this, &ofApp::guiEvent);
  
  int ticksPerBuffer = 8; // 8 * 64 = buffer len of 512
  int numInputs = 1;
    
  ofSoundStreamSetup(2, numInputs, this, 44100, ofxPd::blockSize()*ticksPerBuffer, 3);
    
  if(!pd.init(2, numInputs, 44100, ticksPerBuffer, false)) {
        OF_EXIT_APP(1);
  }
  
  pd.start();
  
  Patch patch = pd.openPatch("pd/PruebaPd.pd");


}

//--------------------------------------------------------------
void ofApp::exit()
{
    gui->saveSettings("settings.xml");
    delete gui;
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackground(150,123,110);
    

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::guiEvent(ofxUIEventArgs &e)
{
    
    if(e.getName() == "LEVEL")
    {
        ofxUISlider *slider = e.getSlider();
        value = slider->getScaledValue();
        pd.sendFloat("envio", value);
        
    }
    
    if(e.getName() == "FRECUENCY")
    {
        ofxUISlider *slider = e.getSlider();
        value = slider->getScaledValue();
        pd.sendFloat("frec", value);
    }

    string name = e.widget->getName();//Se obtiene Nombre de WIDG
    
    if(name == "ON/OFF"){
        
        ofxUIToggle *toggle = (ofxUIToggle *) e.widget;
        val = toggle ->getValue();
        if (val==1){
            pd.sendBang("on");
        }
        if(val==0){
            pd.sendBang("off");
        }
    }
    
    int kind = e.widget->getKind();// Se obtiene Tipo de WIDG
    
    if (kind == OFX_UI_WIDGET_TOGGLE) {
        
        if( name == "SIN"){
        ofxUIToggle *toggle = (ofxUIToggle *) e.widget;
        val = toggle ->getValue();
        pd.sendFloat("sin", val);
        }
    }

    if (kind == OFX_UI_WIDGET_TOGGLE) {
        
        if( name == "SQR"){
        ofxUIToggle *toggle = (ofxUIToggle *) e.widget;
        val = toggle ->getValue();
        pd.sendFloat("sqr", val);
        }
    }
    
    
}

//--------------------------------------------------------------
void ofApp::playTone(int pitch) {
    pd << StartMessage() << "pitch" << pitch << FinishList("tone") << Bang("tone");
}

//--------------------------------------------------------------
void ofApp::audioReceived(float * input, int bufferSize, int nChannels) {
    pd.audioIn(input, bufferSize, nChannels);
}

//--------------------------------------------------------------
void ofApp::audioRequested(float * output, int bufferSize, int nChannels) {
    pd.audioOut(output, bufferSize, nChannels);
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
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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
