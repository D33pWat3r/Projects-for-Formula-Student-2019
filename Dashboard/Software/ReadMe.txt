TODos:
- Button auf Changing Interrupt ändern
- Demo kann durch Knopf ausgelöst werden
- Button-Leds können angesteuert werden

**************************************************************


Dashoard_v1.0 (by Matthias Gramm)
#functions:
	-read CAN Messages and save it
	-if no CAN Messages arrive, values for the demonstration are generated (RPM, Gear, Temperature)
	-use the LED Band as RPM visualisation
	-flicker the LED Band to show, that the Gear can be changing
	-show on the 4digit (7-Segment) Display the current gear and the rpm value
	-flicker the Display to show, that the engine temperature is to high

Dashoard_v1.1 (by Rick Hollinski)
#improvement:
	-split the Code to different files with different characteristics
	-some variables are packed in structures
#new functions:
	-the config.h File is for config values only; e.g. the hardware configuration (used IO-Pins)
	-CAN functions and configs has a seperate files (ConvertCanData.h or *.cpp) for a cleaner overview
	-all other relevant functions and values are in the Dashboard.h file and seperated in different sections (e.g. Debugging, CAN, Demo Mode, RPM Band, ...)


Dashoard_v1.2 (by Rick Hollinski)
#improvement:
	-fill the config.h file with configurations to modify the software without change the algorithm
#new functions:
	-add a input mode to use a pushbutton
	-there are different screens (for endurance and acceleration) for the segment display, which can switch with the pushbutton

Dashoard_v1.2b (by Rick Hollinski)
#improvement:
	-fill the config.h file with more configurations
#new functions:
	-add the function ,that the demo mode can be activate by the pushbutton; but this is to buggy

Dashoard_v1.2c (by Rick Hollinski)
#improvement:
	-add new config value in the config.h
	-delete the buggy push button functions; demo Mode can not be activate by pushbutton now
	-there are new (better) text for the different screens
#new functions:
	-add a new CAN function to read out the shiftLed Signal; but this new value is not used now
	-add a new screen (States), which show successive different values
	-the new "state" screen use the Led Stripe to show the actual progress of max showed states
	
Dashoard_v1.3 (by Rick Hollinski)
#improvement:
	-add much more possibilies entries in the config.h file
#new functions:
	-add a new RPM band function, which use for different ranges the full led stripe and show it with different colors	
	-add a brightness function to show different brightness level for the led stripe
	
Dashoard_v1.4 (by Rick Hollinski)
#improvement:
	-some new entries in the config.h file
#new functions:
	-add the possibbility to change the rpm value by a potentiometer, which use one of the analog ports
	-add the shiftlight function, which use the CAN Signal
	-there are a test modus for the shiftlight, which use the pushbutton to activate the shiftlight; but the screen change function is disabled in this modus
	-there a debugging screen, which can not be selected by the pushbutton, but it can be select as the start screen after boot
	
Dashoard_v1.4b (by Rick Hollinski)
#improvement:
    -add libs to specific folder
#new functions:
	-there are a seperate shiftlight function, which use not the CAN signal and use the RPM value
	-the 2 different shiftlight functions can be select in the config.h file
	