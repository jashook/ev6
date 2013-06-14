#!/usr/bin/env python
################################################################################
################################################################################
# 
# Author: Jarret Shook
#
# Module: visit_site.py
#
# Modifications:
#
# 5-May-13: Version 1.0: Created
#
# Timeperiod: ev6
#
# Notes:
#
#     Uses the cmd line in windows to launch ie(any version) and go to the website given as a command line parameter
#
################################################################################
################################################################################

import sys
import os

################################################################################
################################################################################

if __name__ == '__main__':
   
   #if (len(sys.argv) == 2): 

      _Command = "\"" + "C:\Program Files\Internet Explorer\iexplore.exe" + "\"" + " " + "google.com"

      print _Command

      os.system(_Command)

      os.system("PAUSE")

   #else:

      #print "Error incorrect number of arguements.  Expected (script) (url to visit)"
