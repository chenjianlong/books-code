/*!
 * \file current_conditions_display.h
 * \brief The Current_Conditions_Display class implementation. 
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-04-29
 */
/* $Id$ */

#ifndef CURRENT_CONDITIONS_DISPLAY_H
#define CURRENT_CONDITIONS_DISPLAY_H

#include "observer.h"
#include "display_element.h"
#include "subject.h"

class Current_Conditions_Display : public Observer, Display_Element
{
public:
    Current_Conditions_Display(Subject *weather_data);
    virtual ~Current_Conditions_Display();

	virtual void update(float temperature, float humidity, float pressure);
	virtual void display();
private:
	float temperature_;
	float humidity_;
	Subject *weather_data_;
};

#endif /* CURRENT_CONDITIONS_DISPLAY_H */

