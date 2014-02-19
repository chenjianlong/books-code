PROJECT (party)
CMAKE_MINIMUM_REQUIRED (VERSION 2.8)

SET (party_SOURCE_FILES
	ceiling_fan.cpp
	ceiling_fan_high_command.cpp
	ceiling_fan_medium_command.cpp
	ceiling_fan_off_command.cpp
	hottub.cpp
	hottub_off_command.cpp
	hottub_on_command.cpp
	light.cpp
	light_off_command.cpp
	light_on_command.cpp
	livingroom_light_off_command.cpp
	livingroom_light_on_command.cpp
	macro_command.cpp
	main.cpp
	no_command.cpp
	remote_control.cpp
	remote_loader.cpp
	stereo.cpp
	stereo_off_command.cpp
	stereo_on_command.cpp
	stereo_on_with_cd_command.cpp
	tv.cpp
	tv_off_command.cpp
	tv_on_command.cpp
	)

ADD_EXECUTABLE (party ${party_SOURCE_FILES})
INSTALL (TARGETS party DESTINATION bin)

