/******************************************************************************
                                trace_ecg.pde
                               PROCESSING CODE
*******************************************************************************
INFORMATION---------------------------------------------------------------------
Author: Dr. Samuel Bechara
        Marquette University
        Biomedical Engineering Outreach
Email:  samuel.bechara@marquette.edu

Created: 10 November 2015
Last modified: 17 November 2016

REQUIREMENTS -------------------------------------------------------------------
This code is meant to be run using the processing IDE. It is free, open source,
and available at https://processing.org/

It is compatible with Processing version 3+

NOTE ---------------------------------------------------------------------------
On linux systems, you may need to change owner of the serial port to gain access
sudo chown username /dev/ttyUSB0

DISCLOSURE ---------------------------------------------------------------------
This code borrows a lot from the Demo Program for AD8232 Heart Rate sensor by
Casey Kuhns. Thanks SparkFun and Casey!

LICENSE ------------------------------------------------------------------------
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
******************************************************************************/
