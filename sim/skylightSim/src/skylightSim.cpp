#include "skylightSim.h"

//--------------------------------------------------------------
void skylightSim::setup()
{
	ofSetFrameRate(60); // if vertical sync is off, we can go a bit fast... this caps the framerate at 60fps.
	memset(leds, 0xff, sizeof(leds));
	whitening = false;
	puddle.set_light_level(50);
	puddle.set_min_drop_interval(0.01);
	puddle.set_drop_colour(0xff,0xff,0xff);
}

//--------------------------------------------------------------
void skylightSim::update(){
	puddle.tick();
}

//--------------------------------------------------------------
void skylightSim::draw(){
	// update image from leds
	image.setFromPixels(
			puddle.get_led_representation(),
			leds_width,
			leds_height,
			OF_IMAGE_COLOR,
			true);
	// rescale image
	image.resize(leds_width*px_per_led, leds_height*px_per_led);
	// draw image
	image.draw(0,0);
}

//--------------------------------------------------------------
void skylightSim::keyPressed(int key){

}

//--------------------------------------------------------------
void skylightSim::keyReleased(int key){

}

//--------------------------------------------------------------
void skylightSim::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void skylightSim::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void skylightSim::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void skylightSim::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void skylightSim::windowResized(int w, int h){

}

//--------------------------------------------------------------
void skylightSim::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void skylightSim::dragEvent(ofDragInfo dragInfo){

}
