# PES-ASSIGNMENT-4-Buffhati


Reviewer Partner's name : Balapranesh Elango\
Date and Time : 11th October, 11.30 PM

1) For better readbility, wherever meaningful I have added the appropriate headers
2) Instead of multiplying 0xFF in pwm.c function, I have used efficient left shifting operations which will reduce the number of cycles for same operation
3) In Statemachine.c, I have used a function to abstract the touch slider and switch functionalities from the statemachine function ensuring encapsulation is done properly
4) For better readability, I have used meaningful function names for eg: A function which updates the colour of led based on pwm signal, I renamed it as led_control_pwm instead of start_transiton function name
5) While printing log messages, I have added time in msec as it useful for lettng the know the user when a particular transition is happened
