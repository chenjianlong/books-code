/* $Id$ */

#include <iostream>
#include "statistics_display.h"

Statistics_Display::Statistics_Display(Weather_Data *weather_data) : weather_data_(weather_data), max_temp_(0.0f), min_temp_(200), temp_sum_(0.0f), num_readings_(0)
{ 
	weather_data_->register_observer(this);
}

Statistics_Display::~Statistics_Display()
{ }

void Statistics_Display::update(float temp, float humidity, float pressure)
{
	temp_sum_ += temp;
	num_readings_++;

	if (temp > max_temp_) {
		max_temp_ = temp;
	}

	if (temp < min_temp_) {
		min_temp_ = temp;
	}

	display();
}

void Statistics_Display::display()
{
	std::cout << "Avg/Max/Min temperature = " << (temp_sum_ / num_readings_) << "/" << max_temp_ << "/" << min_temp_ << std::endl;
}
