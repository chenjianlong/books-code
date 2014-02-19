/* $Id$ */

#include <iostream>
#include "forecase_display.h"

Forecase_Display::Forecase_Display(Weather_Data *weather_data) : weather_data_(weather_data)
{
	weather_data_->register_observer(this);
}

Forecase_Display::~Forecase_Display()
{ }

void Forecase_Display::update(float temp, float humidity, float pressure)
{
	last_pressure_ = current_pressure_;
	current_pressure_ = pressure;

	display();
}

void Forecase_Display::display()
{
	std::cout << "Forcast: ";
	if (current_pressure_ > last_pressure_) {
		std::cout << "Improving weather on the way!" << std::endl;
	} else if (current_pressure_ == last_pressure_) {
		std::cout << "More of the same" << std::endl;
	} else if (current_pressure_ < last_pressure_) {
		std::cout << "Watch out for cooler, rainy weather" << std::endl;
	}
}
