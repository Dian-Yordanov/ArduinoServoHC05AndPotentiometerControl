# Project Overview:
The idea for the project is to utilize Arduino's capabilities to control servo motors and get input from multiple sources to replicate a "Fingerbot Plus" ( https://www.aliexpress.com/item/1005005168070181.html?spm=a2g0o.order_list.order_list_main.85.71191802QJsqPV ) like device but with more ways to control it than just an Android app and also some more freedom over how it works in practice. The finished Arduino project takes input from a HC-05 Wireless Bluetooth RF Transceiver and a standard 10k ohm potentiometer to move a chunky MG995 Servo Motor and a set of gears to transform horizontal motion to vertical motion. 

# Physical Setup:
The body of the Arduino and all the cables are held together by a lot of rubber, and plastic and cables are extended enough to be able to control the servo from the potentiometer in a range of 2m. 3 wire connectors are used to make it possible to extend that range if needed in the future although there is some limit due to voltage drop. 

# Wireless Communication:
The HC-05 Wireless Bluetooth RF Transceiver is a very old but reliable way to establish wireless serial UART (Universal Asynchronous Receiver-Transmitter) interface communication. A lot of Android apps out of the store can be used to control the servo via Bluetooth but the one I found to work the best is Servo Bluetooth Arduino ( https://play.google.com/store/apps/details?id=com.nl.servoblue&hl=en_US ).

# Code Behavior:
A limitation/feature/bug of the code that works very well in my case but can be a bit annoying in other cases is that the resting position of the servo motor shaft's angle is set by the signal from the potentiometer.  If a signal is received from the HC-05 Bluetooth module and it is a non-0 serial signal, the servo's motor shaft's angle will change to the integer given by the signal ( also should be less or equal to 180 ), but will rotate back to the potentiomether angle integer after some time. This time varies on boards but its value can be calculated by calculating the " delay(50); " and " delay(15); " functions calls as 15 ms + 50 ms + depending on the computing unit of the Arduino board's "void loop()" duration which should be 1 to 2 ms + speed of motor shaft's movement. Let's assume it is 70ms. That is repeated a bit because the board listens for a non-0 serial signal from the Bluetooth receiver in the next loops. On average on an Arduino UNO R3 SMD with CH340G Chip, the change of the servo's motor shaft's angle from the last non-0 Bluetooth receiver's angle value to the potentiometer's angle value happens in 2-3 seconds. 
Because both of the input methods send signals all the time ( the Bluetooth signal is usually 0 while the potentiometer's value is the angle at which the knob is rotated ) it is hard to make one of them take priority over the other in code. You cannot really have code that sets in the loop the value to 1 variable to 2 different values and expect to have only 1 of these values being selected at all times without an additional system for choosing the correct value. It is possible to have this done either via changing what the signal sent by the Android app is or have a physical switch connected to the Arduino for choosing which input device talks to it. However, this is just useless and overcomplicating the project a lot because a "click" in the real world is exactly moving your finger on position A and then changing it to position B in the span of 2-3 seconds - What the Arduino does right now. Essentially a click if controlling the motor shaft's angle via potentiometer only is achieved by just rotating the knob from nonclicking to clicking to nonclicking position and if controlling it via Bluetooth a click is achieved by choosing a value other than 0 for a click and after 2-3 seconds the shaft rotates back to unclicking position on its own. 

# Wowki schematic and code:
"# ArduinoServoHC05AndPotentiometerControl" 
https://wokwi.com/projects/382905922599364609

# Schematic:
![alt text](https://raw.githubusercontent.com/Dian-Yordanov/ArduinoServoHC05AndPotentiometerControl/main/pics/schematic.png?raw=true)

Picture 1 of the final project before mounting to the servo:
![alt text](https://raw.githubusercontent.com/Dian-Yordanov/ArduinoServoHC05AndPotentiometerControl/main/pics/12-03-2023%2017.15_1.jpg?raw=true)

Picture 2 of the final project before mounting to the servo:
![alt text](https://raw.githubusercontent.com/Dian-Yordanov/ArduinoServoHC05AndPotentiometerControl/main/pics/12-03-2023%2017.15_2.jpg?raw=true)