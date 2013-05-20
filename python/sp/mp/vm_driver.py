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

def clone_vm(_FileName, _SourceFile):
   # cloning a virtual machine is defined to be copying the vmdk file or virtual
   # hard drive

   _Command = "cp -r " + "\"" + _FileName + " " + _SourceFile

   #os.system(_Command)
   
   print _Command

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
