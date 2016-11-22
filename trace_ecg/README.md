
# trace_ecg.pde
# PROCESSING CODE
## Information
Author: Dr. Samuel Bechara
        samuel.bechara@marquette.edu
        Marquette University
        Biomedical Engineering Outreach

Created: 10 November 2015
Last modified: 17 November 2016

## How to use this program
In order to use this program, it is likely that you are going to have to "hack" the code to get it to work.

Look through the program and find the following line of code:
`myPort = new Serial(this, Serial.list()[0], 9600);`
You might have to change the [0] to a different number i.e.) [1] depending on how your computer lists the serial ports. Remember, arrays in processing begin indexing at 0.

![ScreenShot](/screenshots/processing_example.png)

## Requirements
This code is meant to be run using the processing IDE. It is free, open source,
and available at [https://processing.org/](https://processing.org/)

It is compatible with Processing version 3+

## Note
On linux systems, you may need to change owner of the serial port to gain access
`sudo chown username /dev/ttyUSB0`

### DISCLOSURE
This code borrows a lot from the Demo Program for AD8232 Heart Rate sensor by
Casey Kuhns. Thanks SparkFun and Casey!

### LICENSE
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
