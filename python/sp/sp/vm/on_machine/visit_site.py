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
# Notes:
#
#     uses the cmd line in windows to launch ie(any version) and to go to the 
#     website given as a command line parameter
#
################################################################################
################################################################################

import sys
import os

################################################################################
################################################################################

if __name__ == '__main__':

   _Command = "\"" + "C:\Program Files\Internet Explorer\iexplore.exe" + "\"" + " " + "google.com"

   print _Command

   os.system(_Command)

   os.system("PAUSE")
