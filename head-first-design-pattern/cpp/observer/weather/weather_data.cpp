/* $Id$ */

#include <algorithm>
#include "weather_data.h"
#include "observer.h"

Weather_Data::Weather_Data()
{ }

Weather_Data::~Weather_Data()
{ }

void Weather_Data::register_observer(Observer *o)
{
	observers_.push_back(o);
}

void Weather_Data::remove_observer(Observer *o)
{
	using namespace std;

	list<Observer*>::iterator it = find(observers_.begin(), observers_.end(), o);
	if (it != observers_.end()) {
		observers_.remove(o);
	}
}

void Weather_Data::notify_observers()
{
	using namespace std;

	for (list<Observer*>::iterator it = observers_.begin(); it != observers_.end(); it++) {
		(*it)->update(temperature_, humidity_, pressure_);
	}
}

void Weather_Data::measurements_changed()
{
	notify_observers();
}

void Weather_Data::set_measurements(float temperature, float humidity, float pressure)
{
	temperature_ = temperature;
	humidity_ = humidity;
	pressure_ = pressure;
	measurements_changed();
}

