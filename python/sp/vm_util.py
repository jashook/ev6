#!/usr/bin/env python
################################################################################
################################################################################
#
# Author: Jarret Shook
#
# Module: vm_util.py
#
# Modifications:
#
# 2-April-13: Version 1.0: Created
#
# Timeperiod: ev6
#
################################################################################
################################################################################

from heavy_thread import heavy_thread

from multiprocessing import Value, Lock
import os
import re

from vm import vm

################################################################################
################################################################################

_ThreadList = [] # empty thread list

_MachineCount = Value('i', 0) # integer value that will be shared between threads

_Lock = Lock()
_CloneLock = Lock()
_MountLock = Lock()

def clone_vm(_VirtualMachine, _ClonedMachine):
   # cloning a virtual machine is defined to be copying the vmdk file or virtual
   # hard drive and the .vmx file

   _CloneLock.acquire() # extremely ram intensive process therefore cloning will only be allowed to one at a time

   def _os_clone_and_copy(_StartArg):

      print "Copying the virtual disk (this operation may take some time)..."

      print "Forking this operation to a seperate thread..."

      _Thread.set_active(True)

      os_copy(_StartArg)

      _ClonedMachine.set_disk_created(True)

      if _ClonedMachine.disk_created(): print "Disk Cloned"

      _Command = "vmrun -T ws snapshot " + "\"" + _ClonedMachine._m_directory + _ClonedMachine._m_config_file + "\"" + " NewMachineSnapShot"

      print "Creating Snapshot"

      os.system(_Command)

      _Thread.sleep(15) # make sure the snapshot finishes before starting

      _ClonedMachine._m_disk_file = find_snapshot(_ClonedMachine)

      print "Snapshot Created continuing..."

      print "Completed copying the virtual disk, joining back to main thread..."

      _Thread.set_active(False)
   
      _ThreadList.remove(_Thread)

      _CloneLock.release()

      _ClonedMachine() # callback function is nested inside the virtual machine class

   _CopyDiskCommand = "vmware-vdiskmanager -r " + "\"" + _VirtualMachine._m_directory + _VirtualMachine._m_disk_file + "\"" + " -t 0 " + "\"" + _ClonedMachine._m_directory + _ClonedMachine._m_disk_file + "\"" # long operation, fork to a seperate thread

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

def find_snapshot(_VirtualMachine):

   _Vmdks = list()

   for _FileName in os.listdir(_VirtualMachine._m_directory):

      _Extension = _FileName[-5::] # .vmdk is 5 characters long

      if _Extension == ".vmdk": _Vmdks.append(_FileName)

   _Vmdk = None

   _Min = 0

   for _File in _Vmdks:

      if len(_File) > _Min:

         _Min = len(_File)
         _Vmdk = _File

   return _Vmdk

def mount_vmdk(_VirtualMachine, _PartitionNumber = 1, _Path = None):

   _MountLock.acquire() # make sure not to overmount a previous mount

   if not _Path: _Path = "/mnt"

   _Command = "vmware-mount " + "\"" + _VirtualMachine._m_directory + _VirtualMachine._m_disk_file + "\"" + " " + str(_PartitionNumber) + " " + "\"" + _Path + "\""

   os.system(_Command)

   print _Command

   _MountLock.release()

def os_copy(_Command):

   print _Command # print what command is being run

   os.system(_Command)

def umount_vmdk(_VirtualMachine, _Path = None):

   if not _Path: _Path = "\mnt"

   _Command = "vmware-mount -d " + "\"" + _VirtualMachine._m_mount_directory + "\""

   os.system(_Command)

   print _Command

def vmware_create(_WorkingDirectory, _DestinationDirectory, _StartUpFile = None, _NewVmx = "default.vmx", _NewVmdk = "default.vmdk", _CloneMachine = True):

   _Vmx, _Vmdk = find_files(_WorkingDirectory)

   _VirtualMachine = vm(_WorkingDirectory, _Vmx, _Vmdk, _StartUpFile, True, True)

   _Vmx = _NewVmx

   _Vmdk = _NewVmdk

   if _CloneMachine:

      _ClonedMachine = vm(_DestinationDirectory, _Vmx, _Vmdk, _StartUpFile, False, False)

   else:

      _ClonedMachine = vm(_DestinationDirectory, _Vmx, _Vmdk, _StartUpFile, True, True)

   _ClonedMachine.set_function(vmware_entry_point)

   # increasing machine count ** need to lock **

   _Lock.acquire()

   _MachineCount.value = _MachineCount.value + 1

   _Lock.release() # synchronize finished

   if _CloneMachine: clone_vm(_VirtualMachine, _ClonedMachine)

   else: 

      _ClonedMachine._m_disk_file = find_snapshot(_ClonedMachine)

      _ClonedMachine() # if the machine is created then just run it

   return _ClonedMachine

def vmware_entry_point(_VirtualMachine):

   _Thread = heavy_thread(vmware_run, (_VirtualMachine, _MachineCount))

   _ThreadList.append(_Thread)

   _VirtualMachine._m_thread = _Thread

   # pre run code here

   _VirtualMachine.pre_run_function()

   _Thread.set_active(True)

   _Thread.start()


def vmware_is_running(_VirtualMachine):

   _Command = "vmrun list >> running_vms.txt"

   os.system(_Command)

   _File = open("running_vms.txt")

   _Running = False

   for _Line in _File:

      if re.match(_VirtualMachine._m_directory + _VirtualMachine._m_config_file, _Line): _Running = True

   _File.close()

   _File = open("running_vms.txt", 'w')

   _File.close()

   return _Running

def vmware_run(_VirtualMachine, _MachineCount):

   _Thread = _VirtualMachine._m_thread

   _Command = "vmrun start " + "\"" + _VirtualMachine._m_directory + _VirtualMachine._m_config_file + "\""

   print _Command

   _Thread.sleep(2)

   os.system(_Command)

   _Thread.sleep(1)

   _Count = 0

   _Retried = False

   while vmware_is_running(_VirtualMachine) is False:

      _Thread.sleep(10) # sleep for a little to make sure it does not prematurely exit

      if _Retried is True and _Count > 2:

         print "Second Timeout, quitting..."

         break

      if _Count > 2: 

         print "Timeout..."

         print "Virtual Machine failed to start, retrying.."

         _Command = "vmrun start " + "\"" + _VirtualMachine._m_directory + _VirtualMachine._m_config_file + "\""

         print _Command

         _Count = 0

         _Retried = True

      else:
      
         _Count = _Count + 1

   while True:

      if not vmware_is_running(_VirtualMachine): break

      _Thread.sleep(2.5) # sleep for 2.5 seconds
  
   # decreasing machine count ** need to lock **

   _Lock.acquire()

   _MachineCount.value = _MachineCount.value - 1

   _Lock.release() # synchronize finished

   _VirtualMachine.post_run_function()

   _Thread.set_active(False)

def vmware_join():

   for _Thread in _ThreadList:

      if _Thread.is_active():

         print "Thread joining..."

         _Thread.join() #if alive join
