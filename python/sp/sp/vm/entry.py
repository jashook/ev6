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

from multiprocessing import Value, Lock
import os
import re

import time

################################################################################
################################################################################

def vmware_pre_run(_VirtualMachine):

   if _VirtualMachine._m_startup_file != None:

      vm_util.mount_vmdk(_VirtualMachine, 2, _VirtualMachine._m_mount_directory)

      _Command = "sudo echo " + _VirtualMachine._m_url + " > " + "\"" + _VirtualMachine._m_mount_directory + "url.txt" + "\""

      print _Command

      os.system(_Command)

      vm_util.umount_vmdk(_VirtualMachine, _VirtualMachine._m_mount_directory)

def vmware_post_run(_VirtualMachine):

   if _VirtualMachine._m_startup_file != None:

      _Command = "sudo vmrun -T ws snapshot " + "\"" + _VirtualMachine._m_directory + _VirtualMachine._m_config_file + "\"" + " NewMachineSnapShot2"

      print "Creating Snapshot"

      os.system(_Command)

      time.sleep(15) # make sure the snapshot finishes before starting

      _Vmdk = vm_util.find_last_snapshot(_VirtualMachine)

      _Command = "sudo cp " + "\"" + _VirtualMachine._m_directory + _Vmdk + "\"" + " " + "\"" + _VirtualMachine._m_collection + "\""
      print _Command

      os.system(_Command)

      print "Deleting snapshot"

      _Command = "sudo vmrun -T ws deleteSnapshot " + "\"" + _VirtualMachine._m_directory + _VirtualMachine._m_config_file + "\"" + " NewMachineSnapshot2"

      os.system(_Command)

      time.sleep(20)

      vm_util.mount_vmdk(_VirtualMachine, 3, _VirtualMachine._m_mount_directory)

      _Command = "sudo cp -r " + "\"" + _VirtualMachine._m_mount_directory + "pictures" "\"" + " "+ "\"" + _VirtualMachine._m_collection + "/pictures" + "\""
      
      print _Command

      os.system(_Command)

      time.sleep(.1)

      _Command = "sudo cp -r " + "\"" + _VirtualMachine._m_mount_directory + "pcaps" "\"" + " "+ "\"" + _VirtualMachine._m_collection + "/pcaps" + "\""
      print _Command

      os.system(_Command)

      time.sleep(.1)

      _Command = "sudo cp -r " + "\"" + _VirtualMachine._m_mount_directory + "cookies" "\"" + " "+ "\"" + _VirtualMachine._m_collection + "/cookies" + "\""
      print _Command

      os.system(_Command)

      time.sleep(.1)

      _Command = "sudo cp -r " + "\"" + _VirtualMachine._m_mount_directory + "source" "\"" + " "+ "\"" + _VirtualMachine._m_collection + "/source" + "\""
      print _Command

      os.system(_Command)

      time.sleep(5)

      vm_util.umount_vmdk(_VirtualMachine, _VirtualMachine._m_mount_directory)
