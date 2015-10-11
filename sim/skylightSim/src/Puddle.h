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
	static const uint colour_width = 4;
	Puddle();
	virtual ~Puddle();
	void tick();
	PixelType *get_led_representation();
	void set_pixel(PixelType C, PixelType M, PixelType Y, PixelType K, uint x, uint y);

private:
	void propagate(float input[leds_height][leds_width][colour_width],
			   	   float output[leds_height][leds_width][colour_width],
				   uint x,
				   uint y);
	void accelerate(float* pixel, float* velocity);
	void update_buffers();
	PixelType led_representation[leds_height][leds_width][4];
	float colour_map[leds_height][leds_width][4];
	float result[leds_height][leds_width][4];
	float velocity_map[leds_height][leds_width][4];
};

#endif /* SRC_PUDDLE_H_ */
