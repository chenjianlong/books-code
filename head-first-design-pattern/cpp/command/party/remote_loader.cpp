/* $Id$ */

#include <iostream>
#include "remote_loader.h"
#include "remote_control.h"
#include "light_on_command.h"
#include "stereo_on_command.h"
#include "tv_on_command.h"
#include "hottub_on_command.h"
#include "light_off_command.h"
#include "stereo_off_command.h"
#include "tv_off_command.h"
#include "hottub_off_command.h"
#include "macro_command.h"

using std::cout;
using std::endl;

Remote_Loader::Remote_Loader()
{ }

Remote_Loader::~Remote_Loader()
{ }

int Remote_Loader::main(int argc, char *argv[])
{
	Remote_Control control;
	Light light("Living Room");
	TV tv("Living Room");
	Stereo stereo("Living Room");
	Hottub hottub;
	Light_On_Command light_on(light);
	Stereo_On_Command stereo_on(stereo);
	TV_On_Command tv_on(tv);
	Hottub_On_Command hottub_on(hottub);
	Light_Off_Command light_off(light);
	Stereo_Off_Command stereo_off(stereo);
	TV_Off_Command tv_off(tv);
	Hottub_Off_Command hottub_off(hottub);

	COMMANDS party_on;
	party_on.push_back(&light_on);
	party_on.push_back(&stereo_on);
	party_on.push_back(&tv_on);
	party_on.push_back(&hottub_on);
	COMMANDS party_off;
	party_off.push_back(&light_off);
	party_off.push_back(&stereo_off);
	party_off.push_back(&tv_off);
	party_off.push_back(&hottub_off);

	Macro_Command party_on_macro(party_on);
	Macro_Command party_off_macro(party_off);

	control.set_command(0, &party_on_macro, &party_off_macro);

	cout << control << endl;
	cout << "--- Pushing Macro On ---" << endl;
	control.on_button_pushed(0);
	cout << "--- Pushing Macro Off ---" << endl;
	control.off_button_pushed(0);

	return 0;
}

