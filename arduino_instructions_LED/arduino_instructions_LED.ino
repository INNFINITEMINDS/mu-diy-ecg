/******************************************************************************
                          arduino_instructions_LED.ino
																	ARDUINO CODE
*******************************************************************************

Written by: Samuel Bechara, PhD
            samuel.bechara@marquette.edu
            Biomedical Engineering
            Marquette University

Created: 10 November 2015
Last Edited: 22 November 2016

Description ------------------------------------------------------------------
This arduino code is meant to be used for the Marquette University
Arduino outreach project. Specifically to interface a sparkfun redboard with a
sparkfun heart monitor (part#: ADB232) and to display the results on an
Adafruit 7 segment LED Display.

This code relies heavily on libraries written by Sparkfun and Adafruit
employees so please support them and buy their stuff!

If you have any questions about the intended use of this code, please visit
http://www.marquette.edu/biomedical-engineering/outreach.php

Copyright (c) 2016 Samuel Bechara
******************************************************************************/

// Libraries used in this code
#include <Statistic.h>
#include <Wire.h>
#include <Adafruit_LEDBackpack.h>
#include <Adafruit_GFX.h>

// initialize variables
boolean rWaveFlag = false; // this is the "flag" that we will flip when we suspect an r-wave occurs
int latestReading = 0; // the latest reading from the heart monitor is stored here
int average = 0; // this variable holds the average of all the data points and acts as a "baseline"
int inputPin = A0; // change this value if you change the input pin on the arduino
int sensitivity = 2.5; // this is the number of standard deviations above baseline a data point must be to be considered part of an r-wave
int timeDifference = 0; // the difference between the r-wave detected and the last r-wave is stored here
int bpmCalc[3]={0, 0, 0}; // an array to store the previous 3 BPM calculations
int averageBPM = 0; // the average of the bpm Calculations in the bpmCalc array
float rWaveOneTime = 0; // the previous r-wave time
float rWaveTwoTime = 0; // the current r-wave time
float beatsPerMinute = 0; // beats per minute :)
float threshold = 0; // this is the actual value a data point must be at least to be considered part of an r-wave
float pop_stddev = 0; // standard deviation of the population of all data points collected

Statistic readings; // initialize an instance of the Statistic class for data analysis of the serial data

Adafruit_7segment LEDdisplay = Adafruit_7segment(); // initialize an instance of the class for the LED display and call it LEDdisplay

void setup()
{
	// initialize the serial communication:
	Serial.begin(9600);
	pinMode(10, INPUT); // Setup for leads off detection LO +
	pinMode(11, INPUT); // Setup for leads off detection LO -
	LEDdisplay.begin(0x70);
	LEDdisplay.clear();
	readings.clear(); // start fresh
}

// this loop is where all of the action happens
void loop()
{
  // IF the leads are off
	if((digitalRead(10) == 1) || (digitalRead(11) == 1))
	{
		// write ! to the serial port
		Serial.println('!');

		// writes "0FF" on the LED if leads are off
		LEDdisplay.clear();
		LEDdisplay.writeDigitNum(1,0); // first number cooresponds to position on LED
		LEDdisplay.writeDigitNum(3,15); // second is the HEX number
		LEDdisplay.writeDigitNum(4,15); // i.e. "15" is HEX for "F"
		LEDdisplay.writeDisplay();
		LEDdisplay.blinkRate(2); // try changing 0 1 2 or 3 and see what happens!
		LEDdisplay.setBrightness(7); // change the values from 1 to 15

		/*delay(1000);
		// writes "DEAD" on the LED if the leads are off
		LEDdisplay.clear();
		LEDdisplay.print(57005, HEX);
		LEDdisplay.writeDisplay();
		*/
		delay(3000); // wait 3 seconds for user to attach electrodes and calm down
	}

	// OR ELSE the leads must be attached
	else
	{
		LEDdisplay.blinkRate(0); // turn LED blinking off
		LEDdisplay.setBrightness(15);
		latestReading = analogRead(inputPin); // store the newest data point into the latestReading variable
		readings.add(latestReading); // add latest reading to readings instance
		Serial.println(latestReading); // send the value of analog input inputPin:
		average = int(readings.average()); // calculates the average of ALL data points collected
		pop_stddev = int(readings.pop_stdev()); // calculates the standard deviation of ALL data points collected
		threshold = (int)((sensitivity * pop_stddev) + average); // calculate a threshold

		// check to see if the latest data point could be considered part of an r-wave
    // if things are looking weird, try changing the sensitivity above and sit still :)
		if (abs(float(latestReading)) > threshold)
		{
			rWaveFlag = true; // Flag as true! We have found an r-wave!
		}
		else
		{
			rWaveFlag = false; // awww shucks, not part of an r-wave
		}

		// If there has been an r-wave detected, this section calculates the BPM and displays it on the LED screen
		if ((rWaveFlag == true))
		{
			rWaveTwoTime = millis(); // sets rWaveTwoTime to however long the arduino has been running (ms)
			rWaveTwoTime = (float) rWaveTwoTime; // cast rWaveTwoTime as a float for calculations
			timeDifference = rWaveTwoTime - rWaveOneTime; // calculate the time difference
			if (timeDifference > 300) // allow 300ms buffer time (means that MAX detecable heart rate is 200 BPM)
			{
				beatsPerMinute = (float) 60000 / (timeDifference); // convert ms/beat into beat/min
				//LEDdisplay.print((int)beatsPerMinute); // cast BPM as int and send to LED display
				//LEDdisplay.writeDisplay();
				bpmCalc[0]=bpmCalc[1];
				bpmCalc[1]=bpmCalc[2];
				bpmCalc[2]=beatsPerMinute;
				averageBPM = (int)((bpmCalc[0]+bpmCalc[1]+bpmCalc[2])/3);

				if (averageBPM > 35)
				{
					LEDdisplay.clear();
					LEDdisplay.print((int)averageBPM);
					LEDdisplay.writeDisplay();
				}

				rWaveOneTime = rWaveTwoTime; // on our way out of loop, set rWaveOneTime = rWaveTwoTime since it will be the first wave of the next reading!
			}
		}
	}

	//Wait for a bit to keep serial data from saturating
	delay(1);
}
