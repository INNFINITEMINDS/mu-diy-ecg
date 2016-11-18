/******************************************************************************
                                trace_ecg.pde
*******************************************************************************

Author: Dr. Samuel Bechara
        Marquette University
        Biomedical Engineering Outreach
Email:  samuel.bechara@marquette.edu

Created: 10 November 2015
Last modified: 17 November 2016

*******************************************************************************
Heads up:
On linux systems, you may need to change owner of the serial port to gain access
sudo chown username /dev/ttyUSB0

Disclosure:
  This code borrows a lot from the Demo Program for AD8232 Heart Rate sensor by
  Casey Kuhns. Thanks SparkFun and Casey!

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
******************************************************************************/

import processing.serial.*;

Serial myPort;        // The serial port
int xPos = 1;         // horizontal position of the graph
int i = 0;            // R wave counter

float height_old = 0;
float height_new = 0;
float inByte = 0;
float T = 0;          //t and T are time place holders
float t = 0;

//initialize heart rate calculation variables
float heart_rate = 0;
float derivative = 0;
float[] heart_rate_array = new float[3]; //3 cell array to store heart_rate values for average.
float heart_rate_avg = 0;
float r_interval = 0;

String heart_rate_disp = str(0);

PFont font;


void setup () {
  // set the window size
  size(1000, 400);

  //set the font for the heart rate indicator
  font = createFont ("Serif", 32);
  textFont (font);

  // List all the available serial ports
  println(Serial.list());

  // Open whatever port is the one you're using
  //********** YOU MAY NEED TO CHANGE THE SERIAL PORT NUMBER!!!! ************//
  myPort = new Serial(this, Serial.list()[0], 9600);

  // don't generate a serialEvent() unless you get a newline character
  myPort.bufferUntil('\n');

  // set inital background to white
  background(255, 255, 255);
}


void draw () {
  // everything happens in the serialEvent()
}


void serialEvent (Serial myPort) {
  // get the ASCII string:
  String inString = myPort.readStringUntil('\n');

  if (inString != null) {
    // trim off any whitespace:
    inString = trim(inString);

    // If leads off detection is true, notify with blue line
    if (inString.equals("!")) {
      stroke(0, 0, 0xff); //Set stroke to blue ( R, G, B)...He's dead Jim.
      inByte = 512;  // middle of the ADC range (Flat Line)
    }

    // If the data is good let it through
    else {
      stroke(0xff, 0, 0); //Set stroke to red ( R, G, B)
      inByte = float(inString);
     }

     //Map and draw the line for new data point
     inByte = map(inByte, 0, 1023, 0, height);
     height_new = height - inByte;
     line(xPos - 1, height_old, xPos, height_new);
     t=millis();

     //Calculate the derivative (slope) between the previous two points
     derivative = abs(height_new - height_old);

     //If derivative is greater than value indicated begin check if it is an R wave
     //This is the beginning of 3 nested if statements

     if (derivative>20) {
       r_interval = t-T;
       //println(r_interval + "r_interval");

        //assume time interval between R waves cooresponds to a heart rate greater than 20bpm, or else it is just noise
        if (r_interval > 300) {
          heart_rate=((1/(r_interval/1000))*60); //Calculates the heart rate from the R time period
          T=t;
          //println(heart_rate + "heart rate");

          if (i<2) {
            heart_rate_array[i] = heart_rate;
            text("R", xPos, height_new-50); //draw an X where program things R wave occurs. This is so you can visualize if program is identifying R wave correctly
            i=i+1;
          }

          //if it is an R wave, and there have been 3 R waves, calculate the average and display it
          else {
            text("R", xPos, height_new-50); //draw an X where program things R wave occurs. This is so you can visualize if program is identifying R wave correctly
            heart_rate_array[i] = heart_rate;
            heart_rate_avg = ((heart_rate_array[0]+heart_rate_array[1]+heart_rate_array[2])/3);
            heart_rate_disp = str(round(heart_rate_avg)); //convert heart_rate into a string so we can show it
            println(heart_rate_array); //Displays the heart rate array in the message area
            i=0;
          }
        }
       }

     height_old = height_new;

      // at the edge of the screen, go back to the beginning
      if (xPos >= width) {
        //remove saveFrame comment below and change to your name if you would like to save the frame.
        //** WARNING: program will not stop taking frames **//
        //saveFrame("bechara_heart-####.png");
        xPos = 0;
        background(0xff);
      }

     //update heart rate on display
     else if (xPos==1) {
      fill(255,0,0);
      textAlign(CENTER);
      text("Heart Rate (bpm): "+ heart_rate_disp,width/2,60); //Note: this will only display the last calculated heart rate
      xPos++;
     }

      else {
        // increment the horizontal position
        xPos++;
      }

  }
}
