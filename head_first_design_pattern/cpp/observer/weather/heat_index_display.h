/*!
 * \file heat_index_display.h
 * \brief The Heat_Index_Display class implementation. 
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-04-29
 */
/* $Id$ */

#ifndef HEAT_INDEX_DISPLAY_H
#define HEAT_INDEX_DISPLAY_H

#include "observer.h"
#include "display_element.h"
#include "weather_data.h"

class Heat_Index_Display : public Observer, Display_Element
{
public:
    Heat_Index_Display(Weather_Data *weather_data);
    virtual ~Heat_Index_Display();

	virtual void update(float t, float rh, float pressure);
	virtual void display();

private:
	float compute_heat_index(float t, float rh);

private:
	float heat_index_;
	Weather_Data *weather_data_;
};

#endif /* HEAT_INDEX_DISPLAY_H */

