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

import os

################################################################################
################################################################################

def clone_vm(_SourceConfig, _SourceDisk, _DestinationConfig, _DestinationDisk):
   # cloning a virtual machine is defined to be copying the vmdk file or virtual
   # hard drive and the .vmx file

   _CopyDiskCommand = "cp" + "\"" + _SourceDisk + "\"" +  " " + _DestinationDisk # long operation, fork to seperate thread

   #os.system(_CopyDiskCommand)
   
   print _CopyDiskCommand

   _File = open(_SourceConfig) # default open to read only

   # Check to see if the .vmx file that is being copied will automatically ignore copying the .vmdk file.
   # If not then add in two lines that will auto answer the prompted message to be true
 
   _Matched = False

   for _Line in _File:

      if re.match("uuid.action = *", _Line): _Matched = True

   _CopyVmxCommand = "cp" + "\"" + _SourceConfig + "\"" + " " + _DestinationConfig

   #os.system(_CopyVmxCommand)

   print _CopyVmxCommand

   if !_Matched:

      _File = open(_DestinationConfig, 'a') # open the new file to append

      _File.write("uuid.action = \"create\"")
      _File.write("msg.autoAnswer = \"TRUE\"")

   # join before continuing

def cp(_Src, _File):

   _Command = "cp " + _Src + " " + _File

   #os.system(_Command)

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

def mount_vmdk(_Vmdk, _Path = None):

   if not _Path: _Path = "/mnt"

   _Command = "vmware-mount -f" + _Vmdk + " " + _Path

   #os.system(_Command)

   print _Command

def umount_vmdk(_Path = None):

   if not _Path: _Path = "\mnt"

   _Command = "vmware-mount -d" + _Path

   #os.system(_Command)

   print _Command

if __name__ == '__main__':

   _File = "hello.txt"

   _Path = "\media\hdd"

   _Vmx, _Vmdk = find_files("/media/hdd/Virtual Machines/Windows 7 x64")

   clone_vm(_Vmx, "New Windows")

   mount_vmdk(_Vmdk, _Path)

   cp(_Path, _File)

   umount_vmdk(_Path)
