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
	static const size_t kernel_size = 59;
	Puddle();
	virtual ~Puddle();
	void tick();
	void set_light_level(double level);
	PixelType *get_led_representation();
	void set_pixel(double R, double G, double B, uint x, uint y);

private:
	void propagate(double input[leds_height][leds_width][colour_width],
			   	   double output[leds_height][leds_width][colour_width],
				   double velocity[leds_width][leds_height][colour_width],
				   uint x,
				   uint y);
	void accelerate(double* pixel, double* velocity);
	void update_buffers();
	void init_propagation_constants();
	PixelType led_representation[leds_height][leds_width][colour_width];
	double colour_map[leds_height][leds_width][colour_width];
	double result[leds_height][leds_width][colour_width];
	double velocity_map[leds_height][leds_width][colour_width];
	double kernel[kernel_size][kernel_size];
	double avg_light_level;
	double desired_light_level;
	time_t last_drop;
};

#endif /* SRC_PUDDLE_H_ */
