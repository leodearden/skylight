/*
 * Puddle.cpp
 *
 *  Created on: Oct 10, 2015
 *      Author: cassm
 */

#include "Puddle.h"
#include <time.h>
#include <assert.h>
#include <stdlib.h>

Puddle::Puddle() :
	avg_light_level(0),
	desired_light_level(0),
	min_drop_interval(1),
	use_random_colours(true),
	last_drop(time(NULL))
{
	srand(time(NULL));
	init_propagation_constants();
}

Puddle::~Puddle()
{
}

void Puddle::tick()
{
	if ((avg_light_level < desired_light_level) && (difftime(time(NULL), last_drop) > min_drop_interval))
	{
		time(&last_drop);
		if (use_random_colours)
		{
			set_pixel(rand() % 2048, rand() % 2048, rand() % 2048, rand() % leds_width, rand() % leds_height);
		}
		else
		{
			double intensity = (rand() % 2048) / 255.0;
			set_pixel(drop_colours[0] * intensity, drop_colours[1] * intensity, drop_colours[2] * intensity, rand() % leds_width, rand() % leds_height);
		}
	}

	for (uint y = 0; y < leds_height; y++)
	{
		for (uint x = 0; x < leds_width; x++)
		{
			propagate(colour_map, result, velocity_map, x, y);
		}
	}

	update_buffers();
}



PixelType *Puddle::get_led_representation()
{
	return &led_representation[0][0][0];
}

void Puddle::propagate(double input[leds_width][leds_height][colour_width],
					   double output[leds_width][leds_height][colour_width],
					   double velocity[leds_width][leds_height][colour_width],
					   uint x,
					   uint y)
{
	double average_position[colour_width] = {0};
	double propagation_constants[colour_width] = {0.0805,0.08,0.0795}; // RGB
	double damping_constants[colour_width] = {0.003,0.003,0.003}; // RGB
	static const int kOffset = kernel_size / 2;

	assert(kernel_size % 2 == 1);
	for (int kX = -kOffset; kX <= kOffset; kX ++)
	{
		for (int kY = -kOffset; kY <= kOffset; kY ++)
		{
			if (   x + kX >= 0
				&& x + kX < leds_width
				&& y + kY >= 0
				&& y + kY < leds_height)
			{
				for (uint colour = 0; colour < colour_width; colour++)
				{
					average_position[colour] += input[y + kY][x + kX][colour] * kernel[kX+kOffset][kY+kOffset];
				}
			}
		}
	}

	for (uint i = 0; i < colour_width; i++)
	{
		double acceleration = (average_position[i] - input[y][x][i]) * propagation_constants[i];
		velocity[y][x][i] += acceleration - (velocity[y][x][i] * damping_constants[i]);
		output[y][x][i] = input[y][x][i] + velocity[y][x][i];
	}

}


void Puddle::set_pixel(double r, double g, double b, uint x, uint y)
{
	colour_map[y][x][0] = r;
	colour_map[y][x][1] = g;
	colour_map[y][x][2] = b;
}

void Puddle::update_buffers()
{
	total_light_level = 0;

	for (uint y = 0; y < leds_height; y++)
	{
		for (uint x = 0; x < leds_width; x++)
		{
			for (uint colour = 0; colour < colour_width; colour++)
			{
				colour_map[y][x][colour] = result[y][x][colour];

				// only display the top half of the wave for now
				if (colour_map[y][x][colour] < 0)
					led_representation[y][x][colour] = 0;

				else if (colour_map[y][x][colour] > 255)
					led_representation[y][x][colour] = 255;

				else
					led_representation[y][x][colour] = (PixelType) colour_map[y][x][colour];

				total_light_level += led_representation[y][x][colour];
			}
		}
	}

	avg_light_level = total_light_level / (leds_height * leds_width * colour_width);
}

void Puddle::set_light_level(double level)
{
	desired_light_level = level;
}

void Puddle::set_min_drop_interval(double interval)
{
	min_drop_interval = interval;
}

void Puddle::set_drop_colour(double r, double g, double b)
{
	if (r == 0 && g == 0 && b == 0)
	{
		use_random_colours = true;
	}

	else
	{
		use_random_colours = false;
		drop_colours[0] = r;
		drop_colours[1] = g;
		drop_colours[2] = b;
	}
}

void Puddle::init_propagation_constants()
{
	double total = 0;
	int k_centre = kernel_size / 2;

	// calculate weightings via inverse square law
	for (int x = 0; x < kernel_size; x++)
	{
		for (int y = 0; y < kernel_size; y++)
		{
			double dx = abs(x - k_centre);
			double dy = abs(y - k_centre);
			double offset_squared = (dx * dx) + (dy * dy);
			kernel[y][x] = 1 / offset_squared;

			if (x == k_centre && y == k_centre)
				kernel[y][x] = 0;

			total += kernel[y][x];
		}
	}

	printf("total = %f\n", total);

	// normalise
	for (int x = 0; x < kernel_size; x++)
	{
		for (int y = 0; y < kernel_size; y++)
		{
			kernel[y][x] /= total;
		}
	}


}
