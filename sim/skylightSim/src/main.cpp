#include "ofMain.h"
#include "skylightSim.h"

//========================================================================
int main( ){
	ofSetupOpenGL(
			skylightSim::leds_width * skylightSim::px_per_led,
			skylightSim::leds_height * skylightSim::px_per_led,
			OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new skylightSim());

}
