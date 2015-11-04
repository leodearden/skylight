#include "skylightSim.h"

//--------------------------------------------------------------
void skylightSim::setup()
{
	ofSetFrameRate(30); // if vertical sync is off, we can go a bit fast... this caps the framerate at 60fps.
	memset(leds, 0xff, sizeof(leds));
	whitening = false;
	puddle.set_pixel(0xff, 0xff, 0xff, 30, 30);
}

//--------------------------------------------------------------
void skylightSim::update(){
	// update pattern
	// 0 = C
	// 1 = M
	// 2 = Y
	// 3 = K

//	leds[uy][ux][0] = whitening ? 0xff : 0;
//	if(++ux == leds_width) {
//		ux = 0;
//		if(++uy == leds_width) {
//			uy = 0;
//		}
//	}
//	if(ux == 0 && uy == 0) {
//		whitening = !whitening;
//	}

	puddle.tick();
}

//--------------------------------------------------------------
void skylightSim::draw(){
	// update image from leds
	image.setFromPixels(
//			&(leds[0][0][0]),
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
