/******************************************************************************
                          arduino_instructions.ino
                                ARDUINO CODE
*******************************************************************************

Written by: Samuel Bechara, PhD
            samuel.bechara@marquette.edu
            Biomedical Engineering
            Marquette University

Created: 10 November 2015
Last Edited: 6 July 2016


Description ------------------------------------------------------------------
This arduino code is meant to be used to interface a sparkfun redboard with a
sparkfun heart monitor (part#: ADB232) and displays the estimated heart rate
(in beats per minute) on an Adafruit 7 Segment LED Backpack (part#: HT16K33)

This code relies heavily on libraries written by Sparkfun and Adafruit
employees so please support them and buy their stuff!

If you have any questions about the intended use of this code, please visit
http://www.marquette.edu/biomedical-engineering/outreach.php

Copyright (c) 2016 Samuel Bechara
******************************************************************************/

void setup() {
  // initialize the serial communication:
  Serial.begin(9600);
  pinMode(10, INPUT); // Setup for leads off detection LO +
  pinMode(11, INPUT); // Setup for leads off detection LO -

}

void loop() {

  if((digitalRead(10) == 1)||(digitalRead(11) == 1)){
    Serial.println('!');
  }
  else{
    // send the value of analog input 1:
      Serial.println(analogRead(A0));
  }
  //Wait for a bit to keep serial data from saturating
  delay(1);
}
