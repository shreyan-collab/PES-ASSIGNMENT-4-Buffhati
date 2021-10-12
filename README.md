# PES-ASSIGNMENT-4-Buffhati


Reviewer Partner's name : Balapranesh Elango\
Date and Time : 11th October, 11.30 PM

1) For better readbility, wherever meaningful I have added the appropriate headers
2) Instead of multiplying 0xFF in pwm.c function, I have used efficient left shifting operations which will reduce the number of cycles for same operation
3) In Statemachine.c, I have used a function to abstract the touch slider and switch functionalities from the statemachine function ensuring encapsulation is done properly
4) For better readability, I have used meaningful function names for eg: A function which updates the colour of led based on pwm signal, I renamed it as led_control_pwm instead of start_transiton function name
5) While printing log messages, I have added time in msec as it useful for lettng the know the user when a particular transition is happened

The state machine consists of 9 states

START							
STOP						
TRANSITION_TO_GO			
GO				 		
TRANSITION_TO_WARNING			
WARNING							
TRANSITION_TO_STOP				
CROSSWALK 					
TRANSITION_TO_CROSSWALK		
TRANSITION_FROM_CROSSWALK	
CROSSWALK_LED_ON			
CROSSWALK_LED_OFF			

The cross walk is depending on whether the button is pressed(slider change / switch button) is presses

The project conists of 
main.c
statemachine.c
statemachine.h
pwm.c
pwm.
touchslider.c
touchslider.
timer.c
timer.h
switch.c
switch.h files

The program has 2 modes to be run which DEBUG mode and RELEASE mode


