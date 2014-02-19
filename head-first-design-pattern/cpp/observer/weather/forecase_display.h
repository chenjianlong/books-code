/*!
 * \file forecase_display.h
 * \brief The Forecase_Display class implementation. 
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-04-29
 */
/* $Id$ */

#ifndef FORECASE_DISPLAY_H
#define FORECASE_DISPLAY_H

#include "observer.h"
#include "display_element.h"
#include "weather_data.h"

class Forecase_Display : public Observer, Display_Element
{
public:
    Forecase_Display(Weather_Data *weather_data);
    virtual ~Forecase_Display();

	virtual void update(float temp, float humidity, float pressure);
	virtual void display();
private:
	float current_pressure_;
	float last_pressure_;
	Weather_Data *weather_data_;
};

#endif /* FORECASE_DISPLAY_H */

