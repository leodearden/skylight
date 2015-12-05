/*
 * Puddle.h
 *
 *  Created on: Oct 10, 2015
 *      Author: cassm
 */

#ifndef SRC_PUDDLE_H_
#define SRC_PUDDLE_H_

#include <time.h>
#include "ofMain.h"

typedef uint8_t PixelType;

class Puddle {
public:
	static const uint leds_width = 60;
	static const uint leds_height = 60;
	static const uint colour_width = 3;
	static const size_t kernel_size = 7;
	Puddle();
	virtual ~Puddle();
	void tick();
	void set_light_level(float level);
	PixelType *get_led_representation();
	void set_pixel(float R, float G, float B, uint x, uint y);

private:
	void propagate(float input[leds_height][leds_width][colour_width],
			   	   float output[leds_height][leds_width][colour_width],
				   float velocity[leds_width][leds_height][colour_width],
				   uint x,
				   uint y);
	void accelerate(float* pixel, float* velocity);
	void update_buffers();
	void init_propagation_constants();
	PixelType led_representation[leds_height][leds_width][colour_width];
	float colour_map[leds_height][leds_width][colour_width];
	float result[leds_height][leds_width][colour_width];
	float velocity_map[leds_height][leds_width][colour_width];
	float kernel[kernel_size][kernel_size];
	float avg_light_level;
	float desired_light_level;
	time_t last_drop;
};

#endif /* SRC_PUDDLE_H_ */
