# Project Overview:
The idea for the project is to utilize Arduino's capabilities to control servo motors and get input from multiple sources to replicate a "Fingerbot Plus" ( https://www.aliexpress.com/item/1005005168070181.html?spm=a2g0o.order_list.order_list_main.85.71191802QJsqPV ) like device but with more ways to control it than just an Android app and also some more freedom over how it works in practice. The finished Arduino project takes input from a HC-05 Wireless Bluetooth RF Transceiver and a standard 10k ohm potentiometer to move a chunky MG995 Servo Motor and a set of gears to transform horizontal motion to vertical motion. 

# Physical Setup:
The body of the Arduino and all the cables are held together by a lot of rubber and plastic. Cables are extended enough to be able to control the servo from the potentiometer in a range of 2m. 3 wire connectors are used to make it possible to extend that range if needed in the future although there is some limit due to voltage drop. 

# Wireless Communication:
The HC-05 Wireless Bluetooth RF Transceiver is an old but reliable way to establish wireless serial UART (Universal Asynchronous Receiver-Transmitter) interface communication. A lot of Android apps out of the store can be used to control the servo via Bluetooth but the one I found to work the best is Servo Bluetooth Arduino ( https://play.google.com/store/apps/details?id=com.nl.servoblue&hl=en_US ).

# Code Behavior:
In the code, there exists a notable functionality/limitation/bug that, while effective in my specific case, may pose challenges in alternative scenarios. Specifically, the baseline position of the servo motor shaft is determined by the potentiometer signal. When a non-zero serial signal is received from the HC-05 Bluetooth module, the servo motor adjusts its shaft angle to match the integer value of the received signal (limited to 180 degrees). 

However, it eventually reverts to the potentiometer-defined angle after a duration calculated based on the " delay(50); " and " delay(15); " functions calls as 15 ms + 50 ms + depending on the computing unit of the Arduino board's "void loop()" duration which should be 1 to 2 ms + speed of motor shaft's movement, which sum up to approximately 70ms. This process is repeated as the board continuously checks for non-zero serial signals in subsequent loops.

On an Arduino UNO R3 SMD with CH340G Chip, the transition from the last non-zero Bluetooth receiver angle to the potentiometer angle takes an average of 2-3 seconds. The challenge arises from the continuous signaling of both input methods – Bluetooth (typically 0 when not active) and the potentiometer (reflecting the rotated knob's angle). This makes it complex to prioritize one input over the other in the code. Attempting to manage this in a loop with a single variable for two different values requires an additional system for value selection.

Possible solutions involve altering the signal sent by the Android app or introducing a physical switch connected to the Arduino, allowing manual selection of the active input device. However, implementing such solutions may introduce unnecessary complexity to the project.

The Arduino currently replicates a real-world "click" by smoothly transitioning the motor shaft's angle from position unclicked position to clicked postion back to unclicked position in 2-3 seconds. This mimics the act of moving your finger from a non-clicking to clicking position. Specifically, when controlling the motor shaft's angle via the potentiometer, a "click" is achieved by rotating the knob from a non-clicking to clicking position. Conversely, when using Bluetooth control, a "click" is simulated by selecting a value other than 0, and after 2-3 seconds, the shaft automatically returns to the unclicked position.

# Wowki schematic and code:
"# ArduinoServoHC05AndPotentiometerControl" 
https://wokwi.com/projects/382905922599364609

# Schematic:
![alt text](https://raw.githubusercontent.com/Dian-Yordanov/ArduinoServoHC05AndPotentiometerControl/main/pics/schematic.png?raw=true)

Picture 1 of the final project before mounting to the servo:
![alt text](https://raw.githubusercontent.com/Dian-Yordanov/ArduinoServoHC05AndPotentiometerControl/main/pics/12-03-2023%2017.15_1.jpg?raw=true)

Picture 2 of the final project before mounting to the servo:
![alt text](https://raw.githubusercontent.com/Dian-Yordanov/ArduinoServoHC05AndPotentiometerControl/main/pics/12-03-2023%2017.15_2.jpg?raw=true)