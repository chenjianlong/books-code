/* $Id$ */

#include "weather_station.h"
#include "weather_data.h"
#include "current_conditions_display.h"
#include "statistics_display.h"
#include "forecase_display.h"
#include "heat_index_display.h"

Weather_Station::Weather_Station()
{ }

Weather_Station::~Weather_Station()
{ }

int Weather_Station::main(int argc, char *argv[])
{
	Weather_Data weather_data;
	Current_Conditions_Display current_display(&weather_data);
	Statistics_Display statistics_display(&weather_data);
	Forecase_Display forecase_display(&weather_data);
	Heat_Index_Display heat_index_display(&weather_data);

	weather_data.set_measurements(80, 65, 30.4f);
	weather_data.set_measurements(82, 70, 30.4f);
	weather_data.set_measurements(78, 90, 29.2f);

	return 0;
}
