/*
 * Puddle.h
 *
 *  Created on: Oct 10, 2015
 *      Author: cassm
 */

#ifndef SRC_PUDDLE_H_
#define SRC_PUDDLE_H_

#include <time.h>
#include <random>
#include "ofMain.h"

typedef uint8_t PixelType;

class Puddle {
public:
	static const uint leds_width = 60;
	static const uint leds_height = 60;
	static const uint colour_width = 3;
	static const size_t kernel_size = 29;
	Puddle();
	virtual ~Puddle();
	void tick();
	void set_light_level(float level);
	void set_min_drop_interval(float interval);
	void set_std_dev(float val);
	PixelType *get_led_representation();
	void set_pixel(float r, float g, float b, uint x, uint y);
	void set_drop_colour(float r, float g, float b);

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
	std::default_random_engine generator;
	float colour_map[leds_height][leds_width][colour_width];
	float result[leds_height][leds_width][colour_width];
	float velocity_map[leds_height][leds_width][colour_width];
	float kernel[kernel_size][kernel_size];
	float drop_colours[colour_width];
	float avg_light_level;
	float total_light_level;
	float desired_light_level;
	float min_drop_interval;
	float std_dev;
	time_t last_drop;
	bool use_random_colours;
};

#endif /* SRC_PUDDLE_H_ */
