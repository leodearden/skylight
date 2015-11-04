/*
 * Puddle.cpp
 *
 *  Created on: Oct 10, 2015
 *      Author: cassm
 */

#include "Puddle.h"

Puddle::Puddle()
{
}

Puddle::~Puddle()
{
}

void Puddle::tick()
{
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
	float propagationConstants[colour_width] = {0.1,0.1,0.1}; // RGB
	float dampingConstants[colour_width] = {0.1,0.1,0.1}; // RGB

	for (int kX = -1; kX <= 1; kX ++)
	{
		for (int kY = -1; kY <= 1; kY ++)
		{
			if (   x + kX >= 0
				&& x + kX < leds_width
				&& y + kY >= 0
				&& y + kY < leds_height
				&& !(kX == 0 && kY == 0))
			{
				for (uint colour = 0; colour < colour_width; colour++)
				{
					averagePosition[colour] += input[y + kY][x + kX][colour];
				}
			}
		}
	}

	for (int i = 0; i < colour_width; i++)
	{
		averagePosition[i] /= 8;
		float acceleration = input[x][y][i] - averagePosition[i] * propagationConstants[i];
		velocity[x][y][i] += acceleration - (velocity[x][y][i] * dampingConstants[i]);
		output[x][y][i] = input[x][y][i] + velocity[x][y][i];
	}

}

void Puddle::accelerate(float* pixel, float* velocity)
{
	float freq = 0.1;
	float f1 = (2 * 3.14 * freq);

	for (uint colour = 0; colour < colour_width; colour++)
	{
		float val = pixel[colour];
		float x = val > 0 ? val : val * -1;
		float a = -1 * f1 * f1 * val;

		velocity[colour] += a;

		pixel[colour] += velocity[colour];
	}
}

void Puddle::set_pixel(PixelType C, PixelType M, PixelType Y, uint x, uint y)
{
	colour_map[y][x][0] = C;
	colour_map[y][x][1] = M;
	colour_map[y][x][2] = Y;
}

void Puddle::update_buffers()
{
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
			}
		}
	}
}
