/******************************************************************************
                       arduino_instructions_broken.ino
                                ARDUINO CODE
*******************************************************************************

Written by: Samuel Bechara, PhD
            samuel.bechara@marquette.edu
            Biomedical Engineering
            Marquette University

Created: 23 November 2016
Last Edited: 23 November 2016

Description ------------------------------------------------------------------
This arduino code is meant to be used for the Marquette University
Arduino outreach project. Specifically to interface a sparkfun redboard with a
sparkfun heart monitor (part#: ADB232).

NOTE: There are two intentional mistakes left in this code. The goal is to find
them and correct them based on the Arduino errors and your intuition!

This code relies heavily on libraries written by Sparkfun and Adafruit
employees so please support them and buy their stuff.

If you have any questions about the intended use of this code, please visit
http://www.marquette.edu/biomedical-engineering/outreach.php

Copyright (c) 2016 Samuel Bechara
******************************************************************************/

/* The setup() function is called when a sketch starts. The setup function will
only run once, after each powerup or reset of the Arduino board. */
void setup()
{
  // initialize the serial communication:
  Serial.begin(9600);
  pinMode(XX, INPUT); // Setup for leads off detection LO +
  pinMode(11, INPUT); // Setup for leads off detection LO -
}

/* The loop() function does precisely what its name suggests, and loops
consecutively. */
void loop()
{
  // checks if the user is not connected
  if((digitalRead(10) == 1)||(digitalRead(YY) == 1))
  {
    // if they aren't connected, print ! to the serial port
    Serial.println('!');
  }
  else
  {
    // Or else they ARE connected.
    // So this line sends the value from the heart monitor to the A0 port
      Serial.println(analogRead(A0));
  }
  //Wait for a bit to keep serial data from saturating
  delay(1);
}
