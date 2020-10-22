# microprocessor-lab
Lab 2 of MTE241 Intro to Computer Structures and Real-time Systems
Authors: Julia Baribeau and Glenn Tipold

The code we wrote is in main.c. Everything else is system configuration, startup, etc.
This project is to be run on LPC1768 microcontroller, or using hardware simulator such as in Keil uVision5. 

The goal of the lab was to write four functions which work in tandem with a micropresser and accompanying 
hardware and peripherals. 

The four functions are as follows:
  Part 1 -- Write a program to continually read the value of the pushbutton, and turn the topmost
            (or leftmost) LED on when the button is down and off when the button is up.
            
  Part 2 -- Write a program to continually read the joystick and print a message out the serial port
            that indicates whether the joystick position is North, South, East, West or Centre, and whether
            or not it’s pressed in.
            
  Part 3 -- Write a program to repeatedly read a string that’s typed by the user into the serial port,
            convert that string into a number, and display the number in binary on the LEDs. The number
            can be in the range of 0 to 255. When entering text through the serial port, you should end the
            input by pressing ctrl+J which is the ASCII newline character. So for example, if the user enters
            75 and presses ctrl+J, the LEDs should display 1001011.
            
  Part 4 -- Write a program to continually read the value of the analog to digital converter, and
            print the value out the serial port as a decimal number.
            
We coded each of the four functions, and select one of four main() functions using conditional compilation.
