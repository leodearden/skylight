/*
 * Puddle.h
 *
 *  Created on: Oct 10, 2015
 *      Author: cassm
 */

#ifndef SRC_PUDDLE_H_
#define SRC_PUDDLE_H_

#include "ofMain.h"

typedef uint8_t PixelType;

class Puddle {
public:
	static const uint leds_width = 60;
	static const uint leds_height = 60;
	static const uint colour_width = 3;
	Puddle();
	virtual ~Puddle();
	void tick();
	PixelType *get_led_representation();
	void set_pixel(PixelType C, PixelType M, PixelType Y, uint x, uint y);

private:
	void propagate(float input[leds_height][leds_width][colour_width],
			   	   float output[leds_height][leds_width][colour_width],
				   float velocity[leds_width][leds_height][colour_width],
				   uint x,
				   uint y);
	void accelerate(float* pixel, float* velocity);
	void update_buffers();
	PixelType led_representation[leds_height][leds_width][colour_width];
	float colour_map[leds_height][leds_width][colour_width];
	float result[leds_height][leds_width][colour_width];
	float velocity_map[leds_height][leds_width][colour_width];
};

#endif /* SRC_PUDDLE_H_ */
