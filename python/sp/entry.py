#!/usr/bin/env python
################################################################################
################################################################################
#
# Author: Jarret Shook
#
# Module: entry.py
#
# Modifications:
#
# 6-June-13: Version 1.0: Created
#
# Timeperiod: ev6
#
################################################################################
################################################################################

import builtins

builtins.vmware_pre_run = vmware_pre_run
builtins.vmware_post_run = vmware_post_run

import vm

from vm_util import *

################################################################################
################################################################################

def vmware_pre_run(_VirtualMachine):

   if _VirtualMachine._m_startup_file != None:

      mount_vmdk(_VirtualMachine)

      _Command = "cp " + "\"" + _VirtualMachine._m_directory + _VirtualMachine._m_startup_file + "\"" + " " + "\"" + "/mnt/Users/jarret/AppData/Roaming/Microsoft/Windows/Start Menu/Programs/Startup" + "\""

      print _Command

def vmware_post_run(_VirtualMachine):

   print "Hello"
