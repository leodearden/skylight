#pragma once

#include "ofMain.h"

class skylightSim : public ofBaseApp{

public:

	static const uint leds_width = 60;
	static const uint leds_height = 60;
	static const uint px_per_led = 10;

	void setup();
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

private:
	typedef uint8_t PixelType;
	PixelType leds[leds_width][leds_height][4];
	ofImage image;

	uint ux;
	uint uy;
	bool whitening;

};
