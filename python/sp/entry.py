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
# 17-June-13: Version 1.0: Last Updated
# 6-June-13: Version 1.0: Created
#
# Timeperiod: ev6
#
################################################################################
################################################################################

import vm_util

import os

################################################################################
################################################################################

def vmware_pre_run(_VirtualMachine):

   if _VirtualMachine._m_startup_file != None:

      vm_util.mount_vmdk(_VirtualMachine, 2, _VirtualMachine._m_mount_directory)

      _Command = "sudo cp " + "\"" + _VirtualMachine._m_startup_file + "\"" + " " + "\"" + _VirtualMachine._m_mount_directory + "\""

      print _Command

      os.system(_Command)

      vm_util.umount_vmdk(_VirtualMachine)

def vmware_post_run(_VirtualMachine):

   print "Hello"
