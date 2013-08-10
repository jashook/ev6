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

from multiprocessing import Lock
import os

################################################################################
################################################################################

URLS = open("urls.txt")

URLList = URLS.readlines()

_Lock = Lock()

Index = 0

def get_url_index():

   _Lock.acquire()

   global Index

   _CurrentIndex = Index

   Index = Index + 1

   _Lock.release()

   return _CurrentIndex

def vmware_pre_run(_VirtualMachine):

   if _VirtualMachine._m_startup_file != None:

      vm_util.mount_vmdk(_VirtualMachine, 3, _VirtualMachine._m_mount_directory)

      _Command = "sudo echo " + URLList[int(float(get_url_index()) % len(URLList))][:-1] + " > " + "\"" + _VirtualMachine._m_mount_directory + "url.txt" + "\""

      print _Command

      os.system(_Command)

      vm_util.umount_vmdk(_VirtualMachine)

def vmware_post_run(_VirtualMachine):

   if _VirtualMachine._m_startup_file != None:

      vm_util.mount_vmdk(_VirtualMachine, 2, _VirtualMachine._m_mount_directory)

      _Command = "sudo cp -r " + "\"" + _VirtualMachine._m_mount_directory + "pictures" "\"" + " "+ "\"" + _VirtualMachine._m_collection + "/pictures" + "\""
      
      print _Command

      os.system(_Command)

      _Command = "sudo cp -r " + "\"" + _VirtualMachine._m_mount_directory + "pcaps" "\"" + " "+ "\"" + _VirtualMachine._m_collection + "/pcaps" + "\""
      print _Command

      os.system(_Command)

      vm_util.umount_vmdk(_VirtualMachine)
