#!/usr/bin/env python
################################################################################
################################################################################
#
# Author: Jarret Shook
#
# Module: vm_driver.py
#
# Modifications:
#
# 2-April-13: Version 1.0: Created
#
# Timeperiod: ev6
#
# Notes:
#
#   A simple python script that starts and runs a python script (a) virtual machine(s)
#   At the moment the script only supports starting a python script on a windows machine
#
################################################################################
################################################################################

from heavy_thread import heavy_thread

import os
import re

from vm import vm

################################################################################
################################################################################

_ThreadList = [] # empty thread list

def clone_vm(_VirtualMachine, _ClonedMachine):
   # cloning a virtual machine is defined to be copying the vmdk file or virtual
   # hard drive and the .vmx file

   def _os_clone_and_copy(_StartArg):

      print "Copying the virtual disk (this operation may take some time)..."

      print "Forking this operation to a seperate thread..."

      _Thread.set_active(True)

      os_copy(_StartArg)

      _ClonedMachine.set_disk_created(True)

      if _ClonedMachine.disk_created(): print "Disk Cloned"

      print "Completed copying the virtual disk, joining back to main thread..."

      _Thread.set_active(False)
   
      _ThreadList.remove(_Thread)

      _ClonedMachine() # callback function is nested inside the virtual machine class

   _CopyDiskCommand = "cp " + "\"" + _VirtualMachine._m_directory + _VirtualMachine._m_disk_file + "\"" + " " + "\"" + _ClonedMachine._m_directory + _ClonedMachine._m_disk_file + "\"" # long operation, fork to a seperate thread

   _Thread = heavy_thread(_os_clone_and_copy, (_CopyDiskCommand,))

   _ThreadList.append(_Thread)

   _Thread.start()

   _File = open(_VirtualMachine._m_directory + _VirtualMachine._m_config_file) # default open to read only

   # Check to see if the .vmx file that is being copied will automatically ignore copying the .vmdk file.
   # If not then add in two lines that will auto answer the prompted message to be true
 
   _Matched = False

   _ReWriteFile = True

   for _Line in _File:

      if re.match("uuid.action = *", _Line): _Matched = True

      elif re.match("scsi0:0.fileName = *", _Line):

         if re.match("scsi0:0.fileName = " + _ClonedMachine._m_disk_file, _Line): _ReWriteFile = False

   _File.close()

   _File = open(_VirtualMachine._m_directory + _VirtualMachine._m_config_file) # default read only

   _Lines = _File.readlines()

   if _ReWriteFile:

      _File = open(_ClonedMachine._m_directory + _ClonedMachine._m_config_file, 'w')

      for _Line in _Lines:

         if not re.match("scsi0:0.fileName = *", _Line): _File.write(_Line)

      _File.write("scsi0:0.fileName = " + "\"" + _ClonedMachine._m_disk_file + "\"")

      _File.write("\n")

   _ClonedMachine.set_config_created(True)
 
   if _ClonedMachine.config_created(): print "VMX file cloned"
  
   if not _Matched:

      _File = open(_ClonedMachine._m_directory + _ClonedMachine._m_config_file, 'a') # open the new file to append

      _File.write("uuid.action = \"create\"")
      _File.write("\n") # new line
      _File.write("msg.autoAnswer = \"TRUE\"")

def cp(_Src, _File):

   _Command = "cp " + _Src + " " + _File

   os.system(_Command)

   print _Command

def find_files(_Path):

   _Vmdk = None
   _Vmx = None

   for _FileName in os.listdir(_Path):
      
      _Extension = _FileName[-5::]   # .vmdk is 5 characters long

      if _Extension == ".vmdk": _Vmdk = _FileName

      _Extension = _FileName[-4::]   # .vmx is 4 characters long

      if _Extension == ".vmx": _Vmx = _FileName

   return _Vmx, _Vmdk

def mount_vmdk(_VirtualMachine, _Path = None):

   if not _Path: _Path = "/mnt"

   _Command = "vmware-mount -f " + "\"" + _VirtualMachine._m_directory + _VirtualMachine._m_disk_file + "\"" + " " + "\"" + _Path + "\""

   #os.system(_Command)

   print _Command

def os_copy(_Command):

   print _Command # print what command is being run

   os.system(_Command)

def umount_vmdk(_VirtualMachine, _Path = None):

   if not _Path: _Path = "\mnt"

   _Command = "vmware-mount -d " + "\"" + _VirtualMachine._m_directory + _VirtualMachine._m_disk_file + "\"" + " " + "\"" + _Path + "\""

   #os.system(_Command)

   print _Command

def vmware_entry_point(_VirtualMachine):

   _Thread = heavy_thread(vmware_run, (_VirtualMachine, _Thread))

   _Thread.start()

def vmware_is_running(_VirtualMachine):

   _Command = "vmrun list >> running_vms.txt"

   #os.system(_Command)

   print _Command

   _File = open("running_vms.txt")

   _Running = False

   for _Line in _File:

      if re.match("*" + _VirtualMachine._m_config_file + "*", _Line): _Running = True

   return _Running

def vmware_run(_VirtualMachine, _Thread):

   _Command = "vmrun start " + "\"" + _VirtualMachine._m_directory + _VirtualMachine._m_config_file + "\""

   print _Command

   os.system(_Command)

   while vmware_is_running(_VirtualMachine):

      _Thread.sleep(5000) # sleep for 5 seconds

if __name__ == '__main__':

   _File = "hello.txt"

   _Path = "\media\hdd"

   _WorkingDirectory = "/home/jarret/vmware/Ubuntu 64-bit/"

   _DestinationDirectory = "/media/hdd0/Virtual Machines/"

   _Vmx, _Vmdk = find_files(_WorkingDirectory)

   _VirtualMachine = vm(_WorkingDirectory, _Vmx, _Vmdk, True, True)

   _Vmx = "New Windows.vmx"

   _Vmdk = "New Windows.vmdk"

   _ClonedMachine = vm(_DestinationDirectory, _Vmx, _Vmdk, False, False)

   _ClonedMachine.set_function(vmware_entry_point)

   clone_vm(_VirtualMachine, _ClonedMachine)

   mount_vmdk(_ClonedMachine, _Path)

   umount_vmdk(_ClonedMachine, _Path)

   # go through the list of threads and join them to the main thread so they are not prematurely stopped

   for _Thread in _ThreadList:

      if _Thread.is_active(): 

         print "Thread joining..."

         _Thread.join() # if alive join
