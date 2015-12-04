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
	last_drop(time(NULL))
{
	srand(time(NULL));
}

Puddle::~Puddle()
{
}

void Puddle::tick()
{
	if ((avg_light_level < desired_light_level) && (difftime(time(NULL), last_drop) > 3.0))
	{
		time(&last_drop);
		set_pixel(0xfff, 0xfff, 0xfff, rand() % leds_width, rand() % leds_height);
	}

	for (uint y = 0; y < leds_height; y++)
		for (uint x = 0; x < leds_width; x++)
		{
			propagate(colour_map, result, velocity_map, x, y);
		}
	update_buffers();
}



PixelType *Puddle::get_led_representation()
{
	return &led_representation[0][0][0];
}

void Puddle::propagate(float input[leds_width][leds_height][colour_width],
					   float output[leds_width][leds_height][colour_width],
					   float velocity[leds_width][leds_height][colour_width],
					   uint x,
					   uint y)
{
	float averagePosition[colour_width] = {0};
	float propagationConstants[colour_width] = {0.11,0.1,0.09}; // RGB
	float dampingConstants[colour_width] = {0.01,0.01,0.01}; // RGB
	static const float kernel[kernel_size][kernel_size] = {{1,1,1,1,1},{1,2,2,2,1},{1,2,0,2,1},{1,2,2,2,1},{1,1,1,1,1}};
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
					averagePosition[colour] += input[y + kY][x + kX][colour] * kernel[kX+kOffset][kY+kOffset];
				}
			}
		}
	}

	for (int i = 0; i < colour_width; i++)
	{
		averagePosition[i] /= kernel_size * kernel_size + 7;
		float acceleration = (averagePosition[i] - input[x][y][i]) * propagationConstants[i];
		velocity[x][y][i] += acceleration - (velocity[x][y][i] * dampingConstants[i]);
		output[x][y][i] = input[x][y][i] + velocity[x][y][i];
	}

}


void Puddle::set_pixel(float R, float G, float B, uint x, uint y)
{
	colour_map[y][x][0] = R;
	colour_map[y][x][1] = G;
	colour_map[y][x][2] = B;
}

void Puddle::update_buffers()
{
	avg_light_level = 0;

	for (uint y = 0; y < leds_height; y++)
	{
		for (uint x = 0; x < leds_width; x++)
		{
			for (uint colour = 0; colour < colour_width; colour++)
			{
				colour_map[y][x][colour] = result[y][x][colour];

				if (colour_map[y][x][colour] < 0)
					led_representation[y][x][colour] = 0;
				else if (colour_map[y][x][colour] > 255)
					led_representation[y][x][colour] = 255;
				else
					led_representation[y][x][colour] = (PixelType) colour_map[y][x][colour];

				avg_light_level += (float) led_representation[y][x][colour] / (leds_height * leds_width * colour_width);
			}
		}
	}
}

void Puddle::set_light_level(float level)
{
	desired_light_level = level;
}
