# GPS_rx_Module
## Introduction
This project interfaces the SAM-M8Q module with an Arduino Uno. I used the [SparkFun SAM-M8Q breakout board](https://www.sparkfun.com/products/15210) to make the project easier. SparkFun has premade Arduino libraries with examples for GNSS receivers. More information on this library can be found [here](https://github.com/sparkfun/SparkFun_u-blox_GNSS_Arduino_Library) and it can be installed from the Arduino library manager. In this project, I interfaced using the I2C connection on the breakout.

In this project, I test the accuracy of measuring two points 5m apart and 10m apart as well as the drift between two points when the module does not move in various environments. Please see the wiki for setup and results of my tests.

This project is not compiled with AVR-GCC due to many issues getting the libraries to work outside of the Arduino IDE so all source code is in an Arduino sketch file and is compiled and uploaded to the Arduino Uno using the IDE.


## Wiring
### 2x16 LCD
| LCD Pin | Arduino Pin | Other                                          |
|---------|-------------|------------------------------------------------|
| VSS     | GND         |                                                |
| VDD     | 5V          |                                                |
| V0      |             | Output of a potentiometer between GND and 5  V |
| RS      | 8           |                                                |
| R/W     | GND         |                                                |
| E       | 9           |                                                |
| DB4     | 4           |                                                |
| DB5     | 5           |                                                |
| DB6     | 6           |                                                |
| DB7     | 7           |                                                |
| LED+    |             | 5V   through a 220ohm resistor                 |
| LED-    | GND         |                                                |

### SparkFun SAM-M8Q Breakout using I2C
| SAM-M8Q Pin | Arduino Pin |
|-------------|-------------|
| 3.3v        | 3.3V        |
| GND         | GND         |
| SDA         | SDA         |
| SCL         | SCL         |

### Misc.
Connect a button to 5v on one end and connect the other end to GND through a 5.1k-ohm resistor and to Arduino pin 2

## Running the Project
Install the [SparkFun GNSS](https://github.com/sparkfun/SparkFun_u-blox_GNSS_Arduino_Library) Arduino library and the LiquidCrystal library using the Arduino library manager. Open the `SAM-M8Q_characterization.ino` file in the Arduino IDE, compile, and upload to your Arduino board. The LCD will show all commands and the distance result so the use of the serial monitor is not required. However, for debugging purposes, the latitude and longitude of each point and the distance between them is logged to the serial monitor running at baud rate 115200.

The program runs as follows:
| Code Action                                            | What Screen Displays      | What to do                          |
|--------------------------------------------------------|---------------------------|-------------------------------------|
| Startup                                                | "Running"                 | wait                                |
| Waiting for first location (start of loop)             | "Press to cap location #1"| Push the button                     |
| First set of coordinates logged                        | "Captured #1"             | wait and move to next position      |
| Waiting for second location                            | "Press to cap location #2"| Push the button                     |
| Second set of coordinates logged                       | "Captured #2"             | wait                                |
| Displays the distance between the two points in meters | "Dist = ##.##m"           | Push the button to start loop again |

Here is an example run of my code: https://www.youtube.com/shorts/C4bBnyXEACA
