/*!
 * \file statistics_display.h
 * \brief The Statistics_Display class implementation. 
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-04-29
 */
/* $Id$ */

#ifndef STATISTICS_DISPLAY_H
#define STATISTICS_DISPLAY_H

#include "observer.h"
#include "display_element.h"
#include "weather_data.h"

class Statistics_Display : public Observer, Display_Element
{
public:
    Statistics_Display(Weather_Data *weather_data);
    virtual ~Statistics_Display();

	virtual void update(float temp, float humidity, float pressure);
	virtual void display();
private:
	float max_temp_;
	float min_temp_;
	float temp_sum_;
	int num_readings_;
	Weather_Data *weather_data_;
};

#endif /* STATISTICS_DISPLAY_H */

