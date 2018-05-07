# Line Following Robot
Final code part of a line following robot. We won the first prize in university contest in 2017.

Our robot use Arduino UNO, 05 IR sensors, DC motor control L298, two motors and 2 whells, 1 360 degree whell.

First, 5 IR sensors will be connected to 5 annalog pins from A0 to A4 of the UNO.

Sencond, you must connect the motors with the L298 DC motor control. And connect 6 pins of the L298 to the UNO.
Note that you MUST connect the EN1 and EN2 to pins has PWM of the UNO, so that you can control the speed by PWM.

Note that each pins of the UNO has different max value of PWM. Choose 2 pins have the same max PWM value. 
You can read in the Arduino CC page.

You can read more about L298 in the link here:

https://www.bananarobotics.com/shop/How-to-use-the-L298N-Dual-H-Bridge-Motor-Driver

After setting up all the above conditions, you should upload the checkRobot.ino file, run the robot to see the results,
and adjust the difference PWM between 2 motors.

The reason is when you use the normal motors, with the same PWM, the number of circles in each motor never be the same, so we must 
adjust by adding or subtracting one PWM of motors. Adjust until your robot can run in an approximate straight line.
If you use encoder motors, it is easier to set the speed of the motor and behavior when we faces the conners. 
However, the price of the encoder motor is a little bit high.

After have the real difference PWM value between the motors, you can now add this value to each loop of the main file. 

In the code, we use PID algorithms to control motors when it faces different situations.

The situations depend on the sensor's value.

You can see how it works here:
https://youtu.be/h8QR3Aqcv4U
