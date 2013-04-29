/* $Id$ */

#include <iostream>
#include "current_conditions_display.h"

Current_Conditions_Display::Current_Conditions_Display(Subject *weather_data) : weather_data_(weather_data)
{
	weather_data_->register_observer(this);
}

Current_Conditions_Display::~Current_Conditions_Display()
{ }

void Current_Conditions_Display::update(float temperature, float humidity, float pressure)
{
	temperature_ = temperature;
	humidity_ = humidity;
	display();
}

void Current_Conditions_Display::display()
{
		std::cout << "Current conditions: " << temperature_ << "F degress and " << humidity_ << "\% humidity" << std::endl;
}

