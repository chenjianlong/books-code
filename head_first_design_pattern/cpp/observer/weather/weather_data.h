/*!
 * \file weather_data.h
 * \brief The Weather_Data class implementation. 
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-04-30
 */
/* $Id$ */

#ifndef WEATHER_DATA_H
#define WEATHER_DATA_H

#include <list>
#include "subject.h"

class Observer;

class Weather_Data : public Subject
{
public:
    Weather_Data();
    virtual ~Weather_Data();

	virtual void register_observer(Observer *o);
	virtual void remove_observer(Observer *o);
	virtual void notify_observers();

	void measurements_changed();

	void set_measurements(float temperature, float humidity, float pressure);
	float get_temperature();
	float get_humidity();
	float get_pressure();

private:
	std::list<Observer*> observers_;
	float temperature_;
	float humidity_;
	float pressure_;
};

inline float Weather_Data::get_temperature() {
	return temperature_;
}

inline float Weather_Data::get_humidity() {
	return humidity_;
}

inline float Weather_Data::get_pressure() {
	return pressure_;
}

#endif /* WEATHER_DATA_H */

