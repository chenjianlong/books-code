/* $Id$ */

#include <iostream>
#include "heat_index_display.h"

Heat_Index_Display::Heat_Index_Display(Weather_Data *weather_data) : weather_data_(weather_data), heat_index_(0.0f)
{
	weather_data_->register_observer(this);
}

Heat_Index_Display::~Heat_Index_Display()
{ }

void Heat_Index_Display::update(float t, float rh, float pressure)
{
	heat_index_ = compute_heat_index(t, rh);

	display();
}

void Heat_Index_Display::display()
{
	std::cout << "Heat index is " << heat_index_ << std::endl;
}

float Heat_Index_Display::compute_heat_index(float t, float rh)
{
		float index = (float)((16.923 + (0.185212 * t) + (5.37941 * rh) - (0.100254 * t * rh) 
			+ (0.00941695 * (t * t)) + (0.00728898 * (rh * rh)) 
			+ (0.000345372 * (t * t * rh)) - (0.000814971 * (t * rh * rh)) +
			(0.0000102102 * (t * t * rh * rh)) - (0.000038646 * (t * t * t)) + (0.0000291583 * 
			(rh * rh * rh)) + (0.00000142721 * (t * t * t * rh)) + 
			(0.000000197483 * (t * rh * rh * rh)) - (0.0000000218429 * (t * t * t * rh * rh)) +
			0.000000000843296 * (t * t * rh * rh * rh)) -
			(0.0000000000481975 * (t * t * t * rh * rh * rh)));
		return index;
}
