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

import vm_util

################################################################################
################################################################################

def vmware_pre_run(_VirtualMachine):

   if _VirtualMachine._m_startup_file != None:

      vm_util.mount_vmdk(_VirtualMachine, _VirtualMachine._m_mount_directory)

      _Command = "cp " + "\"" + _VirtualMachine._m_directory + _VirtualMachine._m_startup_file + "\"" + " " + "\"" + _VirtualMachine._m_mount_directory + "Users/jarret/AppData/Roaming/Microsoft/Windows/Start Menu/Programs/Startup" + "\""

      print _Command

      #os.system(_Command)

      vm_util.umount_vmdk(_VirtualMachine)

def vmware_post_run(_VirtualMachine):

   print "Hello"
